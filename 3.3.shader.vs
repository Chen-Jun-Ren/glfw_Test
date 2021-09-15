#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float size;
uniform mat4 transform;

out vec3 ourColor;

void main()
{
   gl_Position = transform * vec4( size * aPos.x, size * aPos.y, size * aPos.z, 1.0f);
   ourColor = aColor;
}//���I�ۦ⾹��X

