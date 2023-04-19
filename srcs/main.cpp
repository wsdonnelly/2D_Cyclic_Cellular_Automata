#include <iostream>
#include <SDL.h>
#include <ctime>
#include <thread>
#include "Cca.hpp"


// void update(Cca& cells, SDL_Renderer* renderer, int tid) {

// 	int state;

// 	for (int y = tid; y < cells.height; y += 4) {
// 		for (int x = 0; x < cells.width; x++) {
// 			state = cells.copy_cell_map[cells.width * y + x];
// 			if (cells.check_neighbors(x, y, state)) {
// 				//set new cell state
// 				cells.cell_map[cells.width * y + x] = (state + 1) % cells.num_states;
// 			}
// 			//draw orig
// 			if (state == 0)
// 			//RED
// 				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
// 			else if (state == 1)
// 				//GREEN
// 				SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
// 			else if (state == 2)
// 				//BLUE
// 				SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
// 			else if (state == 3)
// 				//YELLOW
// 				SDL_SetRenderDrawColor(renderer, 255, 224, 32, SDL_ALPHA_OPAQUE);
// 			SDL_RenderDrawPoint(renderer, x, y);
// 		}
// 	}
// }

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

	SDL_GetWindowSize(window, &width, &height);

	srand(time(0));

	Cca cells;

	SDL_Event e;
	bool quit = false;
	int num = 0;

	//int num_threads = 8;
	std::vector<std::thread> thread_vect;
	while (!quit && num < 500)
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

		cells.copy_map();

		// for (int i = 0; i < num_threads; ++i)
		// 	thread_vect.push_back(std::thread{&Cca::evolve, &cells, 0});
		std::thread t1(&Cca::evolve, &cells, 0);
		std::thread t2(&Cca::evolve, &cells, 1);
		std::thread t3(&Cca::evolve, &cells, 2);
		std::thread t4(&Cca::evolve, &cells, 3);
		std::thread t5(&Cca::evolve, &cells, 4);
		std::thread t6(&Cca::evolve, &cells, 5);
		std::thread t7(&Cca::evolve, &cells, 6);
		std::thread t8(&Cca::evolve, &cells, 7);

		// for (auto& it : thread_vect)
		// 	it.join();
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();
		
		cells.draw_map(renderer);

		++num;
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