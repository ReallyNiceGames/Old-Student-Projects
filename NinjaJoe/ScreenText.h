#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class ScreenText
{
public:
	ScreenText(SDL_Renderer* _renderer);
	~ScreenText();

	void Update();

	void Draw();

private:

	SDL_Renderer* renderer;
	SDL_Rect messageRect;
	SDL_Texture* message;
	SDL_Surface* surfaceMessage;
	SDL_Color black;
};

