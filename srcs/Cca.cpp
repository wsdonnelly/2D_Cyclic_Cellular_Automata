#include "Cca.hpp"

Cca::Cca(): cell_map(250000){
	this->init();
}

void Cca::init() {
	//fill cell_map with random vals
	for (auto& it : cell_map)
		it = rand() % num_states;
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
			if (check_neighbors(x, y, state)) {
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
	int left, right, up, down;
	int i = x + (y * width);

	left = (x == 0) ? width - 1 : - 1;
	right = (y == width - 1) ? -(width - 1): 1;
	up = (y == 0) ? (width * (height - 1)) : -width;
	down = (y == height - 1) ? -(width * (height - 1)) : width;

	int target = (state + 1) % num_states;

	if (copy_cell_map[i + left] == target)
		count++;
	if (copy_cell_map[i + right] == target)
		count++;
	if (copy_cell_map[i + up] == target)
		count++;
	if (copy_cell_map[i + down] == target)
		count++;
	if (copy_cell_map[i + (up + left)] == target)
		count++;
	if (copy_cell_map[i + (up + right)] == target)
		count++;
	if (copy_cell_map[i + (down + left)] == target)
		count++;
	if (copy_cell_map[i + (down + right)] == target)
		count++;
	if (count >= threshold)
		return true;
	return false;
}