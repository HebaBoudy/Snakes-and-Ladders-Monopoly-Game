#pragma once

#include "Action.h"

class AddSnakeAction : public Action
{

	CellPosition sPos;
	CellPosition ePos;
	bool valid=true;

public:

	AddSnakeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~AddSnakeAction();

};

