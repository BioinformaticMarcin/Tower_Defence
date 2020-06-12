#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include "constants.h"
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "iostream"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <objloader.hpp>
#include <vboindexer.hpp>
#include <array>
#include "gltext.h"


class Hero
{
private:
	//glm::mat4 MGame;
	//glm::vec3 position;
	glm::vec3 size;
	glm::vec3 position;
	int direction;
	float facing; //"angle" * vec3(0, 1, 0) ustawiane przy kazdym kroku
	float stepSize;
	int level;
	int maxLevel;
	float borders; //wysStolu - brzegi / liczba poziomow
	float lastBorder;
	bool dead;
	bool endGame;

	enum Direction {
		right,
		left,
		downL,
		downR
	};

	void walking();	//MGame, facing(enum), stepSize
	void goRight(); //set position and facing
	void goLeft();
	void goDown();
	bool checkIfNextLevel(float);

	glm::vec3 getVec3(float, float, float);

public:
	Hero(float);
	//~Hero();
	glm::mat4 getPosition(glm::mat4); //MGame * translat(position) * rotate(facing) rotate na koniec aby nie psuc sobie macierzy przesuniecia
	glm::vec3 getVec3Position();
	bool isEndGame();
	bool isDead();

};

