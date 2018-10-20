#pragma once
#include "Sprite.h"
#include "Player.h"
#include <vector>

class Bkg
{
public:
	Bkg(SDL_Renderer* _renderer, char* _imagefile, char* _collisionMapFile, int _x, int _y, int _w, int _h);
	~Bkg();

	void CheckCollision(Player* player, SDL_Rect& move);
	void Draw();

	bool GetIsColliding() { return isColliding; }

private:

	Sprite* image;
	Sprite* collisionMap; // collision image that this bkg uses

	void ReadCollisionImage(char* _collisionMapFile);

	std::vector<SDL_Color> collisionPixels; // store the collision pixel data in here
	SDL_Rect collisionSize;					// size of collision map
	bool showCollisionMap;

	float x;
	float y;
	int w;
	int h;

	bool isColliding;
};