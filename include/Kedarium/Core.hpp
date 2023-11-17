#ifndef KDR_KEDARIUM_HPP
#define KDR_KEDARIUM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace kdr
{
  namespace Core
  {
    /**
     * Prints information about the engine, including its name, version, author, and license.
     */
    void printEngineInfo();
    /**
     * Prints version information related to graphics libraries used by the Kedarium Engine.
     */
    void printVersionInfo();
  }
}

#endif // KDR_KEDARIUM_HPP
