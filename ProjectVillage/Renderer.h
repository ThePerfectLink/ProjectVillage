#include <SDL.h>
#include <SDL_image.h>
#include <SDL_Render.h>

class Renderer {
	public:
		Renderer(SDL_Window* window, int sets, SDL_Rect position, SDL_Rect size);
		SDL_Renderer* renderer;
		SDL_Texture** texture_sets;
		SDL_Rect** texture_frames;
		int* texture_sets_num;
		int texture_set_of_sets_num;
		SDL_Rect pos;
		SDL_Rect si;

		void addTextureSet(SDL_Texture* texture_set, int group, int amount);
		

		~Renderer();
};

