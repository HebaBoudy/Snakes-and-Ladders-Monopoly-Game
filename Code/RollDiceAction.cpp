#include "RollDiceAction.h"
#include"Card.h"
#include "Grid.h"
#include "Player.h"
#include"GameObject.h"
#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Player* CurrentPlayer = pGrid->GetCurrentPlayer();

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	if (pGrid->GetEndGame() == true) {
		pOut->PrintMessage("This Game has ended. Click anywhere to continue...");
		int x, y;
		pIn->GetPointClicked(x, y);
		return;
	}
	//int cardNum = pGrid->GetCard(CurrentPlayer->GetCell()->GetCellPosition())->GetCardNumber();
	if (CurrentPlayer->GetcheckPreventMove())
	{
		int x, y;
		pOut->PrintMessage("you are prevented from moving this turn...click to continue");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		pGrid->AdvanceCurrentPlayer();
		CurrentPlayer->incrementTurnCount();
		return;
	}

	if (CurrentPlayer->GetCheckPrison())
	{
		int x, y;
		pOut->PrintMessage(" You are now in prison ...click to continue.");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();

		int PrisonedPlayerNum = CurrentPlayer->GetPrisonedPlayerNum();
		int r = CurrentPlayer->GetTurnCount();
		for (int i = r; i < 3; i++)
		{
			if (CurrentPlayer->getPlayerNum() == PrisonedPlayerNum)
			{
				pOut->PrintMessage("you're still in prison...click to continue.");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				pGrid->AdvanceCurrentPlayer();
				CurrentPlayer->incrementTurnCount();
				return;
			}
		}
	}

	// -- If not ended, do the following --:

		// 2- Generate a random number from 1 to 6 --> This step is done for you
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed
	string msg = "Your dice value : " + to_string(diceNumber);
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	// 3- Get the "current" player from pGrid
	CurrentPlayer->Move(pGrid, diceNumber);
	// 4- Move the currentPlayer using function Move of class player

	// 5- Advance the current player number of pGrid

	pGrid->AdvanceCurrentPlayer();
	// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

}

RollDiceAction::~RollDiceAction()
{
}
