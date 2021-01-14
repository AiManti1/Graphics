#pragma once

#include "OpenGL/Texture2D.h"

class MTL Sprite
{
public:
	Sprite();
	~Sprite();

	// Screen coordinates. VS normalized coords.
	void Init(float _x, float _y, float _width, float _height);

	void DrawSprite();

private:
	float x;
	float y;
	float m_Width;
	float m_Height;

	// 1. Declare VBO. 
	GLuint m_VboID;
};
