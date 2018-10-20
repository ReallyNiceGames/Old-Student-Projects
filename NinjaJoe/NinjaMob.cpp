#include "NinjaMob.h"
#include <time.h>

NinjaMob::NinjaMob(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol, int _x, int _y) : Sprite(_renderer, _file, _x, _y - 56, _w, _h)
{
	cellsInRow = _cellsInRow;
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 0;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	canSeePlayer = false;
	isAttacking = false;
	facingRight = true;

	posTracker = 0;
	speed = 3;
	left -= speed;
	right += speed;
	moveDir = 0;
	animSpeed = 10;
	animTimer = animSpeed;
	isHit = false;
	m_attackPow = 5;

	gravity = 6;

	m_isFalling = false;
	m_isKilled = false;
	m_isCollidingPlayer = false;
}

void NinjaMob::Draw()
{
	cellRect.x = currentCol * cellRect.w;
	cellRect.y = currentRow * cellRect.h;

	if (image)
	{
		SDL_RenderCopy(renderer, image, &cellRect, &position);
	}
}

void NinjaMob::Update(Player* _joe, Shuriken* _shuriken, Sword* _sword)
{
	this->Idle(_shuriken);
	this->CheckCollision(_joe, _shuriken, _sword);

	this->AttackPlayer(_joe->GetX(), _joe->GetY(), _joe->GetFacingRight());

}

void NinjaMob::Idle(Shuriken* _shuriken)
{
	//Watches the ninja's position and turns them around after moving 200 pixels
	if (((posTracker >= 200) && (!facingRight)) || (position.x < -16))
	{
		facingRight = true;
		posTracker = 0;
		animTimer = animSpeed;
	}
	else
		if (((posTracker >= 200) && (facingRight)) || (position.x > 736))
		{
			facingRight = false;
			posTracker = 0;
			animTimer = animSpeed;
		}

	//Checks to see if the ninja is not attacking or can see the player
	//If it's not doing either of these, then it will start moving in an idle fashion
	if ((!canSeePlayer) && (!isAttacking))
	{
		if ((facingRight) && ((moveDir == left) || (moveDir == 0)))
		{
			moveDir = right;
			currentRow = 0;
			currentCol = 0;
		}
		else
			if ((!facingRight) && ((moveDir == right) || (moveDir == 0)))
			{
				moveDir = left;
				currentRow = 0;
				currentCol = 1;	
			}
	}

	//Animates the walking based on the faced direction
	if ((facingRight) && (moveDir == right))
	{
		currentRow = 1;

		++animTimer;

		if ((currentCol != 0) && (animTimer >= animSpeed))
		{
			currentCol = 0;
			animTimer = 0;
		}
		else
			if ((currentCol != 1) && (animTimer >= animSpeed))
			{
				currentCol = 1;
				animTimer = 0;
			}
	}
	else
		if ((!facingRight) && (moveDir >= left))
		{
			currentRow = 1;

			++animTimer;

			if ((currentCol != 3) && (animTimer >= animSpeed))
			{
				currentCol = 3;
				animTimer = 0;
			}
			else
				if ((currentCol != 2) && (animTimer >= animSpeed))
				{
					currentCol = 2;
					animTimer = 0;
				}
		}
	

	//Moves the ninja along
	if (!m_isFalling)
	{
		position.x += moveDir;
	}

	//Raises posTracker to watch how far the ninja is moving
	if ((moveDir != 0) && (!canSeePlayer))
	{
		posTracker += speed;
	}
	
}

void NinjaMob::AttackPlayer(int _joeX, int _joeY, int _joeFacingRight)
{
	//Checks if the player is within the eye-sight of the ninja
	if ((position.y - 7) == _joeY)
	{
		if ((!facingRight) && (position.x > _joeX))
		{
			canSeePlayer = true;
			joeIsLeft = true;
		}
		else
			if ((facingRight) && (position.x < _joeX))
			{
				canSeePlayer = true;
				joeIsRight = true;
			}
			else
			{
				canSeePlayer = false;
			}
	}
	else
	{
		canSeePlayer = false;
	}

	//Checks if Joe is left of the ninja
	if (joeIsLeft)
	{
		joeIsRight = false;
	}
	
	//Checks if Joe is right of the ninja
	if (joeIsRight)
	{
		joeIsLeft = false;
	}

	//Attacking player based on their position relative to the ninja
	if (canSeePlayer)
	{
		if (position.x > _joeX)
		{
			moveDir = left;
		}
		else
			if (position.x < _joeX)
			{
				moveDir = right;
			}
	}

	if ((m_isCollidingPlayer) && (moveDir == right))
	{
		currentRow = 0;
		currentCol = 2;
	}
	else
		if ((m_isCollidingPlayer) && (moveDir == left))
		{
			currentRow = 0;
			currentCol = 3;
		}
}

void NinjaMob::CheckCollision(Player* _joe, Shuriken* _shuriken, Sword* _sword)
{
	if (position.y > (700 - 56))
	{
		position.y = (700 - 56);
	}

	if (position.y < (700 - 56) && (position.y != 587) && (position.y != 432) && (position.y != 284)
		&& (position.y != 132))
	{
		position.y += gravity;
		m_isFalling = true;
	}
	else
	{
		m_isFalling = false;
	}

	//Checks to see if the ninja has collided with the player
	if (((position.y - 7) == _joe->GetY()) && (position.x == _joe->GetX()))
	{
		m_isCollidingPlayer = true;
		_joe->SetLife(m_attackPow);
		std::cout << "Life: " << _joe->GetLife() << std::endl;
	}
	else
	{
		m_isCollidingPlayer = false;
	}

	if (((_shuriken->GetY() >= position.y) && (_shuriken->GetY() <= position.y + _shuriken->GetH())) &&
		((_shuriken->GetX() >= position.x) && (_shuriken->GetX() <= position.x + _shuriken->GetW())))
	{
		isHit = true;
	}

	if (((_sword->GetY() >= position.y) && (_sword->GetY() <= position.y + _sword->GetH())) &&
		((_sword->GetX() >= position.x) && (_sword->GetX() <= position.x + _sword->GetW())))
	{
		isHit = true;
	}

	if ((isHit) && ((_shuriken->GetIsShown()) || (_sword->GetIsShown())))
	{
		//std::cout << "it hit, ouch" << std::endl;
		m_isKilled = true;
		_shuriken->SetIsShown();
	}

	isHit = false;
}