#ifndef KDR_FILE_HPP
#define KDR_FILE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace kdr
{
  namespace File
  {
    /**
     * Retrieves the contents of a file specified by its path.
     *
     * @param path The path to the file.
     * @return A string containing the contents of the file. If the file cannot be opened,
     *         an error message is printed to the standard error stream, and an empty string is returned.
     */
    const std::string getContents(const std::string& path);
  }
}

#endif // KDR_FILE_HPP
