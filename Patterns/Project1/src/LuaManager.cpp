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
	lua_register(L, "SetGameObject", LuaSetGameObject);
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

void LuaManager::ExecuteStateWithFile(lua_State* L, const std::string& scriptName)
{
	if (CheckLua(L, luaL_dofile(L, scriptName.c_str())))
	{

	}
	//	model = nullptr;
}

void LuaManager::SetModel( Model*& model)
{
	this->model = model;
	
}

void LuaManager::SetModelList(const std::vector<Model*>& modelList)
{
	for (Model* model : modelList)
	{
		modelMap[model->id] = model;
	}
}

void LuaManager::FindModelBasedOnName(const std::string& name)
{
	if (!name.empty())
	{
		model = modelMap[name];
	}
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

	glm::vec3 target(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));
	float easeInTime;
	float easeOutTime;

	Command* command = nullptr;

	switch (paramLength)
	{
	case 4: 
		command = new MoveTo(GetInstance().model, target, time);
		break;
	case 5:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		command = new MoveTo(GetInstance().model, target, time, easeInTime);
		break;
	case 6:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));
		command = new MoveTo(GetInstance().model, target, time, easeInTime, easeOutTime);
		break;
	}

	CommandManager::GetInstance().AddCommands(command);  

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

int LuaManager::LuaSetGameObject(lua_State* L)
{
	int paramLength = lua_gettop(L);

	std::string gameObjectName = lua_tostring(L, 1);
	std::cout << "GameObject name :" << gameObjectName << std::endl;
	GetInstance().FindModelBasedOnName(gameObjectName);

	return 0;
}

