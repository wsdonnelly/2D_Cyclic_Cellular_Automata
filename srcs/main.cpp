#include <iostream>
#include <SDL.h>
#include <ctime>
#include "Cca.hpp"



int main() {

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//init sdl FIX UP
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not be initialized: " << SDL_GetError();
	else
		std::cout << "SDL success!\n";

	int width = 500;
	int height = 500;
	window = SDL_CreateWindow("CCA",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//SDL_Rect rect;

	SDL_GetWindowSize(window, &width, &height);

	srand(time(0));

	Cca cells;

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT){
				quit = true;
			}
			//if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(window, &width, &height);
				std::cout << "Window resized" << std::endl;
				std::cout << "width: " << width << " height: " << height << std::endl;
				cells.resize(width, height);

			}
		}
		cells.evolve(renderer);

		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		//SDL_RenderClear(renderer);
		//do drawing
		
		//SDL_RenderDrawLine(renderer, 0, 0, width - 1, height - 1);
		
		
		

	}
	
	// SDL_UpdateWindowSurface(window);

	///////
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}




// SDL_Event e;
// bool quit = false;
// while (!quit){
//     while (SDL_PollEvent(&e)){
//         if (e.type == SDL_QUIT){
//             quit = true;
//         }
//         if (e.type == SDL_KEYDOWN){
//             quit = true;
//         }
//         if (e.type == SDL_MOUSEBUTTONDOWN){
//             quit = true;
//         }
//     }
// }