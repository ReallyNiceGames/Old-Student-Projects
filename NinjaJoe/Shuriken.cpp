#include "Shuriken.h"

Shuriken::Shuriken(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol) : Sprite(_renderer, _file, 100, 100, _w, _h)
{
	cellsInRow = _cellsInRow;
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 2;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	isColliding = false;
	isShown = false;
	isThrown = false;

	throwSpeed = 6;
	throwDir = 0;
	left -= throwSpeed;
	right += throwSpeed;
}

void Shuriken::Update(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft)
{
	this->ThrowShuriken(_joeX, _joeY, _onCooldown, _facingRight, _isAttackingRight, _isAttackingLeft);
	this->CheckCollision();
}

void Shuriken::ThrowShuriken(int _joeX, int _joeY, bool _onCooldown, bool _facingRight, bool _isAttackingRight, bool _isAttackingLeft)
{
	//Allows SDL to get keyboard inputs
	const Uint8* key = SDL_GetKeyboardState(NULL);

	//Check is Q is pressed, and if attacks are not on cooldown, and if Joe is in the correct attack pose
	if ((key[SDL_SCANCODE_Q]) && (_onCooldown) &&
		((_isAttackingRight) || (_isAttackingLeft)))
	{
		isShown = true;
	}

	//If the shuriken is not being thrown then its position is reset, it's hidden, and it's direction is reset
	if ((!isShown) && (_facingRight))
	{
		currentCol = 2;
		throwDir = 0;
		position.x = (_joeX + 55);
		position.y = (_joeY + 15);
		isThrown = false;
	}
	else
		if ((!isShown) && (!_facingRight))
		{
			currentCol = 2;
			throwDir = 0;
			position.x = (_joeX - 10);
			position.y = (_joeY + 15);
			isThrown = false;
		}

	//Throws the shuriken based on the direction the player is facing
	//Also tells it to stop when it reaches the left or right edge of the screen
	if ((isShown) && (_facingRight))
	{
		if ((currentCol == 1) || (currentCol == 2))
		{
			currentCol = 0;
		}
		else
			if (currentCol == 0)
			{
				currentCol = 1;
			}

		if(!isThrown)
		{
			throwDir = right;
			isThrown = true;
		}
		
		if ((position.x > 800) || (position.x < 0))
		{
			isShown = false;
			isThrown = false;
		}
	}
	else
		if ((isShown) && (!_facingRight))
		{
			if ((currentCol == 1) || (currentCol == 2))
			{
				currentCol = 0;
			}
			else
				if (currentCol == 0)
				{
					currentCol = 1;
				}

			if (!isThrown)
			{
				throwDir = left;
				isThrown = true;
			}

			if ((position.x < 0) || (position.x > 800))
			{
				isShown = false;
				isThrown = false;
			}
		}

	//Moves the shuriken every frame based on the direction it's given
	position.x += throwDir;
}

void Shuriken::CheckCollision()
{

}

void Shuriken::Draw()
{
	cellRect.x = currentCol * cellRect.w;
	cellRect.y = currentRow * cellRect.h;

	if (image)
	{
		SDL_RenderCopy(renderer, image, &cellRect, &position);
	}
}