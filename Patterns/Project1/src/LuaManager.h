#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <lua.hpp>
#include <iostream>
#include "CommandManager.h"
#include "model.h"
#include "GraphicsRender.h"
#include "PhysicsEngine.h"


class MoveTo;
class OrientTo;
class FollowObject;
class WaitForSeconds;
class GameObject;
class MoveAlongAxisWithTime;
class ScaleTo;
class RotateAlongAxisWithTime;
class SphereTest;

class LuaManager
{
public:

	~LuaManager();

	static LuaManager& GetInstance();

	void RegisterCommands(lua_State* L);
	void ExecuteStateWithFile(lua_State* L, const std::string& scriptName, Model*& model);
	void ExecuteStateWithFile(lua_State* L, const std::string& scriptName);

	void SetModel(Model*& model);
	void SetModelList(const std::vector<Model*>& modelList);
	void SetGameObjectList(const std::vector<GameObject*>& GameobjectList);


	

	void FindModelBasedOnName(const std::string& name);
	void AddModelsInMap(Model* model);

	bool CheckLua(lua_State* L, int r);

	Model* FindModel(const std::string& name);
	 Model* GetModel();

	 std::map<std::string, Model*> modelMap;

	 std::map<std::string, GameObject* > gameObjectMap;
private:

	LuaManager();
	


	static int LuaBeginCommand(lua_State* L);
	static int LuaEndCommand(lua_State* L);

	static int LuaMoveToWrapper(lua_State* L);
	static int LuaOrientToWrapper(lua_State* L);
	static int LuaScaleToWrapper(lua_State* L);

	static int LuaSetGameObject(lua_State* L);

	static int LuaFollowObject(lua_State* L);

	static int LuaSpawnGameObject(lua_State* L);

	static  int LuaWaitForSeconds(lua_State* L);
	static  int LuaMoveAlongAxis(lua_State* L);
	static  int LuaRotateAlongAxis(lua_State* L);

	Model* model;

	GraphicsRender* renderer;
	Shader* shader;
	PhysicsEngine* engine;

};

