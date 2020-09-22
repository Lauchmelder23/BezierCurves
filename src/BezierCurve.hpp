#pragma once

#include <vector>

#include "UI/Vertex.hpp"
#include "UI/Line.hpp"

struct SDL_Renderer;
struct SDL_FPoint;

class BezierCurve : public IDrawable
{
public:
	inline static unsigned char Color[4] = { 20, 230, 20, 255 };
public:
	BezierCurve();

	void AddVertex(int x, int y);
	void Confirm();

	void SetPreviewVertex(int x, int y);

	uint8_t GetVertexCount() const { return numVertices; }

	void ConstructBezier(float resolution);

	void Draw(SDL_Renderer* renderer) override;

private:
	uint8_t numVertices = 0;
	std::vector<Vertex*> vertices;
	std::vector<Line*> lines;

	std::vector<SDL_FPoint> bezier;

	bool inProgress = true;
};