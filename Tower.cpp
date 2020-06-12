#include "Tower.h"

Tower::Tower(glm::mat4 Mmodel, glm::vec3 newPos) 
{
	this->position = newPos;
	this->mainTowerPosition = glm::translate(Mmodel, position);
	this->size = glm::vec3(1.0f, 1.0f, 1.0f); //yyy xd nigdzie tego nie uzylem 
	this->haveTarget = false;
	this->isReloaded = true;
	this->reloadingTime [1] = 100;

	this->bordZLeft = position.z + 7;
	this->bordZRight = position.z - 7;
	this->bordXUp = position.x - 7;
	this->bordXDown = position.x + 7;

	this->positionBarrel = glm::vec3(-1.5f, 1.5f, 0.0f);
	this->sizeBarrel = glm::vec3(1.5f, 0.2f, 0.2f);
	this->angle = 10;
}
glm::mat4 Tower::getPosition() 
{
	//Tu trzeba wstawic translatowanie w momencie ustawiania na mapie 
	//albo lepiej inna metodke "ustawianie", bo po ustawieniu nie ma sensu 
	// liczyc miliard razy przekstalcanie jak ona w miejscu stoi
	return this->mainTowerPosition;
}
glm::mat4 Tower::getBarrelPosition(glm::vec3 posHero)
{
	if (haveTarget){
		//z = arctg(a) = arctg((Yp - Yk) / (Xp - Xk))
		angle = atan2((posHero.x - position.x), (posHero.z - position.z));
		this->angle += 1.5;
	}
	else {
		this->angle -= 0.0006;
	}
	reloading();

	glm::mat4 mainBarrelPosition = glm::rotate(this->mainTowerPosition, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	mainBarrelPosition = glm::translate(mainBarrelPosition, this->positionBarrel);
	mainBarrelPosition = glm::scale(mainBarrelPosition, this->sizeBarrel);
	return mainBarrelPosition;
}

void Tower::reloading() 
{
	if (!isReloaded) {
		this->reloadingTime[0] -= 1;
		if (reloadingTime[0] <= 0) {
			this->isReloaded = true;
		}
	}
}
bool Tower::canTakeShoot()
{
	if (isReloaded) {
		this->reloadingTime[0] = reloadingTime[1];
		this->isReloaded = false;
		return true;
	}
	return false;
}
bool Tower::isHeroInDangerZone(glm::vec3 posHero) {

	if (posHero.z < bordZLeft 
		&& posHero.z > bordZRight
		&& posHero.x > bordXUp
		&& posHero.x < bordXDown)
	{
		this->haveTarget = true;
		return true;
	}
	this->haveTarget = false;
	return false;
}
