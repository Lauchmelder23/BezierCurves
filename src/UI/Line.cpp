#include "Line.hpp"

#include <SDL.h>

Line::Line(const Vertex* a, const Vertex* b) :
	a(a), b(b)
{
}

void Line::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], Color[3]);
	SDL_RenderDrawLine(renderer, a->x, a->y, b->x, b->y);
}
