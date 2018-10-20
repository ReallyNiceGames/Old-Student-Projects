#include "ScreenText.h"
#include <string>
#include <fstream>
#include <SDL_ttf.h>

ScreenText::ScreenText(SDL_Renderer* _renderer)
{
	renderer = _renderer;

	messageRect.x = 200;  
	messageRect.y = 200; 
	messageRect.w = 100; 
	messageRect.h = 100;
}

ScreenText::~ScreenText()
{
	if (message)
	{
		SDL_DestroyTexture(message);
	}
}

void ScreenText::Update()
{
	//Found from: http://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
	TTF_Font* sans = TTF_OpenFont("arial.ttf", 24);
	black = { 0, 0, 0 };
	surfaceMessage = TTF_RenderText_Solid(sans, "Hello world", black);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	//std::ofstream out("test");
	
}

void ScreenText::Draw()
{
	if (message)
	{
		SDL_RenderCopy(renderer, message, NULL, &messageRect);
	}
}