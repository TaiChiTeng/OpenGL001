#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// out vec3 ourColor;
out vec3 ourPosition;

void main()
{
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0); 
    // ourColor = aColor;
    // ourPosition = aPos;
    ourPosition = vec3(aPos.x, -aPos.y, aPos.z);
}
