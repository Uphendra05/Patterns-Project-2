#include "LuaManager.h"
#include "MoveTo.h"
#include "OrientTo.h"
#include "FollowObject.h"
#include "WaitForSeconds.h"
#include "MoveAlongOneAxisWithTime.h"
#include "GameObject.h"
#include "ScaleTo.h"
#include "Sphere.h"
#include "RotateAlongAxisWithTime.h"

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
	lua_register(L, "OrientTo", LuaOrientToWrapper);
	lua_register(L, "ScaleTo", LuaScaleToWrapper);
	lua_register(L, "Endcommand", LuaEndCommand);
	lua_register(L, "FollowObject", LuaFollowObject);
	lua_register(L, "SpawnObject", LuaSpawnGameObject);
	lua_register(L, "WaitForSeconds", LuaWaitForSeconds);
	lua_register(L, "MoveAlongAxisWithTime", LuaMoveAlongAxis);
	lua_register(L, "RotateAlongAxisWithTime", LuaRotateAlongAxis);

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

void LuaManager::SetGameObjectList(const std::vector<GameObject*>& GameobjectList)
{
	for (GameObject* gameObject : GameobjectList)
	{
		gameObjectMap[gameObject->id] = gameObject;
	}
}





void LuaManager::FindModelBasedOnName(const std::string& name)
{
	if (!name.empty())
	{
		model = modelMap[name];
	}
}

void LuaManager::AddModelsInMap(Model* model)
{
	if (model!=nullptr)
	{
		modelMap[model->id] = model;
	}
}

Model* LuaManager::FindModel(const std::string& name)
{
	if (!name.empty())
	{
		return modelMap[name];
	}
	else
	{
		std::cout << "Follow model is null" << std::endl;
		return nullptr;
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

	glm::vec3 targetRotation(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));
	float easeInTime;
	float easeOutTime;

	Command* command = nullptr;

	switch (paramLength)
	{
	case 4:
		command = new OrientTo(GetInstance().model, targetRotation, time);
		break;
	case 5:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		command = new OrientTo(GetInstance().model, targetRotation, time, easeInTime);
		break;
	case 6:
		easeInTime = static_cast<float>(lua_tonumber(L, 5));
		easeOutTime = static_cast<float>(lua_tonumber(L, 6));
		command = new OrientTo(GetInstance().model, targetRotation, time, easeInTime, easeOutTime);
		break;
	}

	CommandManager::GetInstance().AddCommands(command);
	return 0;
}

int LuaManager::LuaScaleToWrapper(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float x = static_cast<float>(lua_tonumber(L, 1));
	float y = static_cast<float>(lua_tonumber(L, 2));
	float z = static_cast<float>(lua_tonumber(L, 3));

	glm::vec3 targetScale(x, y, z);

	float time = static_cast<float>(lua_tonumber(L, 4));


	Model* model = GetInstance().model;

	Command* command = new ScaleTo(model, targetScale, time);

	CommandManager::GetInstance().AddCommands(command);

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

int LuaManager::LuaFollowObject(lua_State* L)
{
	int paramLength = lua_gettop(L);

	std::string followObjectName = lua_tostring(L, 1);

	float speed = static_cast<float>(lua_tonumber(L, 2));
	float acceleration = static_cast<float>(lua_tonumber(L, 3));
	float deceleration = static_cast<float>(lua_tonumber(L, 4));
	float distance = static_cast<float>(lua_tonumber(L, 5));

	float x = static_cast<float>(lua_tonumber(L, 6));
	float y = static_cast<float>(lua_tonumber(L, 7));
	float z = static_cast<float>(lua_tonumber(L, 8));

	glm::vec3 followOffset{ x,y,z };

	Model* targetModel = GetInstance().FindModel(followObjectName);

	Command* command = nullptr;

	command = new FollowObject(GetInstance().model, targetModel, speed, acceleration, deceleration, distance, followOffset);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaSpawnGameObject(lua_State* L)
{
	int paramLength = lua_gettop(L);
	std::string GameObjectName = lua_tostring(L, 1);

	if (GameObjectName =="SphereTest")
	{
		GameObject* gameObject = new SphereTest();
		

		GetInstance().AddModelsInMap(gameObject->model);
	}


	

	

	return 0;
}

int LuaManager::LuaWaitForSeconds(lua_State* L)
{
	int paramLength = lua_gettop(L);

	float waitTime = static_cast<float>(lua_tonumber(L, 1));

	Command* command = new WaitForSeconds(waitTime);
	
	CommandManager::GetInstance().AddCommands(command);
	return 0;
}

int LuaManager::LuaMoveAlongAxis(lua_State* L)
{
	int paramLength = lua_gettop(L);

	int axis = lua_tonumber(L, 1);

	float time = static_cast<float>(lua_tonumber(L, 2));
	float speed = static_cast<float>(lua_tonumber(L, 3));

	
	Model* model = GetInstance().model;

	Command* command = new MoveAlongAxisWithTime(model,axis,time,speed);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

int LuaManager::LuaRotateAlongAxis(lua_State* L)
{
	int paramLength = lua_gettop(L);

	int axis = lua_tonumber(L, 1);

	float time = static_cast<float>(lua_tonumber(L, 2));
	float speed = static_cast<float>(lua_tonumber(L, 3));


	Model* model = GetInstance().model;

	Command* command = new RotateAlongAxisWithTime(model, axis, time, speed);

	CommandManager::GetInstance().AddCommands(command);


	return 0;
}

