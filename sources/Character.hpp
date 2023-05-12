#ifndef COWBOY_VS_NINJA_A_MAIN_CHARACTER_H
#define COWBOY_VS_NINJA_A_MAIN_CHARACTER_H

#include "Point.hpp"
#include "iostream"

class Character {
public:
    Point place;
    int hit_pts;
    std::string name;

    //Constructors
    Character();
    Character(Point place, int hit_pts, std::string name);

    virtual bool isAlive();
    virtual double distance(Character *other);
    virtual void hit(int num);
    virtual int getHitPoints();
    virtual std::string getName();
    virtual Point getLocation();
    virtual std::string print();
};


#endif //COWBOY_VS_NINJA_A_MAIN_CHARACTER_H
