#pragma once

#include "Action.h"

class InputDiceValue : public Action
{
	int DiceValue;
	int i;

public:
	InputDiceValue();
	InputDiceValue(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValue();
};