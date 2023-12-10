#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <lua.hpp>
#include <iostream>
#include "CommandManager.h"
#include "model.h"


class MoveTo;
class OrientTo;
class FollowObject;

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


	void FindModelBasedOnName(const std::string& name);
	Model* FindModel(const std::string& name);

	bool CheckLua(lua_State* L, int r);

	 Model* GetModel();

	 std::map<std::string, Model*> modelMap;
private:

	LuaManager();
	


	static int LuaBeginCommand(lua_State* L);
	static int LuaEndCommand(lua_State* L);

	static int LuaMoveToWrapper(lua_State* L);
	static int LuaOrientToWrapper(lua_State* L);

	static int LuaSetGameObject(lua_State* L);

	static int LuaFollowObject(lua_State* L);

	Model* model;
	

};

