#ifndef COWBOY_VS_NINJA_A_MAIN_TEAM_H
#define COWBOY_VS_NINJA_A_MAIN_TEAM_H
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "Point.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "vector"
#include "ios"
class Team
{
public:
    std::vector<Character*> warriors;
    Character *leader;

    Team();
    Team(Character *leader);
    virtual ~Team () {
        for (size_t i = 0; i < warriors.size(); i++) { delete warriors.at(i); }
    }    void add(Character *character);
    virtual void attack(Team *enemy_team);
    int stillAlive();
    virtual void print();
    virtual Character* getClosest(Team *enemy_team);
};


#endif //COWBOY_VS_NINJA_A_MAIN_TEAM_H
