#include <iostream>
#include <vector>

#include <SDL.h>

#include "BezierCurve.hpp"

#undef main

std::vector<BezierCurve*> curves;

void AddVertex(int x, int y, BezierCurve** curve);

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Bezier Curves",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 800,
		SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cerr << "Could not create window" << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr)
	{
		std::cerr << "Could not create renderer" << std::endl;
		return 1;
	}

	SDL_Event e;
	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	BezierCurve* currentCurve = nullptr;

	Vertex cursor(mouseX, mouseY, Vertex::Cursor);

	bool isOpen = true;
	while (isOpen)
	{
		while (SDL_PollEvent(&e))
		{
			if(e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					isOpen = false;
					break;
				}
			}

			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				cursor.SetPos(mouseX, mouseY);
				if (currentCurve != nullptr)
				{
					currentCurve->SetPreviewVertex(mouseX, mouseY);
					currentCurve->ConstructBezier(0.05);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
					AddVertex(mouseX, mouseY, &currentCurve);
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					if (currentCurve == nullptr)
						break;

					if (currentCurve->GetVertexCount() > 1)
					{
						currentCurve->Confirm();
						curves.push_back(currentCurve);
					}

					currentCurve = nullptr;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		for (BezierCurve* curve : curves)
			curve->Draw(renderer);

		if(currentCurve != nullptr)
			currentCurve->Draw(renderer);

		cursor.Draw(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

void AddVertex(int x, int y, BezierCurve** curve)
{
	if (*curve == nullptr)
		(*curve) = new BezierCurve;

	(*curve)->AddVertex(x, y);

	if ((*curve)->GetVertexCount() == 4)
	{
		(*curve)->Confirm();
		curves.push_back(*curve);
		*curve = nullptr;
	}
}