#include "Hero.h"

Hero::Hero(float step)
{
	this->facing = 90;
	this->direction = 0;
	this->stepSize = step;
	this->size = glm::vec3(1.0f, 1.0f, 1.0f);
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Hero::walking()
{
	if (direction == Direction::right) {
		goRight();
	}
	else if (direction == Direction::left) {
		goLeft();
	}
	else if (direction == Direction::downL){
		goDown('L');
	}
	else if (direction == Direction::downR){
		goDown('R');
	}
}

void Hero::goRight()
{
	float z = position.z + stepSize;
	position = getVec3(position.x, position.y, z);
	if (false) //in borders)
	{
		direction = Direction::downR;
		facing = 0;
	}
}

void Hero::goLeft()
{
	float x = position.x + stepSize;
	position = getVec3(x, position.y, position.z);
	if (x) //in borders)
	{
		direction = Direction::downL;
		facing = 0;
	}
}

void Hero::goDown(char side)
{
	float y = position.y + stepSize;
	position = getVec3(position.x, y, position.z);
	if (y) //in borders)
	{
		direction = Direction::right;
		facing = 90;
	}
	if (y) //in borders
	{
		direction = Direction::left;
		facing = 270;
	}
}

glm::vec3 Hero::getVec3(float x, float y, float z)
{
	return glm::vec3(x, y, z);
}

glm::mat4 Hero::calculate(glm::mat4 Mmodel)
{
	walking();

	Mmodel = glm::translate(Mmodel, position);
	Mmodel = glm::rotate(Mmodel, facing * PI/180, glm::vec3(0.0f, 1.0f, 0.0f));
	Mmodel = glm::scale(Mmodel, size);

	return Mmodel;
}
