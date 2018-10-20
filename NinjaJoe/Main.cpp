#include <SDL.h>
#include <iostream>
#include "Sprite.h"
#include "Player.h"
#include "Bkg.h"
#include "Platform.h"
#include "Sword.h"
#include "Shuriken.h"
#include "NinjaMob.h"
#include <vector>
#include "EnemyManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ScreenText.h"

// function prototypes
void GameLoop(SDL_Window* window, SDL_Renderer* renderer);

int main(int, char**)
{
	//Based on the Sprite Guide template by Peter Allen
	SDL_Window* window;
	SDL_Renderer* renderer;

	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return 0;
	}

	// try to create the window, log error and pause if fail
	window = SDL_CreateWindow("sprite_guide", 100, 100, 800, 700, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// this function call goes into the actual game loop
	GameLoop(window, renderer);

	// clean up, free any memory we have used
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void GameLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	bool quit = false;
	SDL_Event e;

	Player* joe = new Player(renderer, "JoeSprSheet.bmp", 54, 63, 4, 3);
	Bkg* bkg = new Bkg(renderer, "cityBkg.bmp", "CityBkgCollision.bmp", 0, 0, 800, 700);
	Sword* sword = new Sword(renderer, "SwordSprSheet.bmp", 59, 17, 3, 1);
	Shuriken* shuriken = new Shuriken(renderer, "ShurikenSprSheet.bmp", 26, 26, 3, 1);
	EnemyManager* ninjas = new EnemyManager(renderer);
	ScreenText* text = new ScreenText(renderer);

	while (!quit) { // this is the main game loop

		while (SDL_PollEvent(&e)) // allow closing SDL window to quit
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Randomises rand() for usage
		srand(time(NULL));

		//First clear the renderer
		SDL_RenderClear(renderer);

		//Updating classes
		SDL_Rect moveJoe = joe->Update(bkg->GetIsColliding());

		sword->Update(joe->GetX(), joe->GetY(), joe->GetOnCooldown(), joe->GetFacingRight(), 
			joe->GetAttackingRight(), joe->GetAttackingLeft());

		shuriken->Update(joe->GetX(), joe->GetY(), joe->GetOnCooldown(), joe->GetFacingRight(), 
			joe->GetAttackingRight(), joe->GetAttackingLeft());

		ninjas->Update(joe, shuriken, sword);
		text->Update();

		//SDL_Rect scrollAmount = joe->TakeInput();

		
		bkg->CheckCollision(joe, moveJoe);
		joe->Move(moveJoe);

		//Drawing background
		bkg->Draw();

		//Drawing Joe and weapons
		joe->Draw();
		sword->Draw();
		shuriken->Draw();

		//Drawing Ninjas
		ninjas->Draw();

		//Drawing text
		text->Draw();

		//Update the screen
		SDL_RenderPresent(renderer);
	}

	delete joe;
	delete bkg;
	delete sword;
	delete shuriken;

	//Unloading Ninjas
	delete ninjas;

	//Unloading Text
	delete text;
}

