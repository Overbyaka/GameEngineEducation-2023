#define SOL_ALL_SAFETIES_ON 1

#include "ScriptProxy.h"
#include "../GameEngine/InputHandler.h"
//#include <fstream>

void ScriptProxy::Init(const char* filename)
{
	lua_script.open_libraries(sol::lib::base);
	/*std::ifstream f(filename);
	std::string lua_code = "", temp = "";
	while (std::getline(f, temp))
	{
		lua_code += temp;
	}*/

	InputHandler* inputHandler = new InputHandler();

	lua_script.new_usertype<InputHandler>("InputHandler", 
		"TestInput", &(InputHandler::Test));


	lua_script.script_file(filename);
}
void ScriptProxy::Update()
{
	//lua_script["Update"]();
}
