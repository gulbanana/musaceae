#pragma once
#include <string>
#include "IComponent.h"

class CLabel : public IComponent
{
public:
	static const ID ID = ID::Label;
	std::string text;

	CLabel(std::string t) : text(t) {}
};

