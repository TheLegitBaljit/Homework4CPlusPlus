#include "Character.hpp"
#include <iostream>
#include <cmath>
#include "Cowboy.hpp"

using namespace std;

Cowboy::Cowboy()
{

}

Cowboy::Cowboy(std::string name, Point location) : Character(location, 110, name) , bullets(6) {this->type = 1;}


void Cowboy::shoot(Character *enemy)
{
    if(this->bullets == 0)
        return;
    if(this->getHitPoints() <= 0)
        throw std::runtime_error("cannot attack while dead");
    if(enemy == this)
        throw std::runtime_error("You cannot shoot yourself");
    if(enemy->isAlive() == false)
        throw std::runtime_error("You cannot shoot a dead target");
    enemy->hit(10);
    this->bullets -= 1;
}
bool Cowboy::hasboolets()
{
    return (this->bullets > 0);
}
void Cowboy::reload()
{
    if(this->getHitPoints() <= 0)
        throw std::runtime_error("dead cowboy cannot reload");
    this->bullets = 6;
}

std::string Cowboy::print()
{
    string res = "";
    res += "C (" + this->getName() + ")";
    if(this->isAlive() == true)
        res += to_string(this->getHitPoints());
    res += " (" + to_string(this->getLocation().getX()) + "," + to_string(this->getLocation().getY()) + ")";
    return res;
}