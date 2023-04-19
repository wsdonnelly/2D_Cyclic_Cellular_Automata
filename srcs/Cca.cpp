#include "Cca.hpp"

Cca::Cca(): cell_map(250000){
	this->init();
}

void Cca::init() {
	//fill cell_map with random vals
	for (auto& it : cell_map)
		it = rand() % num_states;
	neighbors.resize(8);
	neighbors[0] = 0;
	neighbors[1] = 1;
	neighbors[2] = 2;
	neighbors[3] = width;
	neighbors[4] = width + 2;
	neighbors[5] = width * 2;
	neighbors[6] = width * 2 + 1;
	neighbors[7] = width  * 2 + 2;
}

void Cca::resize(int w, int h) {
	width = w;
	height = h;
	cell_map.resize(width * height);
	init();
}

void Cca::evolve(SDL_Renderer* renderer) {

	int state;

	copy_cell_map = cell_map;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			state = copy_cell_map[width * y + x];
			if (x > 0 && x < width - 1 && y > 0 && y < height -1 && check_neighbors(x, y, state)) {
				//set new cell state
				cell_map[width * y + x] = (state + 1) % num_states;
			}
			//draw orig
			if (state == 0)
			//RED
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			else if (state == 1)
				//GREEN
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
			else if (state == 2)
				//BLUE
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
			else if (state == 3)
				//YELLOW
				SDL_SetRenderDrawColor(renderer, 255, 224, 32, SDL_ALPHA_OPAQUE);

			SDL_RenderDrawPoint(renderer, x, y);
			
			//SDL_RenderDrawRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}


bool Cca::check_neighbors(int x, int y, int state) {
	//num of neighbors with state + 1
	//if == threshold change cell to i + 1;
	int count = 0;
	int i = x + (y * width) - (width + 1);

	int target = (state + 1) % num_states;

	for (auto distance: neighbors) {
		if (copy_cell_map[i + distance] == target)
			++count;
			if (count == threshold)
				return (true);
	}
	return false;
}