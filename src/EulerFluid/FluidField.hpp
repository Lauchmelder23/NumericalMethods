#pragma once

#include <vector>

class VectorField;
struct SDL_Renderer;
struct SDL_Rect;

enum class BoundaryCondition
{
	Continuous,
	InvertVertical,
	InvertHorizontal
};

class FluidField
{
public:
	FluidField(int size);
	~FluidField();

	void AddSource(int x, int y, double density, double dt);
	void AddFlow(int x, int y, double dx, double dy, double dt);
	void ApplyBoundaryConditions(BoundaryCondition condition, std::vector<double>& field);

	void Diffuse(double diff, double dt);
	void Advect(double dt);
	void DensityStep(double diff, double dt);

	void DiffuseVelocity(double visc, double dt);
	void AdvectVelocity(double dt);
	void VelocityStep(double visc, double dt);
	void Project();

	void Draw(SDL_Renderer* renderer, const SDL_Rect& target);

private:
	int size;

	VectorField* vel;
	VectorField* prevVel;
	std::vector<double>* density;
	std::vector<double>* prevDensity;

	int lastMouseX, lastMouseY;
};