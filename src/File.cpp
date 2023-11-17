#include "Kedarium/File.hpp"

const std::string kdr::File::getContents(const char* path)
{
  std::ifstream file(path);
  if (!file.is_open())
  {
    std::cerr << "Failed to open the file: " << path << "!\n";
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}
