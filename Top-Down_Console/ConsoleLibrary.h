// ConsoleLibrary.h

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <conio.h>
#include <future>
#pragma once

// ENCABEZADO DE LA LIBRERIA, PUBLICAR Y DEFINIR LAS FUNCIONES SIN ENSEÑAR SU CODIGO PARA USARLAS EN EL CLIENTE
// PARTE DE LA LIBRERIA

namespace ConsoleLibrary
{

	class Snake
	{
	public:
		static int length; // Snake's length
		static std::vector<COORD> body;
		static int position[2]; // Head position
		static COORD positionC; // Coord to use with the vectors, positionC = (position[0], position[1])
		static double speed;
		static double pSpeed;
		static char dir; // Snake's direction --> ['W, 'A', 'S', 'D', 'N'] (N for none, means you lose)
		static bool collided;

		static void spawnSnake(); // Change default position value
		static void move(); // Move one position in the current direction
		static void grow();
		static void speedUp();
		static std::vector<COORD> get_body();
	};

	class Utility
	{
	public:
		static std::string answer;

		static void wait(int milliseconds);
		static void input(Snake& snake);
		static void printC(std::string printed);
		static bool replay();
		static void resetAll(Snake& Snake);
		static void gameTick(Snake Snake);
	};

	class Apple
	{
	public:
		static int position[2];

		static void spawnApple();
		static bool eaten(Snake snake);
	};

	class Mapping
	{
	public:
		static int height, width;
		static std::string map[40][50];
		static void printTitle(); // Prints the title screen.

		static void printEmptyMap(); // Prints the map, fills the empty map[][] array.
		static void printMap(Snake Snake, Apple apple); // Prints the updated map.
	};

}