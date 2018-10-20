#include "Player.h"
#include "Platform.h"
#include <iostream>

Player::Player(SDL_Renderer* _renderer, char* _file, int _w, int _h, int _cellsInRow, int _cellsInCol) : Sprite(_renderer, _file, 100, (700 - 63), _w, _h)
{
	m_hp = 100;
	speed = 6;
	jumpHeight = 50;
	isJumping = false;
	jumpLooper = 0;
	gravity = 8;
	m_score = 0;

	cellsInRow = _cellsInRow;
	cellsInCol = _cellsInCol;

	currentRow = 0;
	currentCol = 0;

	cellRect.x = 0;
	cellRect.y = 0;
	cellRect.w = _w;
	cellRect.h = _h;

	lastPressed = '0';
	animTimer = 0;
	cooldownTimer = 0;
	onCooldown = false;

	facingRight = true;
	isStandingRight = true;
	isStandingLeft = false;
	isJumpingRight = false;
	isJumpingLeft = false;
	isAttackingRight = false;
	isAttackingLeft = false;
	isFalling = false;
}

SDL_Rect Player::Update(bool _isCollidingPlatform)
{
	move.x = 0;
	move.y = 0;

	this->TakeInput(_isCollidingPlatform);
	this->CheckCollision(_isCollidingPlatform);
	this->CheckLife();

	this->CheckCooldown();
	this->Animate(_isCollidingPlatform);

	//std::cout << "y:" << position.y << std::endl;
	//std::cout << "x:" << position.x << std::endl;

	return move;
}

void Player::CheckLife()
{

}

void Player::CheckCollision(bool _isCollidingPlatform)
{
	if (position.y > (700 - 63))
	{
		position.y = (700 - 63);
	}
	else
		if (position.y < 100)
		{
			position.y = 100;
		}

	
	//Checking to see if the player is on a surface
	if ((position.y == (700 - 63) || ((position.y == 587 ) && (_isCollidingPlatform)) ||
		((position.y == 432) && (_isCollidingPlatform)) || ((position.y == 284) && (_isCollidingPlatform))
		|| ((position.y == 132) && (_isCollidingPlatform))))
	{
		isJumping = false;
		isFalling = false;
	}
	

	//Stops Joe going off of the sides of the screen
	if (position.x < 6)
	{
		position.x = 6;
	}
	else
		if (position.x > 740)
		{
			position.x = 740;
		}

	//Accurately places Joe on the platforms
	if ((position.y >= 580) && (position.y <= 588) && (_isCollidingPlatform))
	{
		position.y = 587;
	}
	else
		if ((position.y >= 425) && (position.y <= 435) && (_isCollidingPlatform))
		{
			position.y = 432;
		}
		else
			if ((position.y >= 277) && (position.y <= 286) && (_isCollidingPlatform))
			{
				position.y = 284;
			}
			else
				if ((position.y >= 126) && (position.y <= 132) && (_isCollidingPlatform))
				{
					position.y = 132;
				}



	if (position.y < (700 - 63))
	{
		if (!_isCollidingPlatform)
		{
			move.y += gravity;
			//isFalling = true;
		}
		else
			if ((_isCollidingPlatform) && (position.y != 587) && (position.y != 432)
				&& (position.y != 284) && (position.y != 132))
			{
				move.y += gravity;
				//isFalling = true;
			}
	}

	if ((move.y == 0) && (!isJumping))
	{
		isFalling = false;
		//std::cout << move.y << std::endl;
	}
}

SDL_Rect Player::TakeInput(bool _isCollidingPlatform)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);
	
	//Moving left
	if (key[SDL_SCANCODE_A])
	{
		if ((_isCollidingPlatform) && (position.x != 442) && (position.x != 322) && (position.x != 202) &&
			(position.x != 100) && (position.x != 580) && (position.x != 688) && (position.x != 582) && (position.x != 578))
		{
			move.x -= speed;
		}
		else
			if (!_isCollidingPlatform)
			{
				move.x -= speed;
			}

	}

	//Moving right
	if (key[SDL_SCANCODE_D])
	{
		if ((_isCollidingPlatform) && (position.x != 286) && (position.x != 162) && (position.x != 42) &&
			(position.x != 424) && (position.x != 532) && (position.x != 646) && (position.x != 40) && (position.x != 160)
			&& (position.x != 422))
		{
			move.x += speed;
		}
		else
			if (!_isCollidingPlatform)
			{
				move.x += speed;
			}

	}

	//Check if player is not jumping and is on the ground
	if ((!isJumping) && (!isFalling))
	{
		if ((key[SDL_SCANCODE_W]) || (key[SDL_SCANCODE_SPACE]))
		{
			isJumping = true;
		}
	}

	if ((isJumping) && (!isFalling))
	{
		//jumpLooper is used to smoothen the transition of the player jumping in the air
		move.y -= jumpHeight;
		++jumpLooper;
		jumpHeight -= 5;

		//This statement is called once the player has reached the top of their jump
		if (jumpLooper == 10)
		{
			isJumping = false;
			isFalling = true;
			jumpLooper = 0;
			jumpHeight = 50;
		}
	}

	return move;
}

void Player::Move(SDL_Rect& _move)
{
	position.x += _move.x;
	position.y += _move.y;
}

void Player::Draw()
{
	cellRect.x = currentCol * cellRect.w;
	cellRect.y = currentRow * cellRect.h;

	if (image)
	{
		SDL_RenderCopy(renderer, image, &cellRect, &position);
	}
}

