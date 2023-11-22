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
    }

    void setup()
    {
      boxTexture.TextureUnit(defaultShader, "tex0", 0);
      coneTexture.TextureUnit(defaultShader, "tex0", 0);
      nukeTexture.TextureUnit(defaultShader, "tex0", 0);

      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          kdr::Solids::Cube* cube = new kdr::Solids::Cube(
            {(x - 1) * 2.f, -2.f, (z - 1) * 2.f},
            1.f
          );
          cubes.push_back(cube);
        }
      }
      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          kdr::Solids::Cuboid* cuboid = new kdr::Solids::Cuboid(
            {(x - 1) * 4.f, 0.f, (z - 1) * 2.f},
            2.f,
            1.f,
            1.f
          );
          cuboids.push_back(cuboid);
        }
      }
      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          kdr::Solids::Pyramid* pyramid = new kdr::Solids::Pyramid(
            {(x - 1) * 2.f, 2.f, (z - 1) * 2.f},
            0.5f,
            1.f
          );
          pyramids.push_back(pyramid);
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

      nukeTexture.Bind();
      for (kdr::Solids::Cube* cube : cubes)
      {
        cube->Render(defaultShader.getID());
      }
      boxTexture.Bind();
      for (kdr::Solids::Cuboid* cuboid : cuboids)
      {
        cuboid->Render(defaultShader.getID());
      }
      coneTexture.Bind();
      for (kdr::Solids::Pyramid* pyramid : pyramids)
      {
        pyramid->Render(defaultShader.getID());
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
    kdr::Graphics::Texture coneTexture {
      "resources/Textures/cone.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::Graphics::Texture nukeTexture {
      "resources/Textures/nuke.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    std::vector<kdr::Solids::Cube*> cubes;
    std::vector<kdr::Solids::Cuboid*> cuboids;
    std::vector<kdr::Solids::Pyramid*> pyramids;

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
