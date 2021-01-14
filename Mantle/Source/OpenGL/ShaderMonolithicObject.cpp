#include "mtlpch.h"
#include "OpenGL/ShaderMonolithicObject.h"

ShaderMonolithicObject::ShaderMonolithicObject() :
	m_ProgramID(0),

	m_VertexShaderID(0),
	m_FragmentShaderID(0),
	m_TesselationShader(0),
	m_GeometryShaderID(0),
	m_ComputeShaderID(0),

	m_NumAttributes(0)
{
}

ShaderMonolithicObject::~ShaderMonolithicObject()
{
}
