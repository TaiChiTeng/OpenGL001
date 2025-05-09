#version 330 core
out vec4 FragColor;
uniform float ourColorY;
void main()
{
    FragColor = vec4(0.0, ourColorY, 0.0, 1.0);
}