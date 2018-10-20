#pragma once

#include "Sprite.h"

class Shuriken : public Sprite
{
public:
	Shuriken(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol);

	void Draw() override;

	void Update(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft);

	void ThrowShuriken(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft);

	void CheckCollision();

	int GetX() { return position.x; }
	int GetY() { return position.y; }
	int GetH() { return position.h; }
	int GetW() { return position.w; }
	bool GetIsShown() { return isShown; }
	void SetIsShown() { isShown = false; }

private:

	SDL_Rect cellRect;

	int cellsInRow;
	int cellsInCol;
	int currentRow;
	int currentCol;

	bool isShown;
	bool isColliding;
	bool isThrown;

	int throwDir;
	int left;
	int right;
	int throwSpeed;
};



