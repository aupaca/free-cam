#include "Shape.h"
#include <glm/gtc/matrix_transform.hpp>

Shape::Shape(std::vector<unsigned>& indexCache)
	: _indicesRef(indexCache)
{
	_position = glm::vec3(0.f);
}

Shape::~Shape()
{
	
}

void Shape::position(const glm::vec3& destiny)
{
	glm::vec3 direction = destiny - _position;
	_position = destiny;
	for (Vertex& v : _vertices)
	{
		v.pos += direction;
	}
}

void Shape::move(const glm::vec3& displacement)
{
	_position += displacement;
	for (Vertex& v : _vertices)
	{
		v.pos += displacement;
	}
}


// BOX

std::vector<unsigned> Box::_boxIndices;

Box::Box(const glm::vec3& dimensions)
	: Shape(_boxIndices)
{
	const glm::vec4 colors[] =
	{
		{0.90f, 0.90f, 0.98f, 1.f},
		{0.94f, 0.50f, 0.50f, 1.f},
		{0.60f, 0.98f, 0.60f, 1.f}
	};
	
	Vertex v;
	v.pos = dimensions / 2.f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v.color = colors[0];
			_vertices.push_back(v);
			v.color = colors[1];
			_vertices.push_back(v);
			v.color = colors[2];
			_vertices.push_back(v);
			
			v.pos[j % 2] *= -1;
		}
		v.pos.z *= -1;
	}
	
	if (_boxIndices.empty())
	{
		buildIndices();
	}
}

void Box::buildIndices()
{
	_boxIndices = std::vector<unsigned>({
		// front 
		0, 9, 6,
		0, 6, 3,
		
		// back
		12, 21, 18,
		12, 18, 15,
		
		// right
		13, 22, 10,
		13, 1, 10,
		
		// left
		16, 4, 7,
		16, 19, 7,
		
		// top
		14, 2, 5,
		14, 17, 5,
		
		// bottom
		23, 11, 8, 
		23, 20, 8
	});
}


// PYRAMID

std::vector<unsigned> Pyramid::_pyramidIndices;

Pyramid::Pyramid(const glm::vec3& dimensions)
	: Shape(_pyramidIndices)
{
	const glm::vec4 colors[] =
	{
		{0.90f, 0.90f, 0.98f, 1.f},
		{0.94f, 0.50f, 0.50f, 1.f},
		{0.60f, 0.98f, 0.60f, 1.f}
	};
	
	glm::vec3 halfDimensions = dimensions / 2.f;
	
	Vertex v;
	v.pos = glm::vec3(0.f, halfDimensions.y, 0.f);
	v.color = colors[0];
	_vertices.push_back(v);
	v.color = colors[1];
	_vertices.push_back(v);
	
	v.pos = glm::vec3(halfDimensions.x, -halfDimensions.y, halfDimensions.z);
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			v.color = colors[0];
			_vertices.push_back(v);
			v.color = colors[1];
			_vertices.push_back(v);
			v.color = colors[2];
			_vertices.push_back(v);
			
			v.pos.x *= -1;
		}
		v.pos.z *= -1;
	}
	
	if (_pyramidIndices.empty())
	{
		buildIndices();
	}
}

void Pyramid::buildIndices()
{
	_pyramidIndices = std::vector<unsigned>({
		// front
		0, 2, 5,
		// back
		0, 8, 11,
		// left
		1, 6, 12,
		// right
		1, 3, 9,
		// bottom
		10, 4, 7,
		10, 13, 7
	});
}
