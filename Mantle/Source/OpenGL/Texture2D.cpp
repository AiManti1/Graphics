#include "mtlpch.h"
#include "OpenGL/Texture2D.h"

// Constructor sets default texture modes.
Texture2D::Texture2D()
	: m_Width(0), m_Height(0), 
	m_Internal_Format(GL_RGB), m_Image_Format(GL_RGB), 
	m_Wrap_S(GL_REPEAT), m_Wrap_T(GL_REPEAT), 
	m_Filter_Min(GL_LINEAR), m_Filter_Max(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture2D::CreateTexture(GLuint width, GLuint height, unsigned char* data)
{
	this->m_Width = width;
	this->m_Height = height;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->m_Internal_Format, width, height, 0, this->m_Image_Format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_Max);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}