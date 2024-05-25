#ifndef RENDERER_H
#define RENDERER_H
#include <ANUT/ANUT_graphics.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	
	void loadData(const std::vector<Vertex>& vertexList, const std::vector<unsigned>& indexList);
	void setUniform(const char* name, const glm::mat4& value);
	void draw();
	
private:
	anut::GLSLCompiler _glsl;
	anut::Shader _shader;
	anut::GPUBuffer _vertexArray;
	anut::GPUBuffer _indexArray;
	anut::VertexLayout _layout;
	int _indexCount;
};

#endif
