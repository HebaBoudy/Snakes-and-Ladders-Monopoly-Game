#pragma once
#include "Action.h"
class SwitchToPlayMode :
	public Action
{
	string isswitch;
public:
	SwitchToPlayMode(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToPlayMode();
};

