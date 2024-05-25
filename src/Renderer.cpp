#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(const char* vertShaderPath, const char* fragShaderPath)
	: _vertexArray(GL_ARRAY_BUFFER), _indexArray(GL_ELEMENT_ARRAY_BUFFER)
{
	if (!_glsl.compile(vertShaderPath, fragShaderPath))
	{
		// TODO: throw error
		return;
	}
	
	_shader = _glsl.shaderId();
	_shader.use();
	
	_indexCount = 0;
	_layout.indexBuffer(_indexArray);
	_layout.vertexBuffer(0, _vertexArray, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	_layout.vertexBuffer(1, _vertexArray, 4, GL_FLOAT, false, sizeof(Vertex), sizeof(glm::vec3));

 glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
 glFrontFace(GL_CW);
 glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
	
}

void Renderer::loadData(const std::vector<Vertex>& vertexList, const std::vector<unsigned>& indexList)
{
	_indexCount = indexList.size();
	_vertexArray.alloc(vertexList.size() * sizeof(Vertex), GL_STATIC_DRAW, vertexList.data());
	_indexArray.alloc(_indexCount * sizeof(unsigned), GL_STATIC_DRAW, indexList.data());
}

void Renderer::setUniform(const char* name, const glm::mat4& value)
{
	glUniformMatrix4fv(_shader.uniform(name), 1, false, glm::value_ptr(value));
}

void Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_layout.drawIndexed(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT);
}

