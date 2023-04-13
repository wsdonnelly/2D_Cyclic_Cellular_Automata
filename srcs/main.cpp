#include <iostream>
#include <SDL.h>


int main() {

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	//init sdl FIX UP
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL could not be initialized: " << SDL_GetError();
	else
		std::cout << "SDL success!\n";

	window = SDL_CreateWindow("CCA",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			500,
			500,
			SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rect;

	int width;
	int height;

	SDL_GetWindowSize(window, &width, &height);
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
			}
		}
		//do logic
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		//do drawing
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawLine(renderer, 0, 0, width - 1, height - 1);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8 ; j++) {
				rect.x = j * (width / 8);
				rect.y = i * (height / 8);
				rect.w = width / 8;
				rect.h = height / 8;
				SDL_RenderDrawRect(renderer, &rect);
			}
		}

		
		SDL_RenderPresent(renderer);

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