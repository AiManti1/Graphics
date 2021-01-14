#pragma once
#include "Glad/glad.h"

class MTL ShaderMonolithicObject
{
public:
	ShaderMonolithicObject();
	virtual ~ShaderMonolithicObject();

	// 1. Read a shader from file and compile shaders for GPU.
	void CompileShaders(
		const std::string& vertexShaderFilePath,
		const std::string& fragmentShaderFilePath,
		const std::string& tesselationShaderFilePath = nullptr,
		const std::string& geometryShaderFilePath = nullptr,
		const std::string& computeShaderFilePath = nullptr
	);

	void LinkShader();

	// 2. Automatically add attribute to the next free attribute slot. Like "Vertext position" inside the vertex shader.
	// The order in which we add an attribute is important.
	void AddAttribute(const std::string& attributeName);

	// 3. Make use of Shader program, and not only one program at a time.
	void UseShaderMonolithicObject();
	void UnuseShaderMonolithicObject();

	virtual void InitShaders() = 0;

	// 4. Uniform
	GLuint GetUniformLocation(const std::string& uniformName);

private:
	// 1. Add shaders
	GLuint m_ProgramID;

	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
	GLuint m_TesselationShader;
	GLuint m_GeometryShaderID;
	GLuint m_ComputeShaderID;

	void CompileShader(const std::string& filePath, GLuint id);

	// 2. Add attributes to count. For positions, color, textures to a vertext shader.
	int m_NumAttributes;
};