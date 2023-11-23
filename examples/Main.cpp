#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

#include "Kedarium/Core.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Space.hpp"
#include "Kedarium/Keys.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Solids.hpp"

// Window Settings
constexpr unsigned int WINDOW_WIDTH  {800};
constexpr unsigned int WINDOW_HEIGHT {600};
const    std::string   WINDOW_TITLE  {"Kedarium Engine"};

// Camera Settings
constexpr float CAMERA_FOV         {60.f};
constexpr float CAMERA_ASPECT      {(float)WINDOW_WIDTH / WINDOW_HEIGHT};
constexpr float CAMERA_NEAR        {0.1f};
constexpr float CAMERA_FAR         {100.f};
constexpr float CAMERA_SPEED       {3.f};
constexpr float CAMERA_SENSITIVITY {24.f};

// Vertices and Indices
GLfloat vertices[] = {
  -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f,
  -0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f,
};
GLuint indices[] = {
  1, 0, 3,
  2, 3, 0,
};

class MainWindow : public kdr::Window
{
  public:
    using kdr::Window::Window;

    ~MainWindow()
    {
      defaultShader.Delete();
      boxTexture.Delete();
      floorTexture.Delete();
    }

    void setup()
    {
      boxTexture.TextureUnit(defaultShader, "tex0", 0);

      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          kdr::Solids::Cube* cube = new kdr::Solids::Cube(
            {(x - 1) * 2.f, 0.5f, (z - 1) * 2.f},
            1.f
          );
          cubes.push_back(cube);
        }
      }
    }

  protected:
    void update()
    {
      if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::E))
      {
        this->getBoundCamera()->setIsCursorLocked(true);
      }
      else if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::Escape))
      {
        this->getBoundCamera()->setIsCursorLocked(false);
      }

      this->getBoundCamera()->handleMovement(getGlfwWindow(), getDeltaTime());

      if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::C))
      {
        kdr::Graphics::usePointMode();
      }
      else if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::V))
      {
        kdr::Graphics::useLineMode();
      }
      else if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::B))
      {
        kdr::Graphics::useFillmode();
      }

      if (kdr::Keys::isPressed(getGlfwWindow(), kdr::Key::F))
      {
        if (canUseFullscreen)
        {
          getIsFullscreenOn()
            ? unmaximize()
            : maximize();
        }
        canUseFullscreen = false;
      }
      else
      {
        canUseFullscreen = true;
      }
    }

    void render()
    {
      bindShader(defaultShader);

      floorTexture.Bind();
      plane.Render(defaultShader.getID());
      boxTexture.Bind();
      for (kdr::Solids::Cube* cube : cubes)
      {
        cube->Render(defaultShader.getID());
      }
    }

  private:
    kdr::Graphics::Shader defaultShader {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    kdr::Graphics::Texture boxTexture {
      "resources/Textures/box.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::Graphics::Texture floorTexture {
      "resources/Textures/floor.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::Solids::Plane plane {
      {0.f, 0.f, 0.f},
      10.f,
      10.f
    };
    std::vector<kdr::Solids::Cube*> cubes;

    bool canUseFullscreen {true};
};

int main()
{
  // Clear Color
  kdr::Color::RGBA clearColor {kdr::Color::Black};
  glClearColor(
    clearColor.red,
    clearColor.green,
    clearColor.blue,
    clearColor.alpha
  );

  // Window
  MainWindow mainWindow {
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE.c_str()
  };

  // Camera
  kdr::Camera mainCamera {{
    CAMERA_FOV,
    CAMERA_ASPECT,
    CAMERA_NEAR,
    CAMERA_FAR,
    CAMERA_SPEED,
    CAMERA_SENSITIVITY
  }};
  mainWindow.setBoundCamera(&mainCamera);

  // Engine and Version Info
  kdr::Core::printEngineInfo();
  std::cout << '\n';
  kdr::Core::printVersionInfo();

  // Main Loop
  mainWindow.setup();
  mainWindow.loop();

  return 0;
}
