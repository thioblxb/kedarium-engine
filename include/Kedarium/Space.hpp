#ifndef KDR_SPACE_HPP
#define KDR_SPACE_HPP

#include <math.h>

namespace kdr
{
  namespace Space
  {
    /**
     * Represents a 3D vector with components x, y, and z.
     */
    class Vec3
    {
      public:
        float x {0.f};
        float y {0.f};
        float z {0.f};

        /**
         * Default constructor for Vec3. Initializes all components to 0.
         */
        Vec3()
        {}
        /**
         * Parameterized constructor for Vec3.
         *
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         * @param z The z-component of the vector.
         */
        Vec3(
          const float x,
          const float y,
          const float z
        ) : x(x), y(y), z(z)
        {}
    };

    /**
     * Represents a 4x4 matrix.
     */
    class Mat4
    {
      public:
        float elements[4][4];

        /**
         * Default constructor for Mat4. Initializes all elements to 0.
         */
        Mat4()
        {
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              elements[y][x] = 0.f;
            }
          }
        }

        /**
         * Constructs a 4x4 matrix with diagonal elements set to a specified value.
         *
         * @param diagonalValue The value to set for the diagonal elements.
         */
        Mat4(const float diagonalValue)
        {
          for (int y = 0; y < 4; y++)
          {
            for (int x = 0; x < 4; x++)
            {
              elements[y][x] = 0.f;
            }
          }
          for (int i = 0; i < 4; i++)
          {
            elements[i][i] = diagonalValue;
          }
        }

        /**
         * Accesses the elements of the matrix using array-like syntax.
         *
         * @param index The index of the row in the matrix.
         * @return A pointer to the array representing the specified row.
         */
        float* operator[](const int index)
        {
          return elements[index];
        }

        /**
         * Accesses the elements of the matrix using array-like syntax (const version).
         *
         * @param index The index of the row in the matrix.
         * @return A const pointer to the array representing the specified row.
         */
        const float* operator[](const int index) const
        {
          return elements[index];
        }

        /**
         * Multiplies this 4x4 matrix with another matrix.
         *
         * @param other The matrix to multiply with.
         * @return The resulting matrix after multiplication.
         */
        Mat4 operator*(const Mat4& other) const {
          Mat4 result {0.f};
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              for (int k = 0; k < 4; k++) {
                result[i][j] += other[i][k] * elements[k][j];
              }
            }
          }
          return result;
        }
    };

    /**
     * Converts degrees to radians.
     *
     * @param degrees The angle in degrees to be converted.
     * @return The equivalent angle in radians.
     */
    static const float radians(const float degrees)
    { return degrees * 3.1416f / 180.f; }
    /**
     * Translates a 4x4 matrix by a specified 3D vector.
     *
     * @param mat The input 4x4 matrix.
     * @param vec The 3D vector representing translation.
     * @return A new 4x4 matrix resulting from the translation.
     */
    kdr::Space::Mat4 translate(const kdr::Space::Mat4& mat, const kdr::Space::Vec3& vec);
    /**
     * Creates a perspective projection matrix.
     *
     * @param fov    The field of view angle in radians.
     * @param aspect The aspect ratio of the projection (width / height).
     * @param near   The distance to the near clipping plane.
     * @param far    The distance to the far clipping plane.
     * @return A 4x4 matrix representing the perspective projection.
     */
    kdr::Space::Mat4 perspective(const float fov, const float aspect, const float near, const float far);
  }
}

#endif // KDR_SPACE_HPP
