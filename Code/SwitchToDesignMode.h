#pragma once
#include "Action.h"
class SwitchToDesignMode :
	public Action
{
	string isswitch;
public:
	SwitchToDesignMode(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToDesignMode();
};

