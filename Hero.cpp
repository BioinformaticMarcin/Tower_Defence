#include "Hero.h"

Hero::Hero(float step)
{
	this->facing = 90;
	this->direction = 0;
	this->stepSize = step;
	this->size = glm::vec3(0.5f, 1.0f, 0.5f);
	this->position = glm::vec3(7.0f, 1.0f, -5.0f);
	this->level = 0;
	this->maxLevel = 4;
	this->borders = 12.5f;//(64.0 - 14.0) / 4; //wysStolu - brzegi / liczba poziomow
	this->lastBorder = 7.0f;
	this->dead = false;
}

void Hero::walking()
{
	if (direction == Direction::right) {
		goRight();
	}
	else if (direction == Direction::left) {
		goLeft();
	}
	else if (direction == Direction::downL) {
		goDown();
	}
	else if (direction == Direction::downR) {
		goDown();
	}
}

void Hero::goRight()
{
	float z = position.z - stepSize;
	position = getVec3(position.x, position.y, z);
	if (position.z < -55.0f) //in borders)64
	{
		if (maxLevel == level)
		{
			fprintf(stdout, "PRZEJEBALES GOSCIU\n");
			this->dead = true;
			this->endGame = true;
		}
		this->direction = Direction::downR;
		facing = 180;
	}
}

void Hero::goLeft()
{
	float z = position.z + stepSize;
	position = getVec3(position.x, position.y, z);
	if (position.z > -5.0f) //in borders)
	{
		this->direction = Direction::downL;
		facing = 0;
	}
}

bool Hero::checkIfNextLevel(float x) {
	float currentBorder = lastBorder + borders;
	if (x > (currentBorder - 0.1f) /*&& x < (lastBorder + 0.1f)*/) {
		this->level += 1;
		this->lastBorder = currentBorder;
		return true;
	}
	return false;
}

void Hero::goDown()
{
	float x = position.x + stepSize;
	position = getVec3(x, position.y, position.z);

	if (checkIfNextLevel(x))
	{
		if (direction == Direction::downL) //in borders)
		{
			this->direction = Direction::right;
			facing = 90;
		}
		if (direction == Direction::downR) //in borders
		{
			this->direction = Direction::left;
			facing = 270;
		}
	}
}

glm::vec3 Hero::getVec3(float x, float y, float z)
{
	return glm::vec3(x, y, z);
}

glm::mat4 Hero::getPosition(glm::mat4 Mmodel)
{
	walking();

	Mmodel = glm::translate(Mmodel, position);
	Mmodel = glm::rotate(Mmodel, facing * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));
	Mmodel = glm::scale(Mmodel, size);

	return Mmodel;
}

glm::vec3 Hero::getVec3Position()
{
	return this->position;
}

bool Hero::isEndGame() {
	return endGame;
}

bool Hero::isDead() {
	return dead;
}