void Player::Animate(bool _isCollidingPlatform)
{
	const Uint8* key = SDL_GetKeyboardState(NULL);

	//Left walking
	if (key[SDL_SCANCODE_A])
	{
		if (lastPressed != 'A')
		{
			animTimer = 0;
		}

		++animTimer;

		if (animTimer == 10)
		{
			currentRow = 2;

			if (currentCol != 3)
			{
				currentCol = 3;
			}
			else
				if (currentCol != 2)
				{
					currentCol = 2;
				}

			animTimer = 0;
		}

		facingRight = false;
		lastPressed = 'A';
	}

	//Right walking
	if (key[SDL_SCANCODE_D])
	{
		if (lastPressed != 'D')
		{
			animTimer = 0;
		}

		++animTimer;

		if (animTimer == 10)
		{
			currentRow = 2;

			if (currentCol != 1)
			{
				currentCol = 1;
			}
			else
				if (currentCol != 0)
				{
					currentCol = 0;
				}

			animTimer = 0;
		}
		
		facingRight = true;
		lastPressed = 'D';
	}

	//Jumping
	if (!isFalling)
	{
		if ((key[SDL_SCANCODE_W]) || (key[SDL_SCANCODE_SPACE]))
		{
			if (lastPressed == 'A')
			{
				currentCol = 3;
				currentRow = 0;
			}

			if (lastPressed == 'D')
			{
				currentCol = 2;
				currentRow = 0;
			}

			if (lastPressed == 'W')
			{
				if (!facingRight)
				{
					currentCol = 3;
					currentRow = 0;
				}
				else
					if (facingRight)
					{
						currentCol = 2;
						currentRow = 0;
					}
			}

			lastPressed = 'W';
		}
	}
	else
		if (isFalling)
		{
			if (facingRight)
			{
				currentCol = 0;
				currentRow = 1;
			}
			else
				if (!facingRight)
				{
					currentCol = 1;
					currentRow = 1;
				}
		}

	//Slashing
	if ((key[SDL_SCANCODE_E]) && (!key[SDL_SCANCODE_A]) && (!key[SDL_SCANCODE_D]) && 
		(!key[SDL_SCANCODE_SPACE]) && (!key[SDL_SCANCODE_W]))
	{

		//Changes pose based on direction faced
		if ((facingRight) && (!onCooldown))
		{
			currentCol = 2;
			currentRow = 1;
			onCooldown = true;
		}
		else
			if ((!facingRight) && (!onCooldown))
			{
				currentCol = 3;
				currentRow = 1;
				onCooldown = true;
			}

		lastPressed = 'E';
	}

	//Shooting
	if ((key[SDL_SCANCODE_Q]) && (!key[SDL_SCANCODE_A]) && (!key[SDL_SCANCODE_D]) && 
		(!key[SDL_SCANCODE_SPACE]) && (!key[SDL_SCANCODE_W]))
	{

		//Changes pose based on direction faced
		if ((facingRight) && (!onCooldown))
		{
			currentCol = 2;
			currentRow = 1;
			onCooldown = true;
		}
		else
			if ((!facingRight) && (!onCooldown))
			{
				currentCol = 3;
				currentRow = 1;
				onCooldown = true;
			}

		lastPressed = 'Q';
	}

	//Idle pose
	if (((!key[SDL_SCANCODE_W]) && (!key[SDL_SCANCODE_A]) && (!key[SDL_SCANCODE_D]) && 
		(!key[SDL_SCANCODE_SPACE]) && (!key[SDL_SCANCODE_E]) && (!key[SDL_SCANCODE_Q]) && 
		(position.y == (700 - 63)) || ((_isCollidingPlatform) && ((!key[SDL_SCANCODE_D]) || (!key[SDL_SCANCODE_A])))))
	{
		if ((lastPressed == 'A') || ((lastPressed == 'E') && (!facingRight)) || 
			((lastPressed == 'Q') && (!facingRight)))
		{
			currentCol = 1;
			currentRow = 0;
		}
		
		if ((lastPressed == 'D') || ((lastPressed == 'E') && (facingRight)) || 
			((lastPressed == 'Q') && (facingRight)))
		{
			currentCol = 0;
			currentRow = 0;
		}

		if (lastPressed == 'W')
		{
			if (currentCol == 1)
			{
				currentRow = 0;
			}
			else
				if (currentCol == 0)
				{
					currentRow = 0;
				}
		}
	}

	this->CurrentPose();
}

void Player::CheckCooldown()
{
	//Checks weapon cooldown
	if (onCooldown)
	{
		++cooldownTimer;
		if (cooldownTimer == 60)
		{
			onCooldown = false;
			cooldownTimer = 0;
		}
	}
}

void Player::CurrentPose()
{
	//Getting current pose and setting booleans accordingly
	//This is to keep track of Joe's sprite being used to sync them with the actions

	//Jumping
	if ((currentCol == 2) && (currentRow == 0))
	{
		isJumpingRight = true;
	}
	else
	{
		isJumpingRight = false;
	}

	if ((currentCol == 3) && (currentRow == 0))
	{
		isJumpingLeft = true;
	}
	else
	{
		isJumpingLeft = false;
	}
	
	//Attacking
	if ((currentCol == 2) && (currentRow == 1))
	{
		isAttackingRight = true;
	}
	else
	{
		isAttackingRight = false;
	}

	if ((currentCol == 3) && (currentRow == 1))
	{
		isAttackingLeft = true;
	}
	else
	{
		isAttackingLeft = false;
	}

	//Standing
	if ((currentCol == 0) && (currentRow == 0))
	{
		isStandingRight = true;
	}
	else
	{
		isStandingRight = false;
	}

	if ((currentCol == 1) && (currentRow == 0))
	{
		isStandingLeft = true;
	}
	else
	{
		isStandingLeft = false;
	}
}
