#ifndef KDR_SOLIDS_HPP
#define KDR_SOLIDS_HPP

#include <GL/glew.h>

#include "Graphics.hpp"
#include "Space.hpp"

namespace kdr
{
  namespace Solids
  {
    /**
     * Represents a generic 3D solid object.
     */
    class Solid
    {
      public:
        /**
         * Constructs a Solid object with a specified position.
         *
         * @param position The 3D position of the solid.
         */
        Solid(const kdr::Space::Vec3& position)
        : position(position)
        {}
        /**
         * Virtual destructor for the Solid class.
         */
        virtual ~Solid();

        /**
         * Renders the solid object using a specified shader program.
         *
         * This is a pure virtual function, and it should be implemented by derived classes
         * to define how the solid object is rendered with a specific shader program.
         *
         * @param shaderID The ID of the shader program used for rendering.
         */
        virtual void Render(const GLuint shaderID) = 0;

      protected:
        kdr::Space::Vec3 position;

        kdr::Graphics::VAO* VAO {NULL};
        kdr::Graphics::VBO* VBO {NULL};
        kdr::Graphics::EBO* EBO {NULL};

        /**
         * Applies the position of the solid to a shader uniform variable.
         *
         * @param shaderID The ID of the shader program where the model matrix is updated.
         */
        void _applyPosition(const GLuint shaderID);
    };

    /**
     * Represents a cube, derived from the Solid class.
     */
    class Cube : public Solid
    {
      public:
        /**
         * Constructs a Cube object with a specified position and edge length.
         *
         * @param position The 3D position of the cube.
         * @param edgeLength The length of each edge of the cube.
         */
        Cube(const kdr::Space::Vec3& position, const float edgeLength);

        /**
         * Renders the cube using a specified shader program.
         *
         * @param shaderID The ID of the shader program used for rendering.
         */
        void Render(const GLuint shaderID);
    };

    /**
     * Represents a cuboid (rectangular box) in 3D space.
     */
    class Cuboid : public Solid
    {
      public:
        /**
         * Constructs a Cuboid object with a specified position, length, height, and width.
         *
         * @param position The 3D position of the cuboid.
         * @param length The length of the cuboid along the x-axis.
         * @param height The height of the cuboid along the y-axis.
         * @param width The width of the cuboid along the z-axis.
         */
        Cuboid(const kdr::Space::Vec3& position, const float length, const float height, const float width);

        /**
         * Renders the cuboid using the specified shader program.
         *
         * @param shaderID The ID of the shader program used for rendering.
         */
        void Render(const GLuint shaderID);
    };
  }
}

#endif // KDR_SOLIDS_HPP
