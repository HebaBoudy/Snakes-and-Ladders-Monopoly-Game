#include "SwitchToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

SwitchToPlayMode::SwitchToPlayMode(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayMode::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	
	pGrid->PrintErrorMessage("Are you sure you want to go to Play Mode? y/n");
	isswitch = pIn->GetSrting(pOut);
	/*
	pOut->PrintMessage("Switching To Play Mode: Click Anywhere to Continue ...");
	int x, y;
	*/
	pOut->ClearStatusBar();
	
}

void SwitchToPlayMode::Execute() {
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (isswitch == "y") {
		pOut->CreatePlayModeToolBar();
	}

}

SwitchToPlayMode::~SwitchToPlayMode() {

}