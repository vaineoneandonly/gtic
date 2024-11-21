#define SDL_MAIN_HANDLED
#define SCR_X 1024
#define SCR_Y  768

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main(void)
{	
	//window and renderer
	SDL_Window     *mainWindow = SDL_CreateWindow("GTIC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_X, SCR_Y, SDL_WINDOW_SHOWN);	
	SDL_Renderer *mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

	//player physics
	SDL_Rect playerPos = {200, 200, 50, 70};

	float speedX = 0.0f;
	float speedY = 0.0f;

	float     friction = 0.8f;
	float acceleration = 1.2f;	

	//player sprite
	//SDL_Surface *surface = SDL_LoadBMP("C:\\Users\\conta\\Desktop\\Programação\\faculdade\\GTIC\\goofy.bmp");
	SDL_Surface *surface = SDL_LoadBMP("goofy.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(mainRenderer, surface);
	

	//bg
	SDL_Surface *background = SDL_LoadBMP("background.bmp");
	SDL_Texture  *bgTexture = SDL_CreateTextureFromSurface(mainRenderer, background);

	//flags
	bool  left = false;
	bool right = false;
	bool    up = false;
	bool  down = false;

	bool run = true;
	while (run)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case  SDLK_LEFT:  left = true; break;
						case SDLK_RIGHT: right = true; break;
						case    SDLK_UP:    up = true; break;
						case  SDLK_DOWN:  down = true; break;
					}
					break;
				
				case SDL_KEYUP:
					switch(event.key.keysym.sym)					
					{
						case  SDLK_LEFT:  left = false; break;
						case SDLK_RIGHT: right = false; break;
						case    SDLK_UP:    up = false; break;
						case  SDLK_DOWN:  down = false; break;
					}
					break;

				case SDL_QUIT:
					run = false;
					break;
			}
		}

		printf("%d %d\n", playerPos.x, playerPos.y);

		if  (left) speedX -= acceleration;
		if (right) speedX += acceleration;
		if    (up) speedY += acceleration;
		if  (down) speedY -= acceleration;

		speedX *= friction;
		speedY *= friction;

		playerPos.x  += (int)(speedX);
		playerPos.y  -= (int)(speedY);

		if (playerPos.x < 153) playerPos.x = 153;
		if (playerPos.x > 821) playerPos.x = 821;
		if (playerPos.y > 622) playerPos.y = 622;
		if (playerPos.y < 128) playerPos.y = 128;		
		
		SDL_SetRenderDrawColor(mainRenderer, 20, 20, 20, 255);
		SDL_RenderCopy(mainRenderer, bgTexture, NULL, 0);
 
		SDL_RenderCopy(mainRenderer, texture, NULL, &playerPos);

		
		SDL_RenderPresent(mainRenderer);

		SDL_Delay(16);
	}

}
