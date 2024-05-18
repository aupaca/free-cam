#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Vertex.h"

class Shape;

class World
{
public:
	World();
	~World();
	
	void add(const Shape& object);
	
	std::vector<Vertex>& vertexData();
	std::vector<unsigned>& indexData();
	
private:
	std::vector<Vertex> _vertexList;
	std::vector<unsigned> _indexList;
};

inline std::vector<Vertex>& World::vertexData()
{
	return _vertexList;
}

inline std::vector<unsigned>& World::indexData()
{
	return _indexList;
}

#endif