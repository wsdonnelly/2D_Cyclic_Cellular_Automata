#include <iostream>
#include <SDL.h>

void draw_board() {
	
}

int main() {

	SDL_Window *window = nullptr;
	SDL_Surface *screen = nullptr;

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
	screen = SDL_GetWindowSurface(window);

	int width;
	int height;

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
				screen = SDL_GetWindowSurface(window);

			}
		}
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