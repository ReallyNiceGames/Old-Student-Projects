#include "Bkg.h"
#include "Player.h"

Bkg::Bkg(SDL_Renderer* _renderer, char* _imagefile, char* _collisionMapFile, int _x, int _y, int _w, int _h)
{
	w = _w;
	h = _h;
	x = _x;
	y = _y;
	showCollisionMap = false;

	image = new Sprite(_renderer, _imagefile, 0, 0, _w, _h);
	collisionMap = new Sprite(_renderer, _collisionMapFile, _x, _y, _w, _h); // only needed for debug drawing

	ReadCollisionImage(_collisionMapFile);

	isColliding = false;
}

Bkg::~Bkg()
{
	delete image;
	delete collisionMap;
}

// based on: https://wiki.libsdl.org/SDL_PixelFormat
void Bkg::ReadCollisionImage(char* _collisionMapFile)
{
	SDL_PixelFormat *fmt;
	SDL_Surface *collisionSurface;
	Uint32 temp;
	Uint32* pixels;

	collisionSurface = SDL_LoadBMP(_collisionMapFile);
	collisionSize.w = collisionSurface->w;
	collisionSize.h = collisionSurface->h;

	fmt = collisionSurface->format;
	SDL_LockSurface(collisionSurface);
	pixels = (Uint32*)collisionSurface->pixels;
	SDL_UnlockSurface(collisionSurface);

	// store each pixel as an SDL_Color in a std::vec
	for (int i = 0; i < collisionSurface->w * collisionSurface->h; i++)
	{
		SDL_Color col;

		/* Get Red component */
		temp = pixels[i] & fmt->Rmask;  /* Isolate red component */
		temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
		col.r = (Uint8)temp;

		/* Get Green component */
		temp = pixels[i] & fmt->Gmask;  /* Isolate green component */
		temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
		col.g = (Uint8)temp;

		/* Get Blue component */
		temp = pixels[i] & fmt->Bmask;  /* Isolate blue component */
		temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
		col.b = (Uint8)temp;

		/* Get Alpha component */
		temp = pixels[i] & fmt->Amask;  /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
		col.a = (Uint8)temp;

		collisionPixels.push_back(col);
	}

	SDL_FreeSurface(collisionSurface);
}

void Bkg::CheckCollision(Player* player, SDL_Rect& move)
{
	// we want to move to here
	int checkMoveX = x;
	int checkMoveY = y;

	isColliding = false;

	// this is where that would be on the collision map
	// (the upper-left of the players rect would be here if we moved here)
	int yOffset = player->GetY() + move.y;
	int xOffset = player->GetX() + move.x;

	// do not check out of the map bounds
	if (xOffset < 0 || xOffset + player->GetW() > collisionSize.w) return;
	//if (yOffset < 0 || yOffset + player->GetH() > collisionSize.h) return;

	// iterate over the pixels of the collision map that would be under the 
	// players rect if we moved. Return if we find one pixel that is black
	SDL_Color col;
	int checkPixel;
	for (int checkY = yOffset; checkY < yOffset + player->GetH(); checkY++)
	{
		if (checkY < 0 || checkY >= collisionSize.h) continue;

		for (int checkX = xOffset; checkX < xOffset + player->GetW(); checkX++)
		{
			checkPixel = (checkY * collisionSize.w) + checkX;
			col = collisionPixels[checkPixel];

			// if r == 0 then we are trying to move onto a black pixel, so don't.
			// (we could check col.g or col.b instead)
			if (col.r == 0)
			{
				move.x = 0;
				move.y = 0;
				isColliding = true;
				return;
			}
		}
	}

	// it is ok to move onto this pixel
	//x = checkMoveX;
	//y = checkMoveY;

}

void Bkg::Draw()
{
	image->SetX(x);
	image->SetY(y);
	image->Draw();

	if (showCollisionMap)
	{
		collisionMap->SetX(x);
		collisionMap->SetY(y);
		collisionMap->Draw();
	}
}