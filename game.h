#ifndef GAME_H
#define GAME_H

#include<string>
#include "globals.h"

class Arena;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nRats);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;

	// Helper functions
	std::string takePlayerTurn();
};

#endif
