#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	bool valid = true;

	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{

	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Snake! Click on snakes Start Cell ...");
	sPos = pIn->GetCellClicked();
	pOut->PrintMessage("Click on snakes End Cell ...");
	ePos = pIn->GetCellClicked();

	if (sPos.GetCellNum() == ePos.GetCellNum()) {
		pGrid->PrintErrorMessage("Start cell cannot be end cell...");
		valid = false;
		return;
	}
	if ((sPos.VCell() > ePos.VCell()))
	{
		valid = false;
		pGrid->PrintErrorMessage("the end cell cannot be above start cell");
		return;
	}
	if (sPos.VCell() == NumVerticalCells - NumVerticalCells)
	{
		valid = false;
		pGrid->PrintErrorMessage("the startcell of Snake in first row");
		return;
	}
	if (sPos.VCell() == (NumVerticalCells - 1))
	{

		valid = false;
		pGrid->PrintErrorMessage("the startcell of snake cannot be in last row");
		return;
	}
	if (pGrid->GetCard(sPos))
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a card ! Click to continue ...");
		pOut->ClearStatusBar();
		valid = false;
		return;
	}
	if (sPos.GetCellNum() == 99 || ePos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage(" You cannot place game objects in the first or last cell! Click to continue ...");
		pOut->ClearStatusBar();
		valid = false;
		return;
	}

	if (sPos.HCell() == ePos.HCell())
	{
		if (sPos.VCell() != NumVerticalCells - 1)
		{
			if (sPos.VCell() < ePos.VCell())
			{
				if (sPos.VCell() != (NumVerticalCells - NumVerticalCells))
					valid = true;
				return;
			}
		}
	}
	if (!valid)
	{
		sPos = 0;
		ePos = 0;
	}
}
void AddSnakeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Snake* s;
	ReadActionParameters();
	if (valid == true) {
		s = new Snake(sPos, ePos);

		bool added = pGrid->AddObjectToCell(s);
		if (!added)
		{
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}

	}
}