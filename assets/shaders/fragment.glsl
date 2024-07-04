#version 330 core
out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(sin(time), 1.0f, sin(time + 3.14), 1.0f);
}
