#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "common.h"
#include "InputHandler.h"

class SCRIPTSYSTEM_API ScriptProxy
{
public:
	void Init(const char* filename);
	void UpdateInputHandler();
	void ScriptMove();
	sol::state &GetLua();
private:
	InputHandler *inputHandler = new InputHandler();
	sol::state lua_script;
};

