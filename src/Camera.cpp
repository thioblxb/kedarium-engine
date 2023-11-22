#include "Kedarium/Camera.hpp"

void kdr::Camera::handleMovement(GLFWwindow* window, const float deltaTime)
{
  _updateCursor(window);
  if (!isCursorLocked) {
    return;
  }

  if (kdr::Keys::isPressed(window, kdr::Key::W))
  {
    position += front * speed * deltaTime;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::S))
  {
    position -= front * speed * deltaTime;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::A))
  {
    position -= kdr::Space::normalize(kdr::Space::cross(front, up)) * speed * deltaTime;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::D))
  {
    position += kdr::Space::normalize(kdr::Space::cross(front, up)) * speed * deltaTime;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::Spacebar))
  {
    position.y += speed * deltaTime;
  }
  if (kdr::Keys::isPressed(window, kdr::Key::LeftShift))
  {
    position.y -= speed * deltaTime;
  }

  int windowWidth {0};
  int windowHeight {0};
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

  double mouseX {0.};
  double mouseY {0.};
  glfwGetCursorPos(window, &mouseX, &mouseY);

  float deltaX = (float)(mouseX - (windowWidth / 2)) / windowWidth * sensitivity;
  float deltaY = (float)(mouseY - (windowHeight / 2)) / windowHeight * sensitivity;

  yaw += deltaX;
  pitch -= deltaY;

  if (pitch > 85.f) pitch = 85.f;
  if (pitch < -85.f) pitch = -85.f;

  yaw = std::remainderf(yaw, 360.f);

  glfwSetCursorPos(window, (double)windowWidth / 2, (double)windowHeight / 2);
}

void kdr::Camera::updateMatrix()
{
  kdr::Space::Vec3 tempFront {0.f};

  tempFront.x = cos(kdr::Space::radians(pitch)) * cos(kdr::Space::radians(yaw));
  tempFront.y = sin(kdr::Space::radians(pitch));
  tempFront.z = cos(kdr::Space::radians(pitch)) * sin(kdr::Space::radians(yaw));

  front = kdr::Space::normalize(tempFront);

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

void kdr::Camera::applyMatrix(const GLuint shaderID, const std::string& uniformName)
{
  GLuint matrixLoc = glGetUniformLocation(shaderID, uniformName.c_str());
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
