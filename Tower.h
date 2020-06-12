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
#include <Hero.h>

class Tower
{
private:
	glm::mat4 mainTowerPosition;
	glm::vec3 position;
	glm::vec3 size;
	bool haveTarget;
	bool isReloaded;
	int reloadingTime[2];

	//DangerZone
	float bordZLeft;
	float bordZRight;
	float bordXUp;
	float bordXDown;

	glm::vec3 positionBarrel;
	glm::vec3 sizeBarrel;
	float angle;

	void reloading();

public:
	Tower(glm::mat4, glm::vec3);
	//~Tower();

	glm::mat4 getPosition();
	bool isHeroInDangerZone(glm::vec3);
	glm::mat4 getBarrelPosition(glm::vec3);
	bool canTakeShoot();
};

