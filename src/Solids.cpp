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
  0, 3, 9,    // Front
  0, 9, 6,    // Front
  4, 15, 21,  // Right
  4, 21, 10,  // Right
  16, 12, 18, // Back
  16, 18, 22, // Back
  13, 1, 7,   // Left
  13, 7, 19,  // Left
  8, 11, 23,  // Top
  8, 23, 20,  // Top
  14, 17, 5,  // Bottom
  14, 5, 2,   // Bottom
};

kdr::Solids::Cube::Cube(const kdr::Space::Vec3& position, const float edgeLength) : kdr::Solids::Solid(position)
{
  GLfloat cubeVertices[] = {
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 0  000 FT
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 1  000 LT
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 2  000 BT
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 3  100 FT
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 4  100 RT
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 5  100 BT
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 6  010 FT
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 7  010 LT
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 8  010 TP
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 9  110 FT
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 10 110 RT
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 11 110 TP
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 12 001 BK
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 13 001 LT
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 14 001 BT
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 15 101 RT
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 16 101 BK
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 17 101 BT
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 18 011 BK
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 19 011 LT
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 20 011 TP
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 21 111 RT
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 22 111 BK
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 23 111 TP
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(cubeVertices, sizeof(cubeVertices));
  EBO = new kdr::Graphics::EBO(cubeIndices, sizeof(cubeIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  VAO->LinkAtrib(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

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
  0, 3, 9,    // Front
  0, 9, 6,    // Front
  4, 15, 21,  // Right
  4, 21, 10,  // Right
  16, 12, 18, // Back
  16, 18, 22, // Back
  13, 1, 7,   // Left
  13, 7, 19,  // Left
  8, 11, 23,  // Top
  8, 23, 20,  // Top
  14, 17, 5,  // Bottom
  14, 5, 2,   // Bottom
};

kdr::Solids::Cuboid::Cuboid(const kdr::Space::Vec3& position, const float length, const float height, const float width) : kdr::Solids::Solid(position)
{
  GLfloat cuboidVertices[] = {
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 0  000 FT
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 1  000 LT
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 2  000 BT
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 3  100 FT
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 4  100 RT
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 5  100 BT
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 6  010 FT
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 7  010 LT
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 8  010 TP
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 9  110 FT
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 10 110 RT
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 11 110 TP
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 12 001 BK
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 13 001 LT
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 14 001 BT
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // 15 101 RT
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // 16 101 BK
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 17 101 BT
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 18 011 BK
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 19 011 LT
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 20 011 TP
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 21 111 RT
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // 22 111 BK
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // 23 111 TP
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(cuboidVertices, sizeof(cuboidVertices));
  EBO = new kdr::Graphics::EBO(cuboidIndices, sizeof(cuboidIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  VAO->LinkAtrib(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

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
  6, 9, 3,   // Bottom
  6, 3, 0,   // Bottom
  1, 3, 8,   // Front
  1, 4, 12,  // Front
  5, 11, 12, // Right
  10, 7, 12, // Back
  8, 2, 12,  // Left
};

kdr::Solids::Pyramid::Pyramid(const kdr::Space::Vec3& position, const float edgeLength, const float height) : kdr::Solids::Solid(position)
{
  GLfloat pyramidVertices[] = {
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  1.f, // 0  000 BT
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // 1  000 FT
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // 2  000 LT
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  1.f, // 3  100 BT
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // 4  100 FT
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // 5  100 RT
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // 6  001 BT
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // 7  001 BK
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // 8  001 LT
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // 9  101 BT
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // 10 101 BK
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // 11 101 RT
     0.f,                 (height / 2.f),  0.f,                1.f, 1.f, 1.f, 0.5f, 1.f, // 12 TIP
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(pyramidVertices, sizeof(pyramidVertices));
  EBO = new kdr::Graphics::EBO(pyramidIndices, sizeof(pyramidIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  VAO->LinkAtrib(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

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

GLuint planeIndices[] = {
  0, 1, 3,
  0, 3, 2,
};

kdr::Solids::Plane::Plane(const kdr::Space::Vec3& position, const float length, const float width) : kdr::Solids::Solid(position)
{
  GLfloat planeVertices[] = {
    -(length / 2.f), 0.f,  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,   // 0 000
     (length / 2.f), 0.f,  (width / 2.f), 1.f, 1.f, 1.f, length, 0.f,   // 1 100
    -(length / 2.f), 0.f, -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    width, // 2 001
     (length / 2.f), 0.f, -(width / 2.f), 1.f, 1.f, 1.f, length, width, // 3 101
  };

  VAO = new kdr::Graphics::VAO();
  VBO = new kdr::Graphics::VBO(planeVertices, sizeof(planeVertices));
  EBO = new kdr::Graphics::EBO(planeIndices, sizeof(planeIndices));

  VAO->Bind();
  VBO->Bind();
  EBO->Bind();

  VAO->LinkAtrib(*VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  VAO->LinkAtrib(*VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  VAO->LinkAtrib(*VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  VAO->Unbind();
  VBO->Unbind();
  EBO->Unbind();
}

void kdr::Solids::Plane::Render(const GLuint shaderID)
{
  VAO->Bind();
  _applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  VAO->Unbind();
}
