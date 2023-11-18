#include "Kedarium/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

kdr::Window::~Window()
{
  glfwDestroyWindow(glfwWindow);
}

void kdr::Window::loop()
{
  while (!glfwWindowShouldClose(glfwWindow))
  {
    _update();
    _render();
  }
}

void kdr::Window::close()
{
  glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
}

const bool kdr::Window::_initializeGlfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return true;
}

const bool kdr::Window::_initializeGlew()
{
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(err) << '\n';
    glfwTerminate();
    return false;
  }
  return true;
}

void kdr::Window::_initializeOpenGLSettings()
{
  glPointSize(5.f);
  glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
}

void kdr::Window::_initialize()
{
  _initializeGlfw();
  glfwWindow = glfwCreateWindow(
    width,
    height,
    title.c_str(),
    NULL,
    NULL
  );
  if (glfwWindow == NULL)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(glfwWindow);
  _initializeGlew();
  _initializeOpenGLSettings();
}

void kdr::Window::_update()
{
  glfwPollEvents();
  update();
}

void kdr::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  render();
  glfwSwapBuffers(glfwWindow);
}
