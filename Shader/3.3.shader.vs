#version 330 core
layout (location = 0) in vec3 aPos;
uniform float size;
uniform mat4 transform;

void main()
{
   gl_Position = transform * vec4( size * aPos.x, size * aPos.y, size * aPos.z, 1.0f);
}//頂點著色器原碼

