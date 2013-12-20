#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdint.h>
#include "jpeglib.h"

std::vector<unsigned char> g_jpeg_buf;
size_t g_jpeg_data_len = 0;

static void error_exit(j_common_ptr cinfo)
{
  (*cinfo->err->output_message) (cinfo);
  jpeg_destroy_compress((j_compress_ptr) cinfo);
  printf("JPEG compression error");
  exit(1);
}

void init_destination(j_compress_ptr cinfo)
{
  if(g_jpeg_buf.size() == 0)
  {
    const size_t initial_size = 65536;
    g_jpeg_buf.resize(initial_size);
  }
  cinfo->dest->next_output_byte = &(g_jpeg_buf[0]);
  cinfo->dest->free_in_buffer = g_jpeg_buf.size();
}

boolean empty_output_buffer(j_compress_ptr cinfo)
{
  const size_t size = g_jpeg_buf.size();
  g_jpeg_buf.resize(2*size);
  cinfo->dest->next_output_byte = &(g_jpeg_buf[size]);
  cinfo->dest->free_in_buffer = g_jpeg_buf.size() - size;

  return TRUE;
}

void term_destination(j_compress_ptr cinfo)
{
  int len = g_jpeg_buf.size() - (cinfo->dest->free_in_buffer);
  g_jpeg_data_len = len;
}

void compress_bw(const uint8_t *image_buf, int width, int height)
{
  const int quality = 90;

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jerr.error_exit = error_exit;

  jpeg_create_compress(&cinfo);
  if (cinfo.dest == NULL) {
    cinfo.dest = (struct jpeg_destination_mgr *)
      (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo, JPOOL_PERMANENT,
				 sizeof(struct jpeg_destination_mgr));
  }
  cinfo.dest->init_destination = init_destination;
  cinfo.dest->empty_output_buffer = empty_output_buffer;
  cinfo.dest->term_destination = term_destination;

  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = 1; //3;
  cinfo.in_color_space = JCS_GRAYSCALE; //JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);
  cinfo.write_JFIF_header = false;
  cinfo.dct_method = JDCT_IFAST;

  jpeg_start_compress(&cinfo, TRUE);
  JSAMPLE row[width];
  JSAMPROW row_pointer[1];
  *row_pointer = row;

  while (cinfo.next_scanline < cinfo.image_height)
  {
    row_pointer[0] = const_cast<uint8_t*>(image_buf + cinfo.next_scanline*width);
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
}
