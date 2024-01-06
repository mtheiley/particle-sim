#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform vec3 offset;
uniform vec3 colour;
out vec3 fragmentColour;
void main()
{
    vec3 position = vertexPosition_modelspace + offset;
    fragmentColour = colour;
    gl_Position = vec4(position, 1);
}