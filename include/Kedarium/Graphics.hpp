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

    /**
     * Represents an OpenGL Vertex Buffer Object (VBO) in the Kedarium Engine.
     */
    class VBO
    {
      public:
        /**
         * Constructs a Vertex Buffer Object (VBO) with the provided vertex data.
         *
         * @param vertices An array of GLfloat representing the vertex data.
         * @param size     The size of the vertex data array in bytes.
         */
        VBO(GLfloat vertices[], GLsizeiptr size);

        /**
         * Retrieves the OpenGL ID of the Vertex Buffer Object (VBO).
         *
         * @return The OpenGL ID of the VBO.
         */
        const GLuint getID() const
        { return this->ID; }

        /**
         * Binds the Vertex Buffer Object (VBO) for use.
         */
        void Bind()
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * Unbinds the Vertex Buffer Object (VBO).
         */
        void Unbind()
        { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        /**
         * Deletes the Vertex Buffer Object (VBO) from OpenGL memory.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID;
    };
  }
}

#endif // KDR_GRAPHICS_HPP
