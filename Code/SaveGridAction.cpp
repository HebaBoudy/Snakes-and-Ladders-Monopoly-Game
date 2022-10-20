#include "SaveGridAction.h"
#include"Grid.h"
#include<fstream>
#include"Ladder.h"
#include"Snake.h"
#include"Card.h"
SaveGridAction::SaveGridAction(ApplicationManager* pApp) :Action(pApp) {
}

void SaveGridAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Save Grid: Enter File Name...");
	savefilename = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	ReadActionParameters();
	ofstream savefile;
	savefile.open(savefilename, ios::out);

	savefile << pGrid->CountLadders() << endl;
	pGrid->SaveAll(savefile, 1);
	savefile << pGrid->CountSnakes() << endl;
	pGrid->SaveAll(savefile, 2);
	savefile << pGrid->CountCards() << endl;
	pGrid->SaveAll(savefile, 3);

	savefile.close();
}

SaveGridAction::~SaveGridAction() {}