#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform vec3 offset;
void main()
{
    vec3 position = vertexPosition_modelspace + offset;
    gl_Position = vec4(position, 1);
}