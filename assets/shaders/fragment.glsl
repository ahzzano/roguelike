#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform float time;
uniform sampler2D ourTexture;

void main()
{
    // FragColor = vec4(sin(time), 1.0f, sin(time + 3.14), 1.0f);
    FragColor = texture(ourTexture, TexCoord);
}
