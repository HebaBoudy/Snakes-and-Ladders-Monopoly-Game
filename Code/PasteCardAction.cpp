#include "PasteCardAction.h"
#include "Output.h"
#include"Input.h"
#include "Grid.h"
#include "Ladder.h"
#include"Snake.h"
#include"Card.h"
#include"CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"CardSeven.h"
#include"CardEight.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"
#include"CardTwelve.h"
PasteCardAction::PasteCardAction(ApplicationManager* pApp) :Action(pApp) {
	checkpaste = true;
}

PasteCardAction::~PasteCardAction() {

}

void PasteCardAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Paste Card: Click on Cell to Paste ...");
	newcellPos = pIn->GetCellClicked();
	if (newcellPos.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Destination Cell Invalid! Click to continue...");
		pOut->ClearStatusBar();
		checkpaste = false;
		return;
	}
	if (newcellPos.GetCellNum() == 1 || newcellPos.GetCellNum() == 99) {
		pGrid->PrintErrorMessage("Error! Cannot place objects in 1st or last cell. Click to Continue...");
		pOut->ClearStatusBar();
		checkpaste = false;
		return;
	}
	Ladder* HasLadder = pGrid->GetLadder(newcellPos);
	if (HasLadder)
		if (HasLadder->GetPosition().GetCellNum() == newcellPos.GetCellNum())
		{
			pGrid->PrintErrorMessage(" Cell already has an object ! Click to continue ...");
			pOut->ClearStatusBar();
			checkpaste = false;
			return;
		}
	Snake* HasSnake = pGrid->GetSnake(newcellPos);
	if (HasSnake)
	{
		if (HasSnake->GetPosition().GetCellNum() == newcellPos.GetCellNum())
		{
			pGrid->PrintErrorMessage(" Cell already has an object ! Click to continue ...");
			pOut->ClearStatusBar();
			checkpaste = false;
			return;
		}
	}
	pOut->ClearStatusBar();
}

void PasteCardAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	if (checkpaste == true)
	{
		if (pGrid->GetClipboard()) {
			Card* pastecard;
			int cardnum = pGrid->GetClipboard()->GetCardNumber();
			switch (cardnum) {
			case 1:
				pastecard = new CardOne(*(dynamic_cast <CardOne*> (pGrid->GetClipboard())));
				break;


			case 2:
				pastecard = new CardTwo(*(dynamic_cast <CardTwo*> (pGrid->GetClipboard())));
				break;

			case 3:
				pastecard = new CardThree(*(dynamic_cast <CardThree*> (pGrid->GetClipboard())));
				break;



			case 4:
				pastecard = new CardFour(*(dynamic_cast <CardFour*> (pGrid->GetClipboard())));
				break;

			case 5:
				pastecard = new CardFive(*(dynamic_cast <CardFive*> (pGrid->GetClipboard())));
				break;

			case 6:
				pastecard = new CardSix(*(dynamic_cast <CardSix*> (pGrid->GetClipboard())));
				break;

			case 7:
				pastecard = new CardSeven(*(dynamic_cast <CardSeven*> (pGrid->GetClipboard())));
				break;

			case 8:
				pastecard = new CardEight(*(dynamic_cast <CardEight*> (pGrid->GetClipboard())));
				break;

			case 9:
				pastecard = new CardNine(*(dynamic_cast <CardNine*> (pGrid->GetClipboard())));
				break;

			case 10:
				pastecard = new CardTen(*(dynamic_cast <CardTen*> (pGrid->GetClipboard())));
				break;

			case 11:
				pastecard = new CardEleven(*(dynamic_cast <CardEleven*> (pGrid->GetClipboard())));
				break;

			case 12:
				pastecard = new CardTwelve(*(dynamic_cast <CardTwelve*> (pGrid->GetClipboard())));
				break;

			}
			pastecard->setPosition(newcellPos);
			bool added = pGrid->AddObjectToCell(pastecard);
			if (!added) {
				pGrid->PrintErrorMessage("Cell Already has an object!");
			}
			pastecard = NULL;
			return;
		}
	}
	else {
		pGrid->PrintErrorMessage("There is no card to paste!");
	}

}