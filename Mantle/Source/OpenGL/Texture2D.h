#pragma once

#include "Glad/glad.h"

class MTL Texture2D
{
public:
	Texture2D();
	~Texture2D();

private:
	// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture.
	GLuint ID;
	// Texture image dimensions.
	GLuint m_Width, m_Height;		// Width and height of loaded image in pixels
									// Texture Format
	GLuint m_Internal_Format;		// Format of texture object
	GLuint m_Image_Format;			// Format of loaded image
									// Texture configuration
	GLuint m_Wrap_S;				// Wrapping mode on S axis
	GLuint m_Wrap_T;				// Wrapping mode on T axis
	GLuint m_Filter_Min;			// Filtering mode if texture pixels < screen pixels
	GLuint m_Filter_Max;			// Filtering mode if texture pixels > screen pixels

	// Generates texture from image data.
	void CreateTexture(GLuint width, GLuint height, unsigned char* data);
	// Binds the texture as the current active GL_TEXTURE_2D texture object.
	void Bind() const;	
};
