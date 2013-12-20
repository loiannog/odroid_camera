#ifndef JPEG_COMPRESS_H
#define JPEG_COMPRESS_H

/**
 * JPEG compresses a grayscale image. The output is written to g_jpeg_buf and the size of the output is written to
 * g_jpeg_data_len. Note: The size of g_jpeg_buf is not the size of the compressed image, you need to check
 * g_jpeg_data_len.
 * @param[in] image_buf Buffer containing the input grayscale image
 * @param[in] width     Width of the image in image_buf
 * @param[in] height    Height of the image in image_buf
 */
void compress_bw(const uint8_t *image_buf, int width, int height);

extern std::vector<unsigned char> g_jpeg_buf;
extern size_t g_jpeg_data_len;

#endif
