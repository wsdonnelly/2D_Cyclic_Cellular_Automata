#include "Cca.hpp"
#include <iostream>

Cca::Cca(){
	px_w = width / px_size;
	px_h = height / px_size;
	cell_map.resize(px_w * px_h);
	this->init();
}

void Cca::init() {
	//fill cell_map with random vals
	for (auto& it : cell_map)
		it = rand() % num_states;
}

void Cca::resize_win() {
	px_w = width / px_size;
	px_h = height/ px_size;
	cell_map.resize(px_w * px_h);
	init();
}

void Cca::change_resolution(int change) {
	if (change > 0 && px_size * 2 < width) {
		px_size += change;
	}
	else if (change < 0 && px_size > 1)
		px_size += change;

	std::cout << "px_size: " << px_size <<std::endl;
	resize_win();
	init();
}

void Cca::evolve(SDL_Renderer* renderer, SDL_Rect* rect) {

	int state;

	copy_cell_map = cell_map;

	for (int y = 0; y < px_h; y++) {
		for (int x = 0; x < px_w; x++) {
			state = copy_cell_map[px_w * y + x];
			if (check_neighbors(x, y, state)) {
				//set new cell state
				cell_map[px_w * y + x] = (state + 1) % num_states;
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

			//SDL_RenderDrawPoint(renderer, x, y);
			rect->x = x * px_size; 
			rect->y = y * px_size;
			rect->w = px_size;
			rect->h = px_size;

			SDL_RenderFillRect(renderer, rect);
		}
	}
	SDL_RenderPresent(renderer);
}


bool Cca::check_neighbors(int x, int y, int state) {
	//num of neighbors with state + 1
	//if == threshold change cell to i + 1;
	int count = 0;
	int left, right, up, down;
	int i = x + (y * px_w);

	left = (x == 0) ? px_w - 1 : - 1;
	right = (y == px_w - 1) ? -(px_w - 1): 1;
	up = (y == 0) ? (px_w * (px_h - 1)) : -px_w;
	down = (y == px_h - 1) ? -(px_w * (px_h - 1)) : px_w;

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