#include <vector>
#include <SDL.h>
#include <cstdint>

class Cca {
	private:
		std::vector<uint16_t> cell_map;
		std::vector<uint16_t> copy_cell_map;
		int threshold = 3;
		int num_states = 4;
		int width = 500;
		int height = 500;

		void init();
	public:
		Cca();
		void evolve(SDL_Renderer* renderer);
		void update_neighbors(int x, int y, int state);
		void resize(int w, int h);
};
