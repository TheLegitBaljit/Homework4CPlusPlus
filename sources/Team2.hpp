//
// Created by yarin on 5/6/23.
//

#ifndef COWBOY_VS_NINJA_A_MAIN_TEAM2_H
#define COWBOY_VS_NINJA_A_MAIN_TEAM2_H
#include "Team.hpp"
#include "Team2.hpp"

class Team2 : public Team {
public:
    Team2();
    Team2(Character *leader);
//    ~Team2();
    void print() override;
    Character* getClosest(Team *enemy) override;
    void attack(Team *enemy_team) override;
};


#endif //COWBOY_VS_NINJA_A_MAIN_TEAM2_H
