#include "Kedarium/Image.hpp"

const bool kdr::Image::loadFromPNG(const std::string& path, unsigned char **data, int &width, int &height)
{
  png_image image;
  memset(&image, 0, sizeof(image));
  image.version = PNG_IMAGE_VERSION;

  if (!png_image_begin_read_from_file(&image, path.c_str())) {
    std::cerr << "Failed to begin reading PNG: " << path << std::endl;
    return false;
  }

  image.format = PNG_FORMAT_RGBA;
  *data = new unsigned char[PNG_IMAGE_SIZE(image)];

  if (!png_image_finish_read(&image, nullptr, *data, 0, nullptr)) {
    std::cerr << "Failed to finish reading PNG: " << path << std::endl;
    delete[] *data;
    return false;
  }

  width = image.width;
  height = image.height;

  const int row_size = image.width * PNG_IMAGE_PIXEL_CHANNELS(image.format);
  unsigned char* temp_row = new unsigned char[row_size];

  for (int row = 0; row < height / 2; ++row) {
    unsigned char* top_row = *data + row * row_size;
    unsigned char* bottom_row = *data + (height - row - 1) * row_size;
    memcpy(temp_row, top_row, row_size);
    memcpy(top_row, bottom_row, row_size);
    memcpy(bottom_row, temp_row, row_size);
  }
  delete[] temp_row;
  
  return true;
}
