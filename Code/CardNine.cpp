#include "CardNine.h"
#include<fstream>
#include"Grid.h"


CardNine::CardNine(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9 here)
	owner = NULL;
	
	sold = false;
	 
	ownernumber = 0, ownerCellNumber = 0, passerCellNumber = 0, PasserNumber = 0;
}

CardNine::CardNine()
{ 
	cardNumber = 9; 
	owner = NULL;
	sold = false;
	
	ownernumber = 0, ownerCellNumber = 0, passerCellNumber = 0, PasserNumber = 0;
} //deafult constructor
CardNine::~CardNine(void)
{
}
void CardNine::ReadCardParameters(Grid* pGrid) 
{
	
		Input* pIn = pGrid->GetInput();

		Output* pOut = pGrid->GetOutput();

		pOut->PrintMessage("New CardNine: Enter its price");

		CardPrice = pIn->GetInteger(pOut);

		while (CardPrice < 0) // asks the user to re-enter each time  if he entered negative number
		{
			pOut->PrintMessage("Invalid Amount, please re-enter");

			CardPrice = pIn->GetInteger(pOut);
		}
		pOut->ClearStatusBar();
		pOut->PrintMessage("Enter CardNine passer by fees");

		PasserFees = pIn->GetInteger(pOut);

		while (PasserFees < 0) // asks the user to re-enter each time  if he entered negative number
		{
			pOut->PrintMessage("Invalid Amount, please re-enter");

			CardPrice = pIn->GetInteger(pOut);
		}
		pOut->ClearStatusBar();
		
	
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	//ReadCardParameters(pGrid);

	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	CellPosition PasserPosition;
	string answer;
	int x, y;
	if (sold == false)
	{

		pOut->PrintMessage("Do you want to buy this card?(y/n)");
		answer = pIn->GetSrting(pOut);
	}
	int playernumber;
	if (sold == false)
	{
		if (answer =="y")
		{

			if ((pPlayer->GetWallet() >= CardPrice))
			{
				pPlayer->decrementWallet(CardPrice);
				pOut->PrintMessage("You own this card now! ");
				sold = true;
				owner = pPlayer;

				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				ownerCellNumber = owner->GetCell()->GetCellPosition().GetCellNumFromPosition(owner->GetCell()->GetCellPosition());
				ownernumber = owner->getPlayerNum();
			}
		}
	}
	if(sold==true)
	{
		PasserPosition = pPlayer->GetCell()->GetCellPosition();
		passerCellNumber = PasserPosition.GetCellNumFromPosition(PasserPosition);
		PasserNumber = pPlayer->getPlayerNum();
			if (PasserNumber != ownernumber && passerCellNumber == ownerCellNumber) //check that the passer passes on the owner 's card
			{
				pPlayer->decrementWallet(PasserFees);
			
				int temp = owner->GetWallet() + PasserFees;
				owner->SetWallet(temp);
				pOut->PrintMessage(" Owner  new Wallet = " + to_string(owner->GetWallet())+" , Passer  new Wallet = " + to_string(pPlayer->GetWallet()));
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
			}
			/*for (int i = 1; i < 99; i++)
			{
				
				CellPosition positon=pGrid->setall9(pPlayer);
				pPlayer->decrementWallet(PasserFees);

				int temp = owner->GetWallet() + PasserFees;
				owner->SetWallet(temp);
				pOut->PrintMessage(" Owner  new Wallet = " + to_string(owner->GetWallet()) + " , Passer  new Wallet = " + to_string(pPlayer->GetWallet()));
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				
			}*/
	}
}
void CardNine::Save(ofstream& OutFile, int objecttype)
{
	if (checkcardsave == false) {
		if (objecttype == 3) {
			OutFile << cardNumber << " " << position.GetCellNum() << " " << CardPrice << " " << PasserFees << endl;
			checkcardsave = true;
		}

	}
	else {
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}
void CardNine::Load(ifstream& Infile)
{
	if (checkcardload == false)
	{
		int  cellposition;
		Infile >> cellposition >> CardPrice >> PasserFees;
		CellPosition Loadpos(cellposition);
		position = Loadpos;
		checkcardload = true;
	}
	else
	{
		int  cellposition;
		Infile >> cellposition;
		CellPosition LoadPos(cellposition);
		position = LoadPos;
	}
}

