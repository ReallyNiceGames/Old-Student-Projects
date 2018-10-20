#include "EnemyManager.h"

EnemyManager::EnemyManager(SDL_Renderer* _renderer)
{
	m_renderer = _renderer;
	m_maxNinjas = 1;
	m_currentNinjas = 0;
	m_wave = 1;
	m_scoreRequired = 3;
}

EnemyManager::~EnemyManager()
{
	for (int i = 0; i < m_ninjaVec.size(); ++i)
	{
		delete m_ninjaVec[i];
	}
}

void EnemyManager::Update(Player* _joe, Shuriken* _shuriken, Sword* _sword)
{
	if (m_currentNinjas < m_maxNinjas)
	{
		for (int i = 0; m_currentNinjas < m_maxNinjas; ++i)
		{
			++m_currentNinjas;
			this->RandomiseSpawn();
			m_ninjaVec.push_back(new NinjaMob(m_renderer, "NinjaMobSprSheet.bmp", 48, 56, 4, 2, randomSpawn[0], randomSpawn[1]));
		}
	}

	for (int i = 0; i < m_ninjaVec.size(); ++i)
	{
		m_ninjaVec[i]->Update(_joe, _shuriken, _sword);

		
		if (m_ninjaVec[i]->GetIsKilled())
		{
			m_ninjaVec.erase(m_ninjaVec.begin() + i);
			_joe->SetScore();
			std::cout << _joe->GetScore() << std::endl;
		}
	}

	//Keep track of the amount of ninjas
	m_currentNinjas = m_ninjaVec.size();

	if (_joe->GetScore() >= m_scoreRequired)
	{
		++m_wave;
		m_scoreRequired *= 2;
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < m_currentNinjas; ++i)
	{
		m_ninjaVec[i]->Draw();
	}
}

void EnemyManager::RandomiseSpawn()
{
	//Spawn locations
	int farLeftSpawn[] = { 50, 60 };
	int farRightSpawn[] = { 700, 60 };
	int middleLeftSpawn[] = { 250, 60 };
	int middleRightSpawn[] = { 500, 60 };

	//Randomises where the Ninja will spawn from four set locations
	switch (rand() % 4)
	{
		case 0:
		{
			randomSpawn[0] = farLeftSpawn[0];
			randomSpawn[1] = farLeftSpawn[1];
			std::cout << "Far left" << std::endl;
			break;
		}

		case 1:
		{
			randomSpawn[0] = farRightSpawn[0];
			randomSpawn[1] = farRightSpawn[1];
			std::cout << "Far right" << std::endl;
			break;
		}

		case 2:
		{
			randomSpawn[0] = middleLeftSpawn[0];
			randomSpawn[1] = middleLeftSpawn[1];
			std::cout << "Middle left" << std::endl;
			break;
		}

		case 3:
		{
			randomSpawn[0] = middleRightSpawn[0];
			randomSpawn[1] = middleRightSpawn[1];
			std::cout << "Middle right" << std::endl;
			break;
		}

		default:
		{
			std::cout << "ERROR LOADING NINJA" << std::endl;
			break;
		}
	}
}