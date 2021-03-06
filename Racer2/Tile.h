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
		eEmpty, eBasic, eStart, eEnder, ePikup, eInviW, eFakeW
	};

	//start up and shut down
	Tile(FX::MyFX&(fxRef), const TileType& type, int x, int y, float width, float pad, const Vector3& anch, int gridDim, bool isHidden = false, bool isTraverseable = false) 
		:mFX(&fxRef), tileType(type), cellX(x), cellY(y), cellWidth(width), padding(pad), anchor(anch), gridDimensions(gridDim), hidden(isHidden), traverseable(isTraverseable) {}

	~Tile() {
		Release();
	}	
	
	//game logic, called constantly, elapsed time passed in
	virtual void Update(float dTime, float newPadding = -1);

	//render images, called constantly, elapsed time passed in
	virtual void Render(float dTime, float zAdjust = 0, bool setInsteadOfAdd = false, bool matAlreadySet = false);

	//called when ALT+ENTER or drag
	void OnResize(int screenWidth, int screenHeight);
	virtual void Initialise(Mesh& tileMesh);
	virtual void Release();

	//game models that reference meshes
	Model tile;

	//handy rendering state
	FX::MyFX* mFX;

	// getters & setters
	int getCellX();
	int getCellY();
	int getDim();

	Vector3 getAnchor();
	virtual Vector3 getPosition();

	Vector3 getDisplacement();
	void addDisplacement(const Vector3& disp);
	void resetDisplacement();

	TileType getTileType();
	bool getHidden() const;
	virtual int getInfo(int = 0) ;
	void setHidden(bool b);
	bool getTraverseable() const;
	void setTraverseable(bool b);

	float getPadding();
	float getCellWidth();

	// movement functions
	virtual bool bump();
	virtual void moveOn();
	virtual void moveOff();

	MaterialExt *pMat;
private:
	const TileType tileType;
	bool traverseable;
	// attributes for positioning
	const int cellX;
	const int cellY;
	const float cellWidth;
	float padding;
	const Vector3 anchor;
	const int gridDimensions;

	// vector for displacing the tile
	Vector3 adjustVector;

	// visibility of the tile
	bool hidden;
};

#endif




