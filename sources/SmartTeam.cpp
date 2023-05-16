//
// Created by yarin on 5/6/23.
//

#include "SmartTeam.hpp"

SmartTeam::SmartTeam(Character *leader) : Team(leader){
}


Character* SmartTeam::getClosestNinja(Ninja * n ,Team *enemy) { //function that returns the closest enemy to the ninja
    Character *temp;
    double distance = std::numeric_limits<double>::max();
    for (size_t i = 0; i <  enemy->warriors.size(); ++i) {
        if(warriors.at(i)->isAlive() && n->distance(warriors.at(i)) < distance)
        {
            distance = n->distance(warriors.at(i));
            temp = warriors.at(i);
        }
    }
    return temp;
}

Character *SmartTeam::getLowestCowboy(Team *enemy) { //function that returns the closest enemy to the ninja
    Character *temp;
    int hp = std::numeric_limits<int>::max();
    for (size_t i = 0; i <  enemy->warriors.size(); ++i) {
        if(warriors.at(i)->isAlive() && enemy->warriors.at(i)->hit_pts<hp) {
            hp = enemy->warriors.at(i)->hit_pts;
            temp = warriors.at(i);
        }
    }
    return temp;
}


void SmartTeam::attack(Team *enemy_team) {

    for (size_t i = 0; i < this->warriors.size(); ++i) {
        if (enemy_team->stillAlive() == 0)
            return;
        if(this->warriors.at(i)->type == 2) {
            Ninja *n = static_cast<Ninja *>(this->warriors.at(i));
            if(!n->isAlive())
                continue;
            Character *temp = getClosestNinja(n,enemy_team);
            if (n->distance(temp)>=1)
                n->move(temp);
            else
                n->slash(temp);
        }
        if(this->warriors.at(i)->type == 1) {
            Cowboy *c = static_cast<Cowboy *>(this->warriors.at(i));
            if(!c->isAlive())
                continue;
            if(c->hasboolets()) {
                c->shoot(getLowestCowboy(enemy_team));
            }
            else
                c->reload();
        }
    }
}

