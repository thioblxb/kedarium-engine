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

void kdr::Solids::Solid::_applyPosition(const GLuint shaderID)
{
  kdr::Space::Mat4 model {1.f};
  model = kdr::Space::translate(model, position);
  GLuint modelLoc = glGetUniformLocation(shaderID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
}

GLuint cubeIndices[] = {
  0, 1, 3, // Front
  0, 3, 2, // Front
  1, 5, 7, // Right
  1, 7, 3, // Right
  5, 4, 6, // Back
  5, 6, 7, // Back
  4, 0, 2, // Left
  4, 2, 6, // Left
  2, 3, 7, // Top
  2, 7, 6, // Top
  4, 5, 1, // Bottom
  4, 1, 0, // Bottom
};

kdr::Solids::Cube::Cube(const kdr::Space::Vec3& position, const float edgeLength) : kdr::Solids::Solid(position)
{
  GLfloat cubeVertices[] = {
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
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

void kdr::Solids::Cube::Render(const GLuint shaderID)
{
  VAO->Bind();
  _applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  VAO->Unbind();
}

GLuint cuboidIndices[] = {
  0, 1, 3, // Front
  0, 3, 2, // Front
  1, 5, 7, // Right
  1, 7, 3, // Right
  5, 4, 6, // Back
  5, 6, 7, // Back
  4, 0, 2, // Left
  4, 2, 6, // Left
  2, 3, 7, // Top
  2, 7, 6, // Top
  4, 5, 1, // Bottom
  4, 1, 0, // Bottom
};

kdr::Solids::Cuboid::Cuboid(const kdr::Space::Vec3& position, const float length, const float height, const float width) : kdr::Solids::Solid(position)
{
  GLfloat cuboidVertices[] = {
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f,
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f,
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f,
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f,
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f,
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f,
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f,
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f,
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(cuboidVertices, sizeof(cuboidVertices));
  EBO = new kdr::Graphics::EBO(cuboidIndices, sizeof(cuboidIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO->Unbind();
  VBO->Unbind();
  EBO->Unbind();
}

void kdr::Solids::Cuboid::Render(const GLuint shaderID)
{
  VAO->Bind();
  _applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  VAO->Unbind();
}

GLuint pyramidIndices[] = {
  2, 3, 1, // Bottom
  2, 1, 0, // Bottom
  0, 1, 4, // Front
  1, 3, 4, // Right
  3, 2, 4, // Back
  2, 0, 4, // Left
};

kdr::Solids::Pyramid::Pyramid(const kdr::Space::Vec3& position, const float edgeLength, const float height) : kdr::Solids::Solid(position)
{
  GLfloat pyramidVertices[] = {
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f,
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f,
     0.f,                 (height / 2.f),  0.f,                1.f, 1.f, 1.f,
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(pyramidVertices, sizeof(pyramidVertices));
  EBO = new kdr::Graphics::EBO(pyramidIndices, sizeof(pyramidIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO->Unbind();
  VBO->Unbind();
  EBO->Unbind();
}

void kdr::Solids::Pyramid::Render(const GLuint shaderID)
{
  VAO->Bind();
  _applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  VAO->Unbind();
}
