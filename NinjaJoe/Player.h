#pragma once

#include "Sprite.h"

class Player : public Sprite
{
public:

	Player(SDL_Renderer* renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol);

	SDL_Rect Update(bool _isCollidingPlatform);

	void CheckLife();

	void CheckCollision(bool _isCollidingPlatform);

	SDL_Rect TakeInput(bool _isCollidingPlatform);

	void Move(SDL_Rect& _move);

	void CheckCooldown();

	void Draw() override;

	void Animate(bool _isCollidingPlatform);

	void CurrentPose();

	int GetY() { return position.y; }
	int GetX() { return position.x; }
	int GetH() { return position.h; }
	int GetW() { return position.w; }
	char GetLastPressed() { return lastPressed; }
	bool GetFacingRight() { return facingRight; }
	bool GetIsJumping() { return isJumping; }
	bool GetOnCooldown() { return onCooldown; }

	bool GetStandingRight() { return isStandingRight; }
	bool GetStandingLeft() { return isStandingLeft; }
	bool GetJumpingRight() { return isJumpingRight; }
	bool GetJumpingLeft() { return isJumpingLeft; }
	bool GetAttackingRight() { return isAttackingRight; }
	bool GetAttackingLeft() { return isAttackingLeft; }

	void SetScore() { ++m_score; }
	int GetScore() { return m_score; }

	void SetLife(int _attackPow) { m_hp -= _attackPow; }
	int GetLife() { return m_hp; }

private:

	SDL_Rect move;
	int m_hp;
	int speed;
	int jumpHeight;
	int m_score;

	//Keeps track of Joe being off the ground, but it
	//doesn't care which way he's facing
	bool isJumping;

	int jumpLooper;
	int gravity;

	SDL_Rect cellRect;

	int cellsInRow;
	int cellsInCol;
	int currentRow;
	int currentCol;

	char lastPressed;
	int animTimer;

	//Keeps track of when Joe is facing left or right but it doesn't
	//care about which pose Joe is specifically in
	bool facingRight;

	int cooldownTimer;
	bool onCooldown;
	bool isStandingRight;
	bool isStandingLeft;
	bool isJumpingRight;
	bool isJumpingLeft;
	bool isAttackingRight;
	bool isAttackingLeft;
	bool isFalling;

};