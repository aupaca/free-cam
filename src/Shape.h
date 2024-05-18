#ifndef SHAPE_H
#define SHAPE_H
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

class Shape
{
public:
	Shape(std::vector<unsigned>& indexCache);
	virtual ~Shape();
	
	const std::vector<Vertex>& vertexData() const;
	const std::vector<unsigned>& indexData() const;
	const glm::vec3& position() const;
	
	void position(const glm::vec3& destiny);
	void move(const glm::vec3& displacement);
	
protected:
	std::vector<Vertex> _vertices;
	std::vector<unsigned>& _indicesRef;
	glm::vec3 _position;
};

inline const std::vector<Vertex>& Shape::vertexData() const
{
	return _vertices;
}

inline const std::vector<unsigned>& Shape::indexData() const
{
	return _indicesRef;
}

inline const glm::vec3& Shape::position() const
{
	return _position;
}


class Box : public Shape
{
public:
	Box(const glm::vec3& dimensions);
	
private:
	void buildIndices();
	
	static std::vector<unsigned> _boxIndices;
};


class Pyramid : public Shape
{
public:
	Pyramid(const glm::vec3& dimensions);
	
private:
	void buildIndices();
	
	static std::vector<unsigned> _pyramidIndices;
};

#endif
