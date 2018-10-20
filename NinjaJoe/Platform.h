#pragma once

#include "Sprite.h"

class Platform : public Sprite
{
public:
	Platform(SDL_Renderer* renderer, char* _file, int _x, int _y, int _w, int _h);

	int GetX() { return position.x; }
	int GetY() { return position.y; }

private:

};


