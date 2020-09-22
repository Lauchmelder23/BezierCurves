#pragma once

struct SDL_Renderer;

class IDrawable
{
public:
	virtual void Draw(SDL_Renderer* renderer) = 0;

protected:
	IDrawable() = default;
};