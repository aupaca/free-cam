#include "World.h"
#include "Shape.h"

World::World()
{
	
}

World::~World()
{
	
}

void World::add(const Shape& object)
{
	int size = _vertexList.size();
	for (unsigned index : object.indexData())
	{
		_indexList.push_back(index + size);
	}
	
	for (const Vertex& v : object.vertexData())
	{
		_vertexList.push_back(v);
	}
}
