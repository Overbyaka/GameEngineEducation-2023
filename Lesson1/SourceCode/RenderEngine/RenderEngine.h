#pragma once

#include "Common.h"
#include "RenderObject.h"
#include "DefaultGeometry/Cube.h"
#include "DefaultGeometry/Pyramide.h"

class RENDERENGINE_API CRenderEngine
{
public:
	CRenderEngine() = delete;
	CRenderEngine(HINSTANCE hInstance);
	CRenderEngine(const CRenderEngine& renderEngine) = delete;
	~CRenderEngine();

	void Update();

private:
	HWND InitMainWindow(HINSTANCE hInstance);
	HWND m_hwnd = nullptr;

	float r = 5.0f;
	float alpha = 0.0f;

	long m_Width = 800;
	long m_Height = 600;
	//Cube* m_defaultCube;
	Pyramide* m_defaultPyramide;
};
