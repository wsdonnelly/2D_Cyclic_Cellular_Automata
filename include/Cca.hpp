#include <vector>
#include <SDL.h>

class Cca {
	private:
		std::vector<char> cell_map;
		std::vector<char> copy_cell_map;
		int px_size = 3;
		int threshold = 3;
		int num_states = 4;
		int width = 500;
		int height = 500;
		int px_w;
		int px_h;

		void init();
	public:
		Cca();
		void evolve(SDL_Renderer* renderer, SDL_Rect* rect);
		bool check_neighbors(int x, int y, int state);
		void resize(int w, int h);
		void change_resolution(int change);
};
