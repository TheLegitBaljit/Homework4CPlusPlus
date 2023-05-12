//
// Created by yarin on 5/6/23.
//

#ifndef COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H
#define COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H
#include "Team.hpp"
#include "SmartTeam.hpp"
class SmartTeam : public Team{
public:
    SmartTeam();
    SmartTeam(Character *leader);
    ~SmartTeam();
};


#endif //COWBOY_VS_NINJA_A_MAIN_SMARTTEAM_H
