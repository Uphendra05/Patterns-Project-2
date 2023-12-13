#include "GameObject.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
}

void GameObject::SetGameObjectId(const std::string& id)
{
	this->id = id;
}
