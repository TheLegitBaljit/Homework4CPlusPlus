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
    virtual ~Team();
    virtual void add(Character *character);
    virtual void attack(Team *enemy_team);
    virtual int stillAlive();
    virtual void print();
};


#endif //COWBOY_VS_NINJA_A_MAIN_TEAM_H
