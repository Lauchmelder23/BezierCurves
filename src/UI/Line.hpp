#pragma once

#include "IDrawable.hpp"
#include "Vertex.hpp"

class Line : public IDrawable
{
public:
	inline static unsigned char Color[4] = { 200, 200, 200, 255 };

public:
	Line(const Vertex* a, const Vertex* b);

	void Draw(SDL_Renderer* renderer) override;

private:
	const Vertex* a;
	const Vertex* b;
};