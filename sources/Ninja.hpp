#ifndef COWBOY_VS_NINJA_A_MAIN_NINJA_H
#define COWBOY_VS_NINJA_A_MAIN_NINJA_H

#include "Character.hpp"
#include "iostream"

class Ninja : public Character{
public:
    int speed;

    Ninja(std::string name,int hit_pts,Point place,int speed);
    virtual void move(Character *enemy);
    virtual void slash(Character *enemy);

};


#endif //COWBOY_VS_NINJA_A_MAIN_NINJA_H
