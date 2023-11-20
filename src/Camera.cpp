#include "Kedarium/Camera.hpp"

void kdr::Camera::handleMovement(GLFWwindow* window)
{
  _updateCursor(window);
  if (!isCursorLocked) {
    return;
  }

  if (kdr::Keys::isPressed(window, kdr::Key::W))
  {
    position += front * speed;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::S))
  {
    position -= front * speed;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::A))
  {
    position += kdr::Space::normalize(kdr::Space::cross(front, up)) * speed;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::D))
  {
    position -= kdr::Space::normalize(kdr::Space::cross(front, up)) * speed;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::Spacebar))
  {
    position.y += speed;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::LeftShift))
  {
    position.y -= speed;
  }
}

void kdr::Camera::updateMatrix()
{
  kdr::Space::Mat4 view {1.f};
  kdr::Space::Mat4 proj {1.f};

  view = kdr::Space::lookAt(
    position,
    position + front,
    up
  );
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

void kdr::Camera::_updateCursor(GLFWwindow* window)
{
  glfwSetInputMode(
    window,
    GLFW_CURSOR,
    isCursorLocked
      ? GLFW_CURSOR_DISABLED
      : GLFW_CURSOR_NORMAL
  );
}
