#define MAIN_CPP
#include "utilities.cpp"
#include "rat.cpp"
#include "arena.cpp"
#include "player.cpp"
#include "game.cpp"


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 40);

      // Play the game
    g.play();
}

