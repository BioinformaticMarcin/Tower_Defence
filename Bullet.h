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

//Musi zyc wlasnym zyciem bo sie zajade
//przy wystrzale obliczam kierunek i długość trasy 
//szybkość bedzie stala

//Gdyby w trakcie wystrzału zmniejszac y to bedzie ladnie opadał hueh na koniec do zrobienia
class Bullet
{
private:
	glm::mat4 mainBulletMatrix; //ta sama co barrel - musi byc zapisana, bo kiedy tower zmieni target 
								//to bullet musi gdzies doleciec
	glm::vec3 position;
	glm::vec3 size;
	float speed;
	float maxDistance;
	bool dead;

public:
	Bullet(glm::mat4);
	//~Bullet();

	glm::mat4 goForIt();
	bool isDead();


};

