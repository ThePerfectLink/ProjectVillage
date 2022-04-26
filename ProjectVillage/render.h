#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>



class render {
	class Button;
};

class Button {
	public:

		Button(SDL_Renderer*, SDL_Texture*);

	private:
		SDL_Rect button[3];

};