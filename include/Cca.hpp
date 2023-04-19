#include <vector>
#include <SDL.h>

class Cca {
	private:
		std::vector<char> cell_map;
		std::vector<char> copy_cell_map;
		std::vector<int> neighbors;
		int threshold = 3;
		int num_states = 4;
		int width = 500;
		int height = 500;

		void init();
	public:
		Cca();
		void evolve(SDL_Renderer* renderer);
		bool check_neighbors(int x, int y, int state);
		void resize(int w, int h);
};
