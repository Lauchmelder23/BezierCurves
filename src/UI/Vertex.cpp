#include "Vertex.hpp"

#include <SDL.h>

Vertex::Vertex(unsigned int x, unsigned int y, unsigned char* color) :
	rect(new SDL_Rect),
	col(color)
{
	SetPos(x, y);
}

void Vertex::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, col[0], col[1], col[2], col[3]);
	SDL_RenderFillRect(renderer, rect);
}

void Vertex::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;

	rect->x = x - Size / 2;
	rect->y = y - Size / 2;
	rect->w = Size;
	rect->h = Size;
}
