#include "Kedarium/Solids.hpp"

kdr::Solids::Solid::~Solid()
{
  VAO->Delete();
  VBO->Delete();
  EBO->Delete();

  delete VAO;
  delete VBO;
  delete EBO;
}

GLuint cubeIndices[] = {
  1, 0, 3, // Front
  2, 3, 0, // Front
  5, 1, 7, // Right
  3, 7, 1, // Right
  5, 4, 7, // Back
  6, 7, 4, // Back
  0, 4, 2, // Left
  6, 2, 4, // Left
  3, 2, 7, // Top
  6, 7, 2, // Top
  4, 5, 0, // Bottom
  1, 0, 5, // Bottom
};

kdr::Solids::Cube::Cube(const kdr::Space::Vec3& position, const float edgeLength) : kdr::Solids::Solid(position)
{
  GLfloat cubeVertices[] = {
    -0.5f, -0.5f,  0.5f, 1.f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f, 0.f, 1.f, 0.f,
    -0.5f,  0.5f,  0.5f, 0.f, 0.f, 1.f,
     0.5f,  0.5f,  0.5f, 1.f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f, 1.f, 0.f, 1.f,
    -0.5f,  0.5f, -0.5f, 1.f, 0.f, 0.f,
     0.5f,  0.5f, -0.5f, 0.f, 1.f, 0.f,
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(cubeVertices, sizeof(cubeVertices));
  EBO = new kdr::Graphics::EBO(cubeIndices, sizeof(cubeIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO->Unbind();
  VBO->Unbind();
  EBO->Unbind();
}

void kdr::Solids::Cube::Render()
{
  VAO->Bind();
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  VAO->Unbind();
}
