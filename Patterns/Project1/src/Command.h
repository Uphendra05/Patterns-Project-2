#pragma once
#include "iCommand.h"
#include <string>

class Command : public iCommand
{
public:
	Command();
	virtual  ~Command();

	 virtual void Start();
	 virtual void Update(float deltatime);
	 virtual bool IsComplete();


	 std::string GetCommandID();
	 std::string commandId;

private:

};

