#ifndef MONSTER_SPAWN_H
#define MONSTER_SPAWN_H


struct MonsterSpawn 
{
    std::string monsterType;
    unsigned int triggerPosX;
    bool spawned = false;
    MonsterSpawn(unsigned int triggerPosX, std::string monsterType) : triggerPosX(triggerPosX), monsterType(monsterType) {}
};

#endif