#version 330 core
layout (location = 0) in vec3 vertexPos; // the position variable has attribute position 0
layout (location = 1) in vec3 vertexColor;

out vec4 colorFrag; // specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(Pos, 1.0); // see how we directly give a vec3 to vec4's constructor
    colorFrag = vertexColor; // set the output variable to a color
}