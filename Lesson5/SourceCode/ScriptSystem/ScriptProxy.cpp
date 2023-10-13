#pragma once

#include "ScriptProxy.h"

//#include <fstream>

void ScriptProxy::Init(const char* filename)
{
	/*std::ifstream f(filename);
	std::string lua_code = "", temp = "";
	while (std::getline(f, temp))
	{
		lua_code += temp;
	}*/

	

	//lua_script.new_usertype<InputHandler>("InputHandler", 
		//"TestInput", &(InputHandler::Test));


	lua_script.safe_script_file(filename);
}
void ScriptProxy::UpdateInputHandler()
{
	inputHandler->Update();
	//lua_script["Update"]();
}
sol::state& ScriptProxy::GetLua()
{
	return lua_script;
}
void ScriptProxy::ScriptMove()
{
	lua_script["eIC_GoLeft"] = eIC_GoLeft;
	lua_script["eIC_GoRight"] = eIC_GoRight;
	lua_script["eIC_Jump"] = eIC_Jump;
	lua_script.new_usertype<std::bitset<eIC_Max>>("Bitset",
		"test", &std::bitset<eIC_Max>::test);
	lua_script.new_usertype<InputHandler>("InputHandler",
		"getInputState", &InputHandler::GetInputState);
}
