#ifndef COWBOY_VS_NINJA_A_MAIN_NINJA_H
#define COWBOY_VS_NINJA_A_MAIN_NINJA_H

#include "Character.hpp"
#include "iostream"

class Ninja : public Character{
public:
    int speed;

    Ninja();
    Ninja(std::string name,Point place,int hit_pts,int speed);
    void move(Character *enemy);
    void slash(Character *enemy);
    std::string print();
};


#endif //COWBOY_VS_NINJA_A_MAIN_NINJA_H
