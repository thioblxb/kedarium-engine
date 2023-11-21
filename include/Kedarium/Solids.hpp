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
         * Renders the solid object.
         *
         * This is a pure virtual function, and it should be implemented by derived classes
         * to define how the solid object is rendered.
         */
        virtual void Render() = 0;

      protected:
        kdr::Space::Vec3 position;

        kdr::Graphics::VBO* VBO {NULL};
        kdr::Graphics::EBO* EBO {NULL};
        kdr::Graphics::VAO* VAO {NULL};
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
         * Renders the cube.
         */
        void Render();
    };
  }
}

#endif // KDR_SOLIDS_HPP
