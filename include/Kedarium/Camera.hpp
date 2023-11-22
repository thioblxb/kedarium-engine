#ifndef KDR_CAMERA_HPP
#define KDR_CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Keys.hpp"
#include "Space.hpp"

namespace kdr
{
  struct CameraProps
  {
    float fov;
    float aspect;
    float near;
    float far;
    float speed;
    float sensitivity;

    CameraProps(
      const float fov,
      const float aspect,
      const float near,
      const float far,
      const float speed,
      const float sensitivity
    ) : fov(fov), aspect(aspect), near(near), far(far), speed(speed), sensitivity(sensitivity)
    {}
  };

  class Camera
  {
    public:
      /**
       * Constructs a camera with provided camera properties.
       *
       * @param cameraProps Camera properties including fov, aspect, near, far, speed, and sensitivity.
       */
      Camera(const kdr::CameraProps& cameraProps)
      : fov(cameraProps.fov), aspect(cameraProps.aspect), near(cameraProps.near), far(cameraProps.far), speed(cameraProps.speed), sensitivity(cameraProps.sensitivity)
      {}

      /**
       * Retrieves the position of the camera in 3D space.
       *
       * @return The position of the camera.
       */
      const kdr::Space::Vec3 getPosition() const
      { return this->position; }
       /**
       * Retrieves the transformation matrix of the camera.
       *
       * @return The transformation matrix of the camera.
       */
      const kdr::Space::Mat4 getMatrix() const
      { return this->matrix; }
      /**
       * Retrieves the field of view of the camera.
       *
       * @return The field of view of the camera.
       */
      const float getFov() const
      { return this->fov; }
      /**
       * Retrieves the aspect ratio of the camera.
       *
       * @return The aspect ratio of the camera.
       */
      const float getAspect() const
      { return this->aspect; }
      /**
       * Retrieves the near plane distance of the camera.
       *
       * @return The near plane distance of the camera.
       */
      const float getNear() const
      { return this->near; }
      /**
       * Retrieves the far plane distance of the camera.
       *
       * @return The far plane distance of the camera.
       */
      const float getFar() const
      { return this->far; }
      /**
       * Retrieves the movement speed of the camera.
       *
       * @return The movement speed of the camera.
       */
      const float getSpeed() const
      { return this->speed; }
      /**
       * Retrieves the sensitivity of the camera's movement.
       *
       * @return The sensitivity of the camera's movement.
       */
      const float getSensitivity() const
      { return this->sensitivity; }
      /**
       * Retrieves the lock state of the camera's cursor.
       *
       * @return True if the cursor is locked, false otherwise.
       */
      const bool getIsCursorLocked() const
      { return this->isCursorLocked; }

      /**
     * Sets the aspect ratio of the camera.
     *
     * @param aspect New aspect ratio for the camera.
     */
      void setAspect(const float aspect)
      { this->aspect = aspect; }
      /**
       * Sets the lock state of the camera's cursor.
       *
       * @param locked True to lock the cursor, false to unlock.
       */
      void setIsCursorLocked(const bool locked)
      { this->isCursorLocked = locked; }

      /**
       * Handles camera movement based on input from a GLFW window.
       *
       * @param window The GLFW window providing input for camera movement.
       * @param deltaTime The time elapsed between the current and previous frame.
        */
      void handleMovement(GLFWwindow* window, const float deltaTime);
      /**
       * Updates the camera matrix based on its position and properties.
       */
      void updateMatrix();
      /**
       * Applies the camera matrix to a shader uniform.
       *
       * @param shaderID The ID of the shader program.
       * @param uniformName The name of the uniform variable in the shader.
       */
      void applyMatrix(const GLuint shaderID, const std::string& uniformName);

    private:
      kdr::Space::Vec3 position {0.f, 0.f,  3.f};
      kdr::Space::Vec3 front    {0.f, 0.f, -1.f};
      kdr::Space::Vec3 up       {0.f, 1.f,  0.f};
      kdr::Space::Mat4 matrix   {1.f};

      float fov         {60.f};
      float aspect      {1.f};
      float near        {0.1f};
      float far         {100.f};
      float speed       {3.f};
      float sensitivity {24.f};

      float yaw   {-90.f};
      float pitch {0.f};

      bool isCursorLocked {false};
      /**
       * Updates the cursor state based on the lock status.
       *
       * @param window The GLFW window to update the cursor for.
       */
      void _updateCursor(GLFWwindow* window);
  };
}

#endif // KDR_CAMERA_HPP
