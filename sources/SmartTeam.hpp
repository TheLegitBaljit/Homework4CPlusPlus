//
// Created by yarin on 5/6/23.
//

#ifndef COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H
#define COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H

#include "Team.hpp"
#include "SmartTeam.hpp"

class SmartTeam : public Team {
public:
    SmartTeam(Character *leader);

    Character *getLowestCowboy(Team *enemy); //function that returns the closest enemy to the ninja
    Character *getClosestNinja(Ninja* n, Team *enemy);
    void attack(Team *enemy_team) override;

};


#endif //COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H
