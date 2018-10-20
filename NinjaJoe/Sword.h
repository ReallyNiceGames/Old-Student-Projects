#pragma once

#include "Sprite.h"

class Sword : public Sprite
{
public:
	Sword(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol);

	void Update(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft);

	void ShowSword(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft);

	void CheckCollision();

	void Draw() override;

	int GetX() { return position.x; }
	int GetY() { return position.y; }
	int GetH() { return position.h; }
	int GetW() { return position.w; }

	bool GetIsShown() { return isShown; }

private:

	SDL_Rect cellRect;

	int cellsInRow;
	int cellsInCol;
	int currentRow;
	int currentCol;

	bool isShown;
	bool isColliding;

	int displayTimer;
};



