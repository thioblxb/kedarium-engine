#ifndef KDR_GRAPHICS_HPP
#define KDR_GRAPHICS_HPP

#include <GL/glew.h>

#include "File.hpp"

namespace kdr
{
  namespace Graphics
  {
    /**
     * Represents an OpenGL shader program in the Kedarium Engine.
     */
    class Shader
    {
      public:
        /**
         * Constructs a shader program using the provided vertex and fragment shader files.
         *
         * @param vertexPath   The path to the vertex shader file.
         * @param fragmentPath The path to the fragment shader file.
         */
        Shader(const char* vertexPath, const char* fragmentPath);

        /**
         * Retrieves the OpenGL ID of the shader program.
         *
         * @return The OpenGL ID of the shader program.
         */
        const GLuint getID() const
        { return this->ID; }

        /**
         * Activates the shader program for use in rendering.
         */
        void Use()
        { glUseProgram(this->ID); }
        /**
         * Deletes the shader program from OpenGL memory.
         */
        void Delete()
        { glDeleteProgram(this->ID); }

      private:
        GLuint ID;
    };
  }
}

#endif // KDR_GRAPHICS_HPP
