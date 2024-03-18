#include "ConsoleLibrary.h"

// @ProgrammingKnowledge - Creating Simple Snake Game in C++ (With Source Code) - YouTube

using namespace ConsoleLibrary;

int main() {
	// Randomizer
	srand(time(NULL));

	Snake User; // Create a Snake Object with the new position
	Apple Apple; // Create an Apple Object with the new position

	bool playing = true;

	Mapping::printTitle();
	system("pause");

	do {
		Utility::resetAll(User);
		int points = 0;

		system("cls");
		Mapping::printEmptyMap();
		system("cls");

		User.spawnSnake(); // Alter the default position of the Snake
		Apple.spawnApple(); // Alter the default position of the apple
		
		std::vector<COORD> snakeBody = User.get_body();

		while (!Snake::collided) {
			Mapping::printMap(User, Apple); // Prints the map, user and apple

			Utility::input(User); // Gets user input
			User.move(); // Moves snake depending on user direction

			if (Apple.eaten(User)) {
				points++;
				Apple.spawnApple();
				User.speedUp();
				User.grow();
			}

			Utility::gameTick(User); // Ticks faster the quicker the speed is
			std::cout << points << "    \n"; // Spaces to avoid non-re-writing of data
			if (!Snake::collided) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // Resets console cursor to avoid screen-blinking, still shows the cursor moving though :c
			}
		}
	} while (Utility::replay());

}