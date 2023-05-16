#include "Character.hpp"

Character::Character() {
}
Character::Character(const Point &place, int hp, std::string name) {
    this->place = place;
    this->name = name;
    this->hit_pts = hp;
    this->inTeam = false;
    this->type = 0;
}
std::string Character::getName() {
    return this->name;
}
Point Character::getLocation() {
    return this->place;
}

bool Character::isAlive() {
    return (this->hit_pts > 0);
}
void Character::hit(int num) {
    if(num<0)
        throw std::invalid_argument("negative");
    this->hit_pts-=num;
}
double Character::distance(Character *other)
{
    return this->place.distance(other->getLocation());
}
int Character::getHitPoints() {
    return this->hit_pts;
}
std::string Character::print() {
    return "";
}