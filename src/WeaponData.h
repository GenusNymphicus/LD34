#ifndef WEAPON_DATA_H
#define WEAPON_DATA_H

#include <vector>
#include <glm/glm.hpp>

struct WeaponData 
{
    std::string texture;
    std::string name;
    std::vector<std::vector<glm::vec4>> hurtBoxes; 
    int damage = 10;
    float startUpTime = 0.25f;
    float recoveryTime = 0.1f;
};


#endif