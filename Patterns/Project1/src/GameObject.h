#pragma once
#include "model.h"

class GameObject
{
public:
	std::string id;
	GameObject();
	~GameObject();

	void SetGameObjectId(const std::string& id);

	Model* model = nullptr;
	Model* copyModel = nullptr;
private:

};

