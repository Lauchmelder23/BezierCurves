#include "BezierCurve.hpp"

#include <math.h>
#include <iostream>

#include <SDL.h>

#define C(n, k) (tgamma(n+1) / (tgamma(k+1) * tgammal(n-k+1)))

BezierCurve::BezierCurve()
{
	vertices.fill(nullptr);
	lines.fill(nullptr);
}

void BezierCurve::AddVertex(int x, int y)
{
	vertices[numVertices++] = new Vertex(x, y);
	if (numVertices > 1)
		lines[numLines++] = new Line(vertices[numVertices - 2], vertices[numVertices - 1]);
}

void BezierCurve::Confirm()
{
	if (numLines > 1)
	{
		lines[numLines] = new Line(vertices[numLines], vertices[0]);
		numLines++;
	}

	inProgress = false;
	ConstructBezier(0.05);
}

void BezierCurve::SetPreviewVertex(int x, int y)
{
	if (vertices[numVertices] == nullptr)
		vertices[numVertices] = new Vertex(x, y, Vertex::Cursor);
	else
		vertices[numVertices]->SetPos(x, y);
}

void BezierCurve::ConstructBezier(float resolution)
{
	int grade = numVertices - 1;
	if (vertices[grade] != nullptr && inProgress)
		grade++;

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

	for (int i = 0; i < numLines; i++)
		lines[i]->Draw(renderer);

	if (bezier.size() != 0)
	{
		SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], Color[3]);
		SDL_RenderDrawLinesF(renderer, &bezier[0], bezier.size());
	}
}
