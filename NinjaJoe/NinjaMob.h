#pragma once

#include "Sprite.h"
#include "Shuriken.h"
#include "Sword.h"
#include "Player.h"
#include <iostream>

class NinjaMob : public Sprite
{
public:
	NinjaMob(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol, int _x, int _y);

	void Draw() override;

	void Update(Player* _joe, Shuriken* _shuriken, Sword* _sword);

	void AttackPlayer(int _joeX, int _joeY, int _joeFacingRight);

	void CheckCollision(Player* _joe, Shuriken* _shuriken, Sword* _sword);

	void Idle(Shuriken* _shuriken);

	bool GetIsKilled() { return m_isKilled; }

private:

	SDL_Rect cellRect;

	SDL_Texture* shurikenImage;

	SDL_Rect shurikenPosition;

	int cellsInRow;
	int cellsInCol;
	int currentRow;
	int currentCol;

	bool canSeePlayer;
	bool isAttacking;
	bool facingRight;

	int posTracker;
	int speed;
	int left;
	int right;
	int moveDir;
	int animSpeed;
	int animTimer;
	int m_attackPow;

	int gravity;

	bool joeIsLeft;
	bool joeIsRight;

	bool isHit;

	int m_x;
	int m_y;
	bool m_isFalling;
	bool m_isKilled;
	bool m_isCollidingPlayer;
};


