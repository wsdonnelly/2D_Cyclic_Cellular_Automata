#include <vector>
#include <SDL.h>

class Cca {
	private:
		std::vector<char> cell_map;
		std::vector<char> copy_cell_map;
		int threshold = 3;
		int num_states = 4;
		int px_w;
		int px_h;

		void init();
	public:
		Cca();
		int width = 500;
		int height = 500;
		int px_size = 1;
		void evolve(SDL_Renderer* renderer, SDL_Rect* rect);
		bool check_neighbors(int x, int y, int state);
		void resize_win();
		void change_resolution(int change);
};
