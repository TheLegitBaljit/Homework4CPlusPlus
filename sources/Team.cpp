
#include "Team.hpp"
Team::Team() {
    this->leader = new Character();
}

Team::Team(Character *leader) {
    this->leader = leader;
}
Team::~Team() {
    for (size_t i = 0; i < this->warriors.size(); ++i) {
        delete this->warriors[i];
    }
}
void Team::add(Character *character) {

}
void Team::attack(Team *enemy_team) {

}
int Team::stillAlive() {
    return 0;
}
void Team::print() {

}
