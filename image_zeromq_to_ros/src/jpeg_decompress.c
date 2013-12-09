#include "jpeg_decompress.h"
#include <stdio.h>
#include <jpeglib.h>

#if JPEG_LIB_VERSION < 80
static void init_mem_source(j_decompress_ptr cinfo)
{
  /* no work necessary here */
}

static boolean fill_mem_input_buffer(j_decompress_ptr cinfo)
{
  static const JOCTET mybuffer[4] = { (JOCTET) 0xFF, (JOCTET) JPEG_EOI, 0, 0 };

  /* Insert a fake EOI marker */

  cinfo->src->next_input_byte = mybuffer;
  cinfo->src->bytes_in_buffer = 2;

  return TRUE;
}

static void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
  struct jpeg_source_mgr *src = cinfo->src;

  if (num_bytes > 0)
  {
    while (num_bytes > (long) src->bytes_in_buffer)
    {
      num_bytes -= (long) src->bytes_in_buffer;
      (void) (*src->fill_input_buffer) (cinfo);
      /* note we assume that fill_input_buffer will never return FALSE,
       * so suspension need not be handled.
       */
    }
    src->next_input_byte += (size_t) num_bytes;
    src->bytes_in_buffer -= (size_t) num_bytes;
  }
}

static void term_source(j_decompress_ptr cinfo)
{
    /* no work necessary here */
}
#endif

void jpeg_decompress(const uint8_t *compressed, size_t len, uint8_t **decompressed, int *width, int *height, int *channels)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

#if JPEG_LIB_VERSION < 80
  cinfo.src = (struct jpeg_source_mgr *) (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo, JPOOL_PERMANENT,
      sizeof(struct jpeg_source_mgr));

  cinfo.src->init_source = init_mem_source;
  cinfo.src->fill_input_buffer = fill_mem_input_buffer;
  cinfo.src->skip_input_data = skip_input_data;
  cinfo.src->resync_to_restart = jpeg_resync_to_restart; /* use default method */
  cinfo.src->term_source = term_source;
  cinfo.src->bytes_in_buffer = len;
  cinfo.src->next_input_byte = (JOCTET *) compressed;
#else
  jpeg_mem_src(&cinfo, (uint8_t*)compressed, len);
#endif

  jpeg_read_header(&cinfo, TRUE);
  int ret = jpeg_start_decompress(&cinfo);
  if(ret == 0)
  {
    fprintf(stderr, "Error in jpeg_start_decompress\n");
  }

  unsigned int output_width = cinfo.output_width;
  unsigned int output_height = cinfo.output_height;
  unsigned int output_channels = cinfo.output_components;

  if(*decompressed == NULL)
    *decompressed = (uint8_t*) malloc(output_width * output_height * output_channels);

  *width = output_width;
  *height = output_height;
  *channels = output_channels;

  JSAMPROW output_data;
  unsigned int scanline_len = output_width * output_channels;
  unsigned int scanline_count = 0;
  while(cinfo.output_scanline < cinfo.output_height)
  {
    output_data = (*decompressed + (scanline_count * scanline_len));
    jpeg_read_scanlines(&cinfo, &output_data, 1);
    scanline_count++;
  }

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}
