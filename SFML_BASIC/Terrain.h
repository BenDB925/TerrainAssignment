#pragma once
#include <SFML\Graphics\Texture.hpp>
class Terrain
{
	//size of the mesh forming the terrain
	int gridWidth,gridDepth;
	int numVerts;
	//size of the terrain in world_coords
	float terrWidth,terrDepth;

	typedef  GLfloat vector[3];
	//array of vertices for the grid(this will be a triangle list)
	//I know, very inefficient, but let's run before we walk
	vector *vertices;
	vector *colors;


	typedef GLfloat texCoords[2];
	texCoords * textureCoords;

	float getHeight(float x, float y);
	void setPoint(vector, float, float, float);
	void setPointText(vector, float, float);
	
public:
	Terrain(void);
	~Terrain(void);

	void Init();
	void Draw();
};

