#ifndef GRID_H
#define GRID_H

#include <vector>
#include <future>

#include "Mesh.h"
#include "Model.h"
#include "Tile.h"
#include "FX.h"

//wrap up common behaviors, initialization+shutdown
class Grid
{
public:
	//start up and shut down
	Grid() 
	{}
	~Grid() {
		Release();
	}
	//game logic, called constantly, elapsed time passed in
	void Update(float dTime);

	//render images, called constantly, elapsed time passed in
	void Render(float dTime);

	//called when ALT+ENTER or drag
	void OnResize(int screenWidth, int screenHeight);
	void Initialise();
	void Release();

	//ensure each mesh is loaded and release exactly once
	MeshManager mMeshMgr;

	//game models that reference meshes
	//Model mCube;

	//handy rendering state
	FX::MyFX mFX;

private:

	float tilePadding;
	float tileWidth;

	// Array of tiles
	//Tile tileArray[10][10];
	vector<vector<Tile>> tileArray;

};

#endif




