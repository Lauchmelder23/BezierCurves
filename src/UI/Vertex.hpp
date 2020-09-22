#pragma once

#include "IDrawable.hpp"

struct SDL_Rect;

class Vertex : public IDrawable
{
public:
	inline static unsigned char Color[4] = { 230, 20, 20, 255 };
	inline static unsigned char Cursor[4] = { 230, 20, 230, 255 };
	inline static unsigned int Size = 10;

public:
	Vertex(unsigned int x, unsigned int y, unsigned char* color = Color);

	void Draw(SDL_Renderer* renderer) override;
	void SetPos(int x, int y);

	unsigned int x, y;

private:
	SDL_Rect* rect;

	unsigned char* col;
};