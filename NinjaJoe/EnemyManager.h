#pragma once

#include "NinjaMob.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Player.h"

class EnemyManager
{
public:
	EnemyManager(SDL_Renderer* _renderer);
	~EnemyManager();

	void Update(Player* _joe, Shuriken* _shuriken, Sword* _sword);

	void Draw();

	void RandomiseSpawn();

private:

	int m_maxNinjas;
	int m_currentNinjas;
	std::vector<NinjaMob*> m_ninjaVec;
	SDL_Renderer* m_renderer;
	int randomSpawn[2];
	int m_wave;
	int m_scoreRequired;
};

