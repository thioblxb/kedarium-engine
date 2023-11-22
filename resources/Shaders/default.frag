
#version 330 core

in vec3 vertCol;
in vec2 vertTex;

uniform sampler2D tex0;

out vec4 FragColor;

void main()
{
  FragColor = texture(tex0, vertTex) * vec4(vertCol, 1.f);
}
