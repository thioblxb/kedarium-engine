#ifndef KDR_IMAGE_HPP
#define KDR_IMAGE_HPP

#include <png.h>
#include <cstring>
#include <iostream>

namespace kdr
{
  namespace Image
  {
    /**
     * Loads an image from a PNG file.
     *
     * @param path The path to the PNG file.
     * @param data A pointer to the image data. This pointer will be updated to point to the loaded image data.
     * @param width The width of the loaded image.
     * @param height The height of the loaded image.
     * @return True if the image is successfully loaded, false otherwise.
     */
    const bool loadFromPNG(const std::string& path, unsigned char** data, int& width, int& height);
  }
}

#endif // KDR_IMAGE_HPP
