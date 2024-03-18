#include "ConsoleLibrary.h"

namespace ConsoleLibrary
{
	/*
	------------------------------------------------------------------------------------------------------------------------------------
	OTHER
	------------------------------------------------------------------------------------------------------------------------------------
	*/
	int Snake::length = 1;
	std::vector<COORD> Snake::body;
	int Snake::position[2];
	COORD Snake::positionC;
	double Snake::speed = 1;
	double Snake::pSpeed = 1;
	char Snake::dir;
	bool Snake::collided = false;

	int Apple::position[2];

	std::string Utility::answer = "";


	/*
	------------------------------------------------------------------------------------------------------------------------------------
	UTILITY
	------------------------------------------------------------------------------------------------------------------------------------
	*/
	void Utility::wait(int milliseconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		std::cout << "\n";
	}

	void Utility::input(Snake& snake) {
		if (_kbhit()) { // If KeyBoard Hit
			switch (_getch()) {
			case 'w':
				if (snake.dir != 'S') snake.dir = 'W';
				break;
			case 'a':
				if (snake.dir != 'D') snake.dir = 'A';
				break;
			case 's':
				if (snake.dir != 'W') snake.dir = 'S';
				break;
			case 'd':
				if (snake.dir != 'A') snake.dir = 'D';
				break;
			}
		}
	}

	void Utility::printC(std::string printed) {
		std::cout << "\t\t\t\t" << printed;
	}

	bool Utility::replay() {
		wait(200);
		printC("Want to play again ? Y / N\n");
		std::cin >> answer;

		for (int i = 0; i < answer.length(); i++)
		{
			answer[i] = toupper(answer[i]);
		}

		switch (answer[0]) {
		case 'Y':
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	void Utility::resetAll(Snake& Snake) {
		Snake.collided = false;
		Snake.length = 1;
		Snake.position[0] = 10;
		Snake.position[1] = 10;
		Snake.speed = 1;
		Snake.pSpeed = 1;
		Snake.dir = 'N';
	}

	void Utility::gameTick(Snake Snake) {
		wait((10 / Snake.pSpeed + (100 / Snake.speed) * 2) - 10);
		// 10 / 1 + (100 / 1) * 2 = 10 + 200 = 210 --> 200
		// 10 / 1 + (100/1.5)*2 = 10 + 75*2 = 160 --> 160
		// 10 / 2 + (100 / 2) * 2 = 5 + 100 = 105 --> 95
		// 10 / 2 + (100 / 2.5) * 2 = 5 + 75 - 10 --> 70
		// 10 / 3 + (100 / 3.8) * 2 - 10 = 3.3 + 30*2 -10 --> 53
	}

	/*
	------------------------------------------------------------------------------------------------------------------------------------
	MAPPING
	------------------------------------------------------------------------------------------------------------------------------------
	*/

	int Mapping::width = 50;
	int Mapping::height = 40;

	std::string Mapping::map[40][50]; // map[height][width]

	void Mapping::printTitle() {
		for (int i = 0; i < 5; i++)
		{
			std::cout << "\n";
		}
		std::cout <<
			"\t\t\t _____ _             ____                _     ____              _         \n" <<
			"\t\t\t|_   _| |__   ___   / ___|_ __ ___  __ _| |_  / ___| _ __   __ _| | _____ \n" <<
			"\t\t\t  | | | '_ \\ / _ \\ | |  _| '__/ _ \\/ _` | __| \\___ \\| '_ \\ / _` | |/ / _ \\ \n" <<
			"\t\t\t  | | | | | |  __/ | |_| | | |  __/ (_| | |_   ___) | | | | (_| |   <  __/\n" <<
			"\t\t\t  |_| |_| |_|\\___|  \\____|_|  \\___|\\__,_|\\__| |____/|_| |_|\\__,_|_|\\_\\___|\n";

		std::cout << "\n\n";
		Utility::printC("Please play in fullscreen for a better experience.");

		for (int i = 0; i < 5; i++)
		{
			std::cout << "\n";
		}
	}

	// Fills the map with dots and #s as walls, and prints it out.
	void Mapping::printEmptyMap() {

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == 0 || j == width - 1) {
					map[i][j] = "#";
				}
				else if (i == 0 || i == height - 1) {
					map[i][j] = "#";
				}
				else {
					map[i][j] = ".";
				}
				std::cout << map[i][j] << " ";
			}
			std::cout << "\n";
		}
		Utility::wait(400);
	}

	void Mapping::printMap(Snake snake, Apple apple) {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == snake.position[0] && i == snake.position[1]) {
					std::cout << "O ";
				}
				else if (j == apple.position[0] && i == apple.position[1]) {
					std::cout << "A ";
				}
				else {
					bool bodyPart = false;
					for (int k = 0; k < snake.body.size() - 1; k++) {
						if (i == snake.body[k].Y && j == snake.body[k].X) {
							std::cout << "o ";
							bodyPart = true;
							break;
						}
					}

					if (!bodyPart) std::cout << map[i][j] << " ";
				}
			}
			std::cout << "\n";
		}
	}

	/*
	------------------------------------------------------------------------------------------------------------------------------------
	SNAKE
	------------------------------------------------------------------------------------------------------------------------------------
	*/

	void Snake::spawnSnake() {
		bool randomizing = true;

		do {
			//Gets the row position
			position[0] = rand() % (Mapping::width - 1);

			//Gets the column position
			position[1] = rand() % (Mapping::height - 1);

			if (position[0] > 0 && position[1] > 0) {
				randomizing = false;
			}

		} while (randomizing);

		positionC.X = position[0];
		positionC.Y = position[1];
		body.push_back(positionC);
	}

	void Snake::move() {
		switch (dir) {
		case 'W': position[1] -= 1;
			break;
		case 'A': position[0] -= 1;
			break;
		case 'S': position[1] += 1;
			break;
		case 'D': position[0] += 1;
			break;
		}

		positionC.X = position[0];
		positionC.Y = position[1];

		if (position[0] == 0 || position[1] == 0 || position[0] == Mapping::width - 1 || position[1] == Mapping::height - 1) {
			collided = true;
			Utility::printC("Game Over\n");
		}
		for (int i = 0; i < length - 1; i++) {
			if (positionC.X == body[i].X && positionC.Y == body[i].Y) {
				collided = true;
			}
		}

		body.push_back(positionC);
		if (body.size() > length) {
			body.erase(body.begin());
		}
	}

	void Snake::grow() {
		length++;
	}

	void Snake::speedUp() {
		speed += 0.1;
		pSpeed = std::fmod(speed, 10) + (10 / speed); // speed%10 + 10/speed
		if (speed >= 2) (pSpeed = 3);
	}

	std::vector<COORD> Snake::get_body() {
		return body;
	}

	/*
	------------------------------------------------------------------------------------------------------------------------------------
	APPLE
	------------------------------------------------------------------------------------------------------------------------------------
	*/

	void Apple::spawnApple() {
		bool randomizing = true;
		int row, col;
		do {
			//Gets the row position
			row = rand() % (Mapping::width - 1);

			//Gets the column position
			col = rand() % (Mapping::height - 1);

			if (
				(row > 0 && col > 0) && // If Apple Location within map limits &&
				(row != Snake::position[0] && col != Snake::position[1]) // Apple Location != Snake Position
				) {
				randomizing = false;
				position[0] = row;
				position[1] = col;
			}
		} while (randomizing);
	}

	bool Apple::eaten(Snake snake) {
		if (position[0] == snake.position[0] && position[1] == snake.position[1]) {
			return true;
		}
		else {
			return false;
		}
	}
}