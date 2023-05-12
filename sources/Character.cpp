#include "Character.hpp"

Character::Character() {
    this->place = Point();
    this->hit_pts = 100;
    this->name = "DEFAULT";
}
Character::Character(Point place, int hp, std::string name) {
    this->place = place;
    this->name = name;
    this->hit_pts = hp;
}
std::string Character::getName() {
    return this->name;
}
Point Character::getLocation() {
    return this->place;
}

bool Character::isAlive() {
    return true;
}
void Character::hit(int num) {
    this->hit_pts-=num;
}
double Character::distance(Character *other)
{
    return 0.0;
}
int Character::getHitPoints() {
    return this->hit_pts;
}
std::string Character::print() {
    return "";
}