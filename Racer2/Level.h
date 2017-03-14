#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "TileFloor.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//wrap up common behaviors, initialization+shutdown
class Level
{
public:
	//start up and shut down
	Level(const MeshManager& meshMGR, const Vector3& anch, const float width)
		: mMeshMgr(meshMGR), anchorPos(anch), tileWidth(width)
	{
		Load(meshMGR);
	}

	~Level() {
		Release();
	}

	//game logic, called constantly, elapsed time passed in
	void Update(float dTime);

	//render images, called constantly, elapsed time passed in
	void Render(float dTime);

	//called when ALT+ENTER or drag
	void OnResize(int screenWidth, int screenHeight);

	// Called everytime a new level is created
	void Initialise(const vector<vector<Tile::TileType>>& layout, float padding = 1.25, int dim = 10);

	void Release();

	//handy rendering state
	FX::MyFX mFX;

private:
	const Vector3 anchorPos;
	const float tileWidth;

	int cellDim;
	float tilePadding;

	float waveEffect;
	bool waveLevel;

	// Arrays of tile pointers
	vector<vector<TileFloor*>> floor;
	vector<vector<Tile*>> level;

	//ensure each mesh is loaded and release exactly once
	MeshManager mMeshMgr;
	//vector<Mesh> meshArray;


	// Load all the meshes required to build a level
	void Load(MeshManager meshMGR);

	Tile* createTile(const Tile::TileType& type, int x, int y, float width, float pad, const Vector3& anch);
	TileFloor* createFloorTile(const Tile::TileType& type, int x, int y, float width, float pad, const Vector3& anch);


};

#endif



