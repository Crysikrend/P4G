#ifndef TILE_H
#define TILE_H

#include <vector>
#include <future>

#include "Mesh.h"
#include "Model.h"
#include "FX.h"
#include "D3D.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//wrap up common behaviors, initialization+shutdown
class Tile
{
public:

	enum TileType
	{
		eEmpty, eBasic, ePickup
	};

	//start up and shut down
	Tile(const TileType& type, int x, int y, float width, float pad, const Vector3& anch, bool isHidden = false, bool isTraverseable = false) 
		:tileType(type), cellX(x), cellY(y), cellWidth(width), padding(pad), anchor(anch), hidden(isHidden), traverseable(isTraverseable) {}

	~Tile() {
		Release();
	}	
	
	//game logic, called constantly, elapsed time passed in
	virtual void Update(float dTime);

	//render images, called constantly, elapsed time passed in
	virtual void Render(float dTime, float zAdjust = 0, bool setInsteadOfAdd = false);

	//called when ALT+ENTER or drag
	void OnResize(int screenWidth, int screenHeight);
	virtual void Initialise(Mesh& tileMesh);
	virtual void Release();

	// Function to call when you wish to remove the tile from play
	virtual void killTile();

	//game models that reference meshes
	Model tile;

	//handy rendering state
	FX::MyFX mFX;

	// getters & setters
	int getCellX();
	int getCellY();

	Vector3 getAnchor();
	Vector3 getPosition();

	Vector3 getDisplacement();
	void addDisplacement(const Vector3& disp);
	void resetDisplacement();

	TileType getTileType();
	bool getHidden() const;
	bool getChecked() const;
	virtual bool getCollected() const;
	void setHidden(bool b);
	void setChecked(bool b);
	bool getTraverseable() const;
	void setTraverseable(bool b);

	float getPadding();
	float getCellWidth();

	// movement functions
	virtual bool bump();
	virtual void moveOn();
	virtual void moveOff();

	//return if tile is collected
	
	

private:

	const TileType tileType;
	bool traverseable;
	bool checked_;
	// attributes for positioning
	const int cellX;
	const int cellY;
	const float cellWidth;
	float padding;
	const Vector3 anchor;

	// vector for displacing the tile
	Vector3 adjustVector;

	// visibility of the tile
	bool hidden;
};

#endif




