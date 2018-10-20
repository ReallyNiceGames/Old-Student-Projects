#pragma once

#include <SDL.h>

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, char* _file, int _x, int _y, int _w, int _h);
	~Sprite();

	virtual void Draw();

	void SetX(int _x) { position.x = _x; }
	void SetY(int _y) { position.y = _y; }

protected:

	SDL_Renderer* renderer;
	SDL_Texture* image;

	SDL_Rect position;

};