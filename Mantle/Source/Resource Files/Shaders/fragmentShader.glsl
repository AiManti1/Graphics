#version 330 core
out vec4 finalColor;
  
in vec4 colorFrag; // the input variable from the vertex shader (same name and same type)  

uniform float time;

void main()
{
    finalColor = vec4 (colorFrag, 1.0f);
}

/*
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 outColor;\n"
"uniform vec4 unfColor;\n"
"void main()\n"
"{\n"
"outColor = unfColor;\n"
"}\n\0";

*/