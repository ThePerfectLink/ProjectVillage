#include "Renderer.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_Render.h>
#include <stdexcept>

using namespace std;

Renderer::Renderer(SDL_Window* window, int sets, SDL_Rect position, SDL_Rect size) {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	texture_sets_num = (int*)malloc(sizeof(int*) * sets);
	texture_set_of_sets_num = sets;
	texture_sets = (SDL_Texture**)malloc(sizeof(SDL_Texture**) * sets);
	texture_frames = (SDL_Rect**)malloc(sizeof(SDL_Rect**) * (sets));
	si = size;
	pos = position;
	if (texture_sets) {
		for (int i = 0; i < sets; i++) {
			texture_sets[i] = (SDL_Texture*)malloc(sizeof(SDL_Texture*) * 1);
			texture_frames[i] = (SDL_Rect*)malloc(sizeof(SDL_Rect*) * 1);
		}
	}
}

void Renderer::addTextureSet(SDL_Texture* texture_set, int group, int amount) {
	try {
		texture_sets[group] = (SDL_Texture*)realloc(texture_sets[group], sizeof(texture_set) * amount);
		texture_frames[group] = (SDL_Rect*)realloc(texture_frames[group], sizeof(SDL_Rect) * (amount+1));
		texture_sets[group] = texture_set;
		texture_frames[group][0] = si;
		for (int i = 0; i < amount+1; i++) {
			texture_frames[group][i+1] = pos;
			texture_frames[group][i + 1].y += si.h;
		}
	} catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
}

Renderer::~Renderer() {
	for (int i = 0; i < texture_set_of_sets_num; i++) {
		free(texture_sets[i]);
		free(texture_frames[i]);
		texture_sets[i] = NULL;
		texture_frames[i] = NULL;
	}
	free(texture_frames[texture_set_of_sets_num]);
	texture_frames[texture_set_of_sets_num] = NULL;
	free(texture_sets);
	texture_sets = NULL;
	free(texture_frames);
	texture_frames = NULL;
}