#pragma once

#include "../RenderObject.h"

class Pyramide : public RenderObject
{
private:
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		
		float m_z;
		uint32_t m_abgr;
	};
public:
	Pyramide();

private:
	inline static const PosColorVertex s_pyramideVertices[] =
	{ 
		{ 1.0f,  1.0f,  0.0f, 0xff000000 },
		{ 1.0f, -1.0f,  0.0f, 0xff0000ff },
		{-1.0f,  1.0f,  0.0f, 0xff00ff00 },
		{-1.0f, -1.0f,  0.0f, 0xff00ffff },
		{ 0.0f,  0.0f,  2.0f, 0xffff0000 },
	};

	inline static const uint16_t s_pyramideTriList[] =
	{
		0, 2, 4,
		0, 4, 1,
		2, 3, 4,
		3, 1, 4,
		0, 3, 2,
		0, 1, 3,
	};
};

