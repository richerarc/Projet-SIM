#pragma once
#include <vector>
namespace gfx{
	class ModeVideo
	{
	public:
		ModeVideo(){
			SDL_GetDisplayMode(0, 0, &md);
			this->h = md.h;
			this->l = md.w;
		}

		ModeVideo(unsigned int l, unsigned int h){
			this->l = l;
			this->h = h;
			md = { SDL_PIXELFORMAT_RGBA8888, this->l, this->h, 0, 0 };
		}

		static std::vector<ModeVideo>& obtModes(){
			SDL_DisplayMode tmp;
			int nummodes = SDL_GetNumDisplayModes(0);
			for (int j = 0; j < nummodes; ++j) {
				SDL_GetDisplayMode(0, j, &tmp);
				modes.push_back(ModeVideo(tmp.w, tmp.h));
			}
			return modes;
		}

		unsigned int l;
		unsigned int h;
		SDL_DisplayMode md;

		static std::vector<ModeVideo> modes;
	};
}
