#pragma once
#include "IModel.h"
#include "IMaterial.h"

class PrimitiveFactory
{
public:
	static std::unique_ptr<IModel> create_sphere(IMaterial* brush, coord radius, int refinements = 3);
	static std::unique_ptr<IModel> create_cube(IMaterial* brush, coord radius);
	static std::unique_ptr<IModel> create_prism(IMaterial* brush, box6 bounds);
};

