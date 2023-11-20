#ifndef KDR_WINDOW_HPP
#define KDR_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Graphics.hpp"
#include "Camera.hpp"

namespace kdr
{
  /**
   * Represents the properties of a window in the Kedarium Engine.
   */
  struct WindowProps
  {
    unsigned int width;
    unsigned int height;
    std::string  title;

    /**
     * Constructs window properties with specified width, height, and title.
     *
     * @param width  The width of the window.
     * @param height The height of the window.
     * @param title  The title of the window.
     */
    WindowProps(
      const unsigned int width,
      const unsigned int height,
      const std::string& title
    ) : width(width), height(height), title(title)
    {}
  };

  /**
   * Represents a window in the Kedarium Engine.
   */
  class Window
  {
    public:
      /**
       * Constructs a window with the provided window properties.
       *
       * @param windowProps The properties of the window.
       */
      Window(const WindowProps& windowProps)
      : width(windowProps.width), height(windowProps.height), title(windowProps.title)
      { this->_initialize(); }
      /**
       * Constructs a window with specified width and height.
       *
       * @param width  The width of the window.
       * @param height The height of the window.
       */
      Window(const unsigned int width, const unsigned int height)
      : width(width), height(height)
      { this->_initialize(); }
      /**
       * Constructs a window with specified width, height, and title.
       *
       * @param width  The width of the window.
       * @param height The height of the window.
       * @param title  The title of the window.
       */
      Window(const unsigned int width, const unsigned int height, const std::string& title)
      : width(width), height(height), title(title)
      { this->_initialize(); }
      /**
       * Virtual destructor for the Window class.
       */
      virtual ~Window();

      /**
       * Retrieves the GLFW window associated with the Window instance.
       *
       * @return A pointer to the GLFW window.
       */
      GLFWwindow* getGlfwWindow()
      { return this->glfwWindow; }
      /**
       * Retrieves the width of the window.
       *
       * @return The width of the window.
       */
      const unsigned int getWidth() const
      { return this->width; }
      /**
       * Retrieves the height of the window.
       *
       * @return The height of the window.
       */
      const unsigned int getHeight() const
      { return this->height; }
      /**
       * Retrieves the title of the window.
       *
       * @return The title of the window.
       */
      const std::string getTitle() const
      { return this->title; }
      /**
       * Retrieves the time elapsed between the current and previous frame.
       *
       * @return The time elapsed between the current and previous frame in seconds.
       */
      const float getDeltaTime() const
      { return this->deltaTime; }
      /**
       * Retrieves the currently bound camera for the window.
       *
       * @return A pointer to the bound Camera object.
       */
      kdr::Camera* getBoundCamera() const
      { return this->boundCamera; }

      /**
       * Sets the currently bound camera for the window.
       *
       * @param camera A pointer to the Camera object to be bound.
       */
      void setBoundCamera(kdr::Camera* camera)
      { this->boundCamera = camera; }

      /**
       * Starts the main loop for the window.
       */
      void loop();
      /**
       * Closes the window.
       */
      void close();

    protected:
      /**
       * To be implemented by derived classes. Sets up the window environment.
       */
      virtual void setup() = 0;
      /**
       * To be implemented by derived classes. Updates the window state.
       */
      virtual void update() = 0;
      /**
       * To be implemented by derived classes. Renders the window state.
       */
      virtual void render() = 0;

      void bindShader(kdr::Graphics::Shader& shader)
      {
        shader.Use();
        boundShaderID = shader.getID();
      }

    private:
      GLFWwindow* glfwWindow {NULL};

      unsigned int width  {800};
      unsigned int height {600};
      std::string  title  {"Kedarium Engine"};

      float lastTime  {(float)glfwGetTime()};
      float deltaTime {0.f};

      GLuint       boundShaderID {0};
      kdr::Camera* boundCamera   {NULL};

      /**
       * Initializes GLFW for the window.
       *
       * @return True if initialization is successful, false otherwise.
       */
      const bool _initializeGlfw();
      /**
       * Initializes GLEW for the window.
       *
       * @return True if initialization is successful, false otherwise.
       */
      const bool _initializeGlew();
      /**
       * Initializes OpenGL settings for the window.
       */
      void _initializeOpenGLSettings();
      /**
       * Initializes the window.
       */
      void _initialize();
      /**
       * Updates the time difference between the current and previous frames.
       */
      void _updateDeltaTime();
      /**
       * Updates the associated camera in the window.
       */
      void _updateCamera();
      /**
       * Updates the window state.
       */
      void _update();
      /**
       * Renders the window state.
       */
      void _render();
  };
}

#endif // KDR_WINDOW_HPP
