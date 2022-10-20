#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,
	ADD_SNAKE,
	ADD_CARD,
	CUT_CARD,
	COPY_CARD,
	DELETE_CARD,
	PASTE_CARD,
	SAVE_GRID,
	OPEN_GRID,
	EXIT,
	TO_PLAY_MODE,
	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	ROLL_DICE,		// Roll Dice Action
	TO_DESIGN_MODE,	// Go to Design Mode
	NEW_GAME,
	INPUT_DICE_VALUE,
	EXIT_PLAY_MODE,


	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS,			// Inside StatusBar Area
};

#endif 