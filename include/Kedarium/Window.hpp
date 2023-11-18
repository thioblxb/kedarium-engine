#ifndef KDR_WINDOW_HPP
#define KDR_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

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

    private:
      GLFWwindow* glfwWindow {NULL};

      unsigned int width  {800};
      unsigned int height {600};
      std::string  title  {"Kedarium Engine"};

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
       * Initializes the window.
       */
      void _initialize();
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
