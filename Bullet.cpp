#include "Bullet.h"

Bullet::Bullet(glm::mat4 MBarrel)
{
    this->mainBulletMatrix = MBarrel;
    this->position = glm::vec3(0.3f, 0.0f, 0.0f);
    this->size = glm::vec3(0.2f, 1.0f, 1.0f);
    this->speed = 0.6f;
    this->maxDistance = -30.0f;
    this->dead = false;
}

glm::mat4 Bullet::goForIt()
{
    this->position.x -= speed; //na koncu, aby zaczynala w dobrym miejscu
    glm::mat4 bulletMatrix = glm::translate(this->mainBulletMatrix, this->position);
    bulletMatrix = glm::scale(bulletMatrix, this->size);

    return bulletMatrix;
}

bool Bullet::isDead()
{
    if (this->position.x <= maxDistance) {
        this->dead = true;
    }
    return this->dead;
}
