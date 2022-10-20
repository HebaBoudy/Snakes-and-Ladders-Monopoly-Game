#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include"Snake.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	 valid = true;
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();



	///TODO: Make the needed validations on the read parameters
	if (startPos.VCell() == (NumVerticalCells - NumVerticalCells))
	{
		valid = false;
		pGrid->PrintErrorMessage("startcell of ladder cannot be in first row");
		return;

	}
	if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid->PrintErrorMessage(" The end cell can't be the start cell !");
		pOut->ClearStatusBar();
		valid = false;
		return;
	}
	if (startPos.HCell() != endPos.HCell())
	{
		valid = false;
		pGrid->PrintErrorMessage("end cell and start cell must be in the same column");
		return;
	}
	if (pGrid->GetCard(startPos))
	{
		pGrid->PrintErrorMessage(" The start cell cannot be a card !");
		pOut->ClearStatusBar();
		valid = false;
		return;
	}
	if (startPos.GetCellNum() == 99 || endPos.GetCellNum() == 1)
	{
		pGrid->PrintErrorMessage(" You cannot place game objects in the first or last cell! Click to continue ...");
		pOut->ClearStatusBar();
		valid = false;
		return;
	}
	for (int i = startPos.GetCellNum(); i <= endPos.GetCellNum(); i += 11)
	{
		CellPosition check(i);
		Ladder* checkoverlap = pGrid->GetNextLadder(check);
		if (checkoverlap) {
			if (check.HCell() == checkoverlap->GetPosition().HCell()) {
				if (startPos.VCell() >= checkoverlap->GetPosition().VCell() && endPos.VCell() <= checkoverlap->GetEndPosition().VCell()) {
					pGrid->PrintErrorMessage(" Two ladders cannot overlap !");
					pOut->ClearStatusBar();
					valid = false;
					return;
				}
			}

		}
		Snake* checkSnake = pGrid->GetNextSnake(endPos);
		if (checkSnake)
		{
			if (endPos.HCell() == checkSnake->GetEndPosition().HCell() && endPos.VCell() == checkSnake->GetEndPosition().VCell())
			{
				pGrid->PrintErrorMessage(" End cell cannot be a start of another ladder or snake !");
				pOut->ClearStatusBar(); valid = false;
				return;
			}

		}
		checkSnake = pGrid->GetNextSnake(startPos);
		if (checkSnake)
		{
			if (startPos.HCell() == checkSnake->GetEndPosition().HCell() && startPos.VCell() == checkSnake->GetEndPosition().VCell())
			{
				pGrid->PrintErrorMessage(" End cell cannot be a start of another ladder or snake !");
				pOut->ClearStatusBar(); valid = false;
				return;
			}

		}

		if (startPos.HCell() == endPos.HCell())
		{
			if (startPos.GetCellNum() != endPos.GetCellNum())
			{
				if (startPos.VCell() != NumVerticalCells - 1)
				{
					if (startPos.VCell() != (NumVerticalCells - NumVerticalCells))
						valid = true; return;

				}
			}
		}


		if (!valid)
		{
			startPos = 0;
			endPos = 0;
		}

		// Clear messages
		pOut->ClearStatusBar();
	}

}
// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (valid == true) {
		// Create a Ladder object with the parameters read from the user
		Ladder* pLadder = new Ladder(startPos, endPos);     //to make the ladder"drawing it"

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager




		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pLadder);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

	}
}