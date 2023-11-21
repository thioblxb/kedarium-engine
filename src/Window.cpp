#include "Kedarium/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  kdr::Window* appWindow = (kdr::Window*)glfwGetWindowUserPointer(window);
  appWindow->getBoundCamera()->setAspect((float)width / height);
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

void kdr::Window::maximize()
{
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwSetWindowMonitor(
    glfwWindow,
    monitor,
    0,
    0,
    mode->width,
    mode->height,
    mode->refreshRate
  );
  isFullscreenOn = true;
}

void kdr::Window::unmaximize()
{
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwSetWindowMonitor(
    glfwWindow,
    NULL,
    0,
    0,
    width,
    height,
    mode->refreshRate
  );
  isFullscreenOn = false;
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
  glfwSetWindowUserPointer(glfwWindow, this);

  _initializeGlew();
  _initializeOpenGLSettings();
}

void kdr::Window::_updateDeltaTime()
{
  float currentTime = (float)glfwGetTime();
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
}

void kdr::Window::_updateCamera()
{
  if (boundShaderID == 0) return;
  if (boundCamera == NULL) return;

  boundCamera->updateMatrix();
  boundCamera->applyMatrix(boundShaderID, "cameraMatrix");
}

void kdr::Window::_update()
{
  glfwPollEvents();
  update();
  _updateDeltaTime();
  _updateCamera();
}

void kdr::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  render();
  glfwSwapBuffers(glfwWindow);
}
