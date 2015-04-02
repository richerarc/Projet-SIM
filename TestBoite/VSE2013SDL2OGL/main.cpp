#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <math.h>
#include "LecteurFichier.h"

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* pSDLWindow = SDL_CreateWindow("SDL2 / OpenGL", 50, 50, 500, 500, SDL_WINDOW_OPENGL);
	SDL_GLContext SDLGLContext = SDL_GL_CreateContext(pSDLWindow);
	SDL_Event SDLEvent;

	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 0.1, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslated(0, 0, -3);
	glEnable(GL_DEPTH_TEST);
	double Vertices[] = {
		-0.71429, - 3.49810, 2.00671,
		0.14286, - 3.49810, 2.00671,
		0.14286, - 3.49810, 0.00671,
		- 0.71429, - 3.49810, 0.00671,
		- 0.71429, 0.50190, 0.00671,
		- 0.71429, 0.50190, 2.00671,
		0.14286, 0.50190, 2.00671,
		0.14286, 0.50190, 0.00671 };//7
	double Colors[] = { 1, 1, 1,
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
		1, 1, 0,
		1, 0, 1,
		0, 1, 1,
		0, 0, 0 };
	unsigned int Indices[] = { 0, 1, 2, //up
		0, 3, 2,
		3, 4, 0,
		4, 0, 5,
		4, 5, 7,
		5, 7, 6,
	6, 7, 1,
	7, 1, 2,
	1, 0, 6,
	0, 6, 5,
	7, 4, 3,
	3, 2, 7};

	bool boExecution = true;
	while (boExecution) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, Vertices);
		glColorPointer(3, GL_DOUBLE, 0, Colors);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, Indices);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		SDL_GL_SwapWindow(pSDLWindow);
		while (SDL_PollEvent(&SDLEvent)) {
			boExecution = !(SDLEvent.type == SDL_QUIT);
		}
	}

	SDL_GL_DeleteContext(SDLGLContext);
	SDL_DestroyWindow(pSDLWindow);
	SDL_Quit();
	return 0;
}