#include "SwitchToDesignMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToDesignMode::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pGrid->PrintErrorMessage("Are you sure you want to go to Design Mode? y/n");
	isswitch = pIn->GetSrting(pOut);
	pOut->PrintMessage("Switching To Design Mode: Click Anywhere to Continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void SwitchToDesignMode::Execute() {
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (isswitch == "y") {
		pOut->CreateDesignModeToolBar();
		pGrid->NewGame();
	}
}

SwitchToDesignMode::~SwitchToDesignMode() {

}