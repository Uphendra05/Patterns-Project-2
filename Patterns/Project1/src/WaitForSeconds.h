#pragma once

#include "Command.h"

class WaitForSecond  : public Command
{
public:

	WaitForSecond(float time);
	~WaitForSecond();

	 void Start() override;
	 void Update(float deltatime) override;
	 void SetStarted(bool isStarted) override;

	  bool IsComplete() override;
	  bool IsStarted() override;

private:

	float time;
	float timeStep= 0;

};

