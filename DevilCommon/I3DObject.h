#pragma once
#include <vector>

typedef float Vertex[3];
typedef float Colorf[3];

struct Mesh
{
	std::vector<Vertex> vertecies;
	std::vector<int> indecies;
	std::vector<Colorf> color;
};

struct I3DObject
{
	virtual bool Init(Mesh *pMesh) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};