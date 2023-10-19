#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../ScriptSystem/ScriptProxy.h"
#include "../tinyxml2/tinyxml2.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, ScriptProxy* scriptProxy);

	void Update();
private:
	flecs::world ecs;
	tinyxml2::XMLDocument doc;
};

