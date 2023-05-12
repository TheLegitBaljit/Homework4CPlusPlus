#include "Cowboy.hpp"

Cowboy::Cowboy() : Character(Point(0,0),110,"default"), bullets(6) {}
Cowboy::Cowboy(std::string name,Point place) : Character(place,110,name) , bullets(6) {}

void Cowboy::shoot(Character *enemy) {

}

bool Cowboy::hasboolets() {
    return bullets > 0;
}

void Cowboy::reload() {
    this->bullets+=6;
}
