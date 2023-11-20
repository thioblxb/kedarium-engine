#include "Kedarium/Camera.hpp"
#include <iostream>

void kdr::Camera::updateMatrix()
{
  kdr::Space::Mat4 view {1.f};
  kdr::Space::Mat4 proj {1.f};

  view = kdr::Space::translate(view, position);
  proj = kdr::Space::perspective(
    kdr::Space::radians(fov),
    aspect,
    near,
    far
  );

  matrix = proj * view;
}

void kdr::Camera::applyMatrix(const GLuint shaderID, const char* uniformName)
{
  GLuint matrixLoc = glGetUniformLocation(shaderID, uniformName);
  glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, &matrix[0][0]);
}
