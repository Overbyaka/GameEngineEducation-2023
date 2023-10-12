#pragma once

#include <sol/sol.hpp>


class ScriptProxy
{
public:
	void Init(const char* filename);
	void Update();
private:
	sol::state lua_script;
};

