//
// Created by yarin on 5/4/23.
//

#ifndef COWBOY_VS_NINJA_A_MAIN_COWBOY_H
#define COWBOY_VS_NINJA_A_MAIN_COWBOY_H

#include "Character.hpp"
#include "iostream"


class Cowboy : public Character {
public:
    int bullets;

    Cowboy();
    Cowboy(std::string name,Point place);
    void shoot(Character *enemy);
    bool hasboolets();
    void reload();
    std::string print();
};


#endif //COWBOY_VS_NINJA_A_MAIN_COWBOY_H
