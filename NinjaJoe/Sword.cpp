#include "Sword.h"
#include "Player.h"

Sword::Sword(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol) : Sprite(_renderer, _file, 100, 100, _w, _h)
{
	cellsInRow = _cellsInRow;
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 0;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	isColliding = false;
	isShown = false;

	displayTimer = 0;
}

void Sword::Update(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft)
{
	this->ShowSword(_joeX, _joeY, _onCooldown, _facingRight, _isAttackingRight, _isAttackingLeft);
	this->CheckCollision();
}

void Sword::CheckCollision()
{

}

void Sword::ShowSword(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	if ((key[SDL_SCANCODE_E]) && (_onCooldown) && 
		((_isAttackingRight) || (_isAttackingLeft)))
	{
		isShown = true;
	}

	if ((!_onCooldown) || (!key[SDL_SCANCODE_E]))
	{
		isShown = false;
	}

	if (!isShown)
	{
		currentCol = 2;
	}
	else
		if ((isShown) && (_facingRight))
		{
			currentCol = 0;
			position.x = (_joeX + 50);
			position.y = (_joeY + 21);
		}
		else
			if ((isShown) && (!_facingRight))
			{
				currentCol = 1;
				position.x = (_joeX - 55);
				position.y = (_joeY + 21);
			}
}

void Sword::Draw()
{
	cellRect.x = currentCol * cellRect.w;
	cellRect.y = currentRow * cellRect.h;

	if (image)
	{
		SDL_RenderCopy(renderer, image, &cellRect, &position);
	}
}