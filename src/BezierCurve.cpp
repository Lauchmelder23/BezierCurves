#include "BezierCurve.hpp"

#include <math.h>
#include <iostream>

#include <SDL.h>

#define C(n, k) (tgamma(n+1) / (tgamma(k+1) * tgammal(n-k+1)))

BezierCurve::BezierCurve()
{
}

void BezierCurve::AddVertex(int x, int y)
{
	numVertices++;
	if(numVertices != vertices.size())
		vertices.push_back(new Vertex(x, y));
	else
	{
		vertices.insert(vertices.end() - 1, new Vertex(x, y));
	}

	if (numVertices > 1)
		lines.push_back(new Line(vertices[numVertices - 2], vertices[numVertices - 1]));
}

void BezierCurve::Confirm()
{
	if (vertices.size() != numVertices)
	{
		delete vertices.back();
		vertices.pop_back();
	}

	if (lines.size() > 1)
	{
		lines.push_back(new Line(vertices.back(), vertices[0]));
	}

	inProgress = false;
	ConstructBezier(0.01);
}

void BezierCurve::SetPreviewVertex(int x, int y)
{
	if (numVertices == vertices.size())
		vertices.push_back(new Vertex(x, y, Vertex::Cursor));
	else
		vertices[numVertices]->SetPos(x, y);
}

void BezierCurve::ConstructBezier(float resolution)
{
	int grade = vertices.size() - 1;

	if (grade < 1)
		return;

	bezier.clear();

	std::vector<Uint32> binoms;
	for (int i = 0; i <= grade; i++)
		binoms.push_back(C(grade, i));

	SDL_FPoint vert;

	for (float t = 0; t <= 1.f; t += resolution)
	{
		vert = { 0, 0 };
		for (int i = 0; i <= grade; i++)
		{
			float f = binoms[i] * pow(t, i) * pow(1 - t, grade - i);
			vert.x += f * vertices[i]->x;
			vert.y += f * vertices[i]->y;
		}
		bezier.push_back(vert);
	}
	
	vert = { (float)vertices[grade]->x, (float)vertices[grade]->y };
	bezier.push_back(vert);
}

void BezierCurve::Draw(SDL_Renderer* renderer)
{
	for (int i = 0; i <  numVertices; i++)
		vertices[i]->Draw(renderer);

	for (Line* line : lines)
		line->Draw(renderer);

	if (bezier.size() != 0)
	{
		SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], Color[3]);
		SDL_RenderDrawLinesF(renderer, &bezier[0], bezier.size());
	}
}
