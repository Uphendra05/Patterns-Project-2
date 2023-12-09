#include "LuaManager.h"
#include "MoveTo.h"
LuaManager::LuaManager()
{
}

LuaManager::~LuaManager()
{
}

LuaManager& LuaManager::GetInstance()
{
	static LuaManager instance;
	return instance;
}

void LuaManager::RegisterCommands(lua_State* L)
{
	lua_register(L, "BeginCommand", LuaBeginCommand);
	lua_register(L, "MoveTo", LuaMoveToWrapper);
	lua_register(L, "Endcommand", LuaEndCommand);
//	lua_register(L, "_OrientTo", LuaOrientToWrapper);

}

void LuaManager::ExecuteStateWithFile(lua_State* L, const std::string& scriptName, Model*& modelref)
{
	    SetModel(modelref);

		if (!GetModel())
		{
			std::cout << "Model is null for script : " << scriptName << std::endl;
		}
		else
		{
			if (CheckLua(L, luaL_dofile(L, scriptName.c_str())))
			{

			}
		}

		model = nullptr;
		
}

void LuaManager::SetModel( Model*& model)
{
	this->model = model;
	
}

bool LuaManager::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

 Model* LuaManager::GetModel()
{
	
	return model;
}




int LuaManager::LuaBeginCommand(lua_State* L)
{
	int paramLength = lua_gettop(L);

	if (paramLength == 2)
	{
		std::string groupTypeStr = lua_tostring(L, 1); // Serial or Parallel
		int goupdId = lua_tonumber(L, 2); // Group ID
		int groupType = 0;


		if (groupTypeStr == "SERIAL")
		{
			groupType = 0;
		}
		else if (groupTypeStr == "PARALLEL")
		{
			groupType = 1;
		}
		std::cout << "BeginCommandGroup id: " << goupdId << std::endl;
		std::cout << "BeginCommandGroup Type: " << groupTypeStr << std::endl;

		CommandManager::GetInstance().BeginCommandGroup((CommandGroupType)groupType, goupdId);
	}
	else if(paramLength == 1)
	{
		int goupdId = lua_tonumber(L, 1); // Group ID

		std::cout << "BeginCommandGroup id: " << goupdId << std::endl;
		std::cout << "BeginCommandGroup Type: " << "SERIAL" << std::endl;

		CommandManager::GetInstance().BeginCommandGroup(SERIES, goupdId);
	}

	return 0;
}

int LuaManager::LuaEndCommand(lua_State* L)
{
	int paramLength = lua_gettop(L);
	int goupdId = lua_tonumber(L, 1);

	std::cout << "EndCommandGroup id: " << goupdId << std::endl;
	CommandManager::GetInstance().EndCommandGroup(goupdId);

	return 0;
}


int LuaManager::LuaMoveToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	std::cout << "x : " << x << " y: " << y << " z: " << z << std::endl;

	glm::vec3 target(x, y, z);
	Command* command = new MoveTo(GetInstance().model, target);

	CommandManager::GetInstance().AddCommands(command); // sending Serial command as of now

	return 0;
}

int LuaManager::LuaOrientToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	return 0;
}

