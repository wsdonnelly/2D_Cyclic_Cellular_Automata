#include "Cca.hpp"
#include <algorithm>

Cca::Cca(): cell_map(250000){
	this->init();
}

void Cca::init() {
	//fill cell_map with random vals
	//fill with zeros
	std::fill(cell_map.begin(), cell_map.end(), 0);
	
	for (int i = 0; i < cell_map.size(); ++i) {
		int state = rand() % num_states;
		cell_map[i] += state;
		int x = i % width;
		int y = i / width;
		
		int left = (x == 0) ? width - 1 : - 1;
		int right = (y == width - 1) ? -(width - 1): 1;
		int up = (y == 0) ? (width * (height - 1)) : -width;
		int down = (y == height - 1) ? -(width * (height - 1)) : width;

		cell_map[i + up] += (1 << (state * 3 + 2));
		cell_map[i + down] += (1 << (state * 3 + 2));
		cell_map[i + left] += (1 << (state * 3 + 2));
		cell_map[i + right] += (1 << (state * 3 + 2));
		cell_map[i + (up + left)] += (1 << (state * 3 + 2));
		cell_map[i + (up + right)] += (1 << (state * 3 + 2));
		cell_map[i + (down + left)] += (1 << (state * 3 + 2));
		cell_map[i + (down + right)] += (1 << (state * 3 + 2));
	}

}

void Cca::resize(int w, int h) {
	width = w;
	height = h;
	cell_map.resize(width * height);
	init();
}
#include <iostream>
void Cca::evolve(SDL_Renderer* renderer) {

	int state;
	copy_cell_map = cell_map;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int idx = width * y + x;
			state = (copy_cell_map[idx] & 0x03);
			if (((copy_cell_map[idx] >> (((state + 1) % num_states) * 3 + 2)) & 0x07 ) >= threshold){
			
				if (state < 3)
					cell_map[idx] += 0x01;
				else
					cell_map[idx] ^= 0x03;
				update_neighbors(x, y, state);
			}

			// if (check_neighbors(x, y, state)) {
			// 	//set new cell state
			// 	cell_map[width * y + x] = (state + 1) % num_states;
			// }
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


void Cca::update_neighbors(int x, int y, int state) {
	//num of neighbors with state + 1
	//if == threshold change cell to i + 1;
	
	int left, right, up, down;
	int i = x + (y * width);

	left = (x == 0) ? width - 1 : - 1;
	right = (y == width - 1) ? -(width - 1): 1;
	up = (y == 0) ? (width * (height - 1)) : -width;
	down = (y == height - 1) ? -(width * (height - 1)) : width;

	//int target = (state + 1) % num_states;

	cell_map[i + up] -= (1 << (state * 3 + 2));
	cell_map[i + down] -= (1 << (state * 3 + 2));
	cell_map[i + left] -= (1 << (state * 3 + 2));
	cell_map[i + right] -= (1 << (state * 3 + 2));
	cell_map[i + (up + left)] -= (1 << (state * 3 + 2));
	cell_map[i + (up + right)] -= (1 << (state * 3 + 2));
	cell_map[i + (down + left)] -= (1 << (state * 3 + 2));
	cell_map[i + (down + right)] -= (1 << (state * 3 + 2));
	
	int new_state = (state + 1) % num_states;

	cell_map[i + up] += (1 << (new_state * 3 + 2));
	cell_map[i + down] += (1 << (new_state * 3 + 2));
	cell_map[i + left] += (1 << (new_state * 3 + 2));
	cell_map[i + right] += (1 << (new_state * 3 + 2));
	cell_map[i + (up + left)] += (1 << (new_state * 3 + 2));
	cell_map[i + (up + right)] += (1 << (new_state * 3 + 2));
	cell_map[i + (down + left)] += (1 << (new_state * 3 + 2));
	cell_map[i + (down + right)] += (1 << (new_state * 3 + 2));
	
}