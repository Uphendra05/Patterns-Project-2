#pragma once
#include "model.h"

class GameObject
{
public:
	std::string id;
	GameObject();
	virtual ~GameObject();

	void SetGameObjectId(const std::string& id);
	Model* model = nullptr;

	Model* copyModel = nullptr;

	virtual Transform* GetTransform() = 0;
private:

protected : 

	


};

