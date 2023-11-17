#include "Kedarium/Graphics.hpp"

kdr::Graphics::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const std::string vertexShaderSource = kdr::File::getContents(vertexPath);
  const std::string fragmentShaderSource = kdr::File::getContents(fragmentPath);

  const char* vertexShaderSourceC = vertexShaderSource.c_str();
  const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Validating the Shaders
  int success {0};
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader (" << vertexPath << ")!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader (" << fragmentPath << ")!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cerr << "Failed to compile the link the shader program!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

kdr::Graphics::VBO::VBO(GLfloat vertices[], GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  Unbind();
}

kdr::Graphics::EBO::EBO(GLuint indices[], GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  Unbind();
}

void kdr::Graphics::VAO::LinkAtrib(kdr::Graphics::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset)
{
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
}
