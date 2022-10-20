#include "OpenGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
#include "Ladder.h"
#include "Snake.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"


OpenGridAction::OpenGridAction(ApplicationManager* pApp) :Action(pApp) {
}

void OpenGridAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Open Grid: Enter File Name...");
	savefilename = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void OpenGridAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	pGrid->EmptyGrid();
	GameObject* pObj;
	ifstream savefile;
	int LadderCount, SnakeCount, CardCount;
	savefile.open(savefilename);
	savefile >> LadderCount;
	for (int i = 0; i < LadderCount; i++)
	{
		pObj = new Ladder();
		pObj->Load(savefile);
		pGrid->AddObjectToCell(pObj);
	}
	savefile >> SnakeCount;
	for (int i = 0; i < SnakeCount; i++)
	{
		pObj = new Snake();
		pObj->Load(savefile);
		pGrid->AddObjectToCell(pObj);
	}
	savefile >> CardCount;
	for (int i = 0; i < CardCount; i++)
	{
		int cardnum;
		savefile >> cardnum;
		switch (cardnum) {
		case 1:
			pObj = new CardOne();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 2:
			pObj = new CardTwo();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 3:
			pObj = new CardThree();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 4:
			pObj = new CardFour();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 5:
			pObj = new CardFive();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 6:
			pObj = new CardSix();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 7:
			pObj = new CardSeven();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		case 8:
			pObj = new CardEight();
			pObj->Load(savefile);
			pGrid->AddObjectToCell(pObj);
			break;
		}
	}savefile.close();
}

OpenGridAction::~OpenGridAction() {


}