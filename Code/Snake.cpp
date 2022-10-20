//done
#include "Snake.h"
#include "Input.h"
#include "Snake.h"
#include "Input.h"
#include"Output.h"
#include<fstream>

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	if (startCellPos.IsValidCell())
	{
		if (startCellPos.HCell() == endCellPos.HCell() && startCellPos.VCell() < endCellPos.VCell())
			this->endCellPos = endCellPos;
	}


	///TODO: Do the needed validation
}
Snake::Snake() {};//deafult constructor

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{
	//GameObject::Apply(pGrid,pPlayer);
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("You have reached a Snake. Click to continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();

	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click
	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that


}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

void Snake::Save(ofstream& savefile, int objecttype)
{
	if (objecttype == 2) {
		savefile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
	}
}

void Snake::Load(ifstream& savefile) {
	int startcell, endcell;
	savefile >> startcell >> endcell;
	CellPosition startc(startcell);
	CellPosition endc(endcell);
	position = startc;
	endCellPos = endc;
}


Snake::~Snake()
{
}



