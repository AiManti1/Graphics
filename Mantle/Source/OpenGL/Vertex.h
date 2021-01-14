#pragma once
#include "Glad/glad.h"

struct Position
{
	float x;
	float y;
};

struct Color
{
	// GLubyte = unsigned char = [0-255] like in "Paint".
	// 4 bytes for r g b a color.
	GLubyte r;		
	GLubyte g;
	GLubyte b;
	GLubyte a;
};


struct Vertex
{
	Position position;
	Color color;
};
