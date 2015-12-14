#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>

struct MonsterData 
{
    std::string texture;
    glm::vec2 scale;
    int health;
    int spiritGain;
    int spiritDrain;
    float attackRecoveryTime = 1.0f;
    float attackStartupTime = 0.3f;
    std::map<std::string, std::vector<glm::vec4>> animations;
    glm::vec2 textureSize;
    glm::vec2 size;
    
    MonsterData(std::string texture, glm::vec2 scale, unsigned int health, int spiritGain, int spiritDrain) : texture(texture), scale(scale), health(health), spiritGain(spiritGain), spiritDrain(spiritDrain)
    {
    }
    
};


#endif