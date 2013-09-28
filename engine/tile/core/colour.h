#pragma once

struct colour
{
	const float r;
	const float g;
	const float b;
	const float a;

	colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0f) {}
	colour(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

	bool operator==(colour const& c) const { return r == c.r && g == c.g && b == c.b && a == c.a; }
	bool operator!=(colour const& c) const { return r != c.r || g != c.g || b != c.b || a != c.a; }

	colour withOpacity(float opacity) const { return colour(r, g, b, opacity); }

	static const colour RED;
	static const colour GREEN;
	static const colour BLUE;
	static const colour CYAN;
	static const colour MAGENTA;
	static const colour YELLOW;
	static const colour BLACK;
	static const colour WHITE;
};