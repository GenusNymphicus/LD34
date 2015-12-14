#ifndef MONSTER_SPAWNER_H
#define MONSTER_SPAWNER_H
#include "Monster.h"
#include "MonsterData.h"

class MonsterSpawner 
{
public:
    MonsterSpawner() 
    {
	monsterData.push_back(MonsterData("Bob", glm::vec2(64,64), 1, 1, 1));
	monsterData.back().animations["WALK"].push_back(glm::vec4(7, 1, 62, 114));
	monsterData.back().animations["WALK"].push_back(glm::vec4(80, 1, 69, 108));
	monsterData.back().animations["ATTACK"].push_back(glm::vec4(1, 160, 90, 71));
	monsterData.back().animations["ATTACK"].push_back(glm::vec4(1, 259, 84, 71));
	monsterData.back().animations["ATTACK"].push_back(glm::vec4(156, 160, 98, 71));
	monsterData.back().textureSize = glm::vec2(256.0f, 360.0f);
	monsterData.back().size = glm::vec2(80,100);
    }
    
    void reset()
    {
	difficulty = 0;
	spawnedMonster.clear();
    }
    void increaseDifficulty() 
    { 
	difficulty++;
	spawnedMonster.clear();
	spawnTimer =  1+((rand()%500)/100);
    }
    void decreaseDifficulty() { difficulty--; }
    
    void update(float dt) 
    {
	for(int i = spawnedMonster.size()-1; i>=0; i--)
	{
	    if(!spawnedMonster[i].isAlive())
	    {
		spawnedMonster.erase(spawnedMonster.begin() + i);
	    }
	}
	
	if(spawnTimer < 0.0f)
	{
	    spawnMonster();
	    
 	    spawnTimer =  1+((rand()%500)/100);
	}
	else spawnTimer -= dt;
    }
    
    
    void spawnMonster()
    {
	MonsterData data = monsterData.back();
	int spawnPoint = rand()%2;
	glm::vec2 pos;
	glm::vec2 dir;

	//left
	if(spawnPoint == 1)
	{
	    dir = glm::vec2(1,0);
	    pos.x = -data.scale.x;
	}
	else 
	{
	    dir = glm::vec2(-1,0);
	    pos.x = 800;
	}
	pos.y = 600-200;
		if(difficulty == 1)
	{
	    if(spawnedMonster.size() == 0)
		dir.x *= (1 + (300)/100.0f);
	    else 
		dir.x *= (1 + (50)/100.0f);
	}
	if(difficulty == 2)
	{
	    if(spawnedMonster.size() == 0)
 		dir.x *= (1 + ((rand()%100)/100.0f));
	    else 
 		dir.x *= (1 + ((rand()%50)/100.0f));
	}
	spawnedMonster.push_back(Monster(monsterData.back(), pos, dir));
    }
    
    std::vector<Monster>* getSpawnedMonster() { return &spawnedMonster; }
    
private:
    std::vector<Monster> spawnedMonster;
    unsigned int difficulty = 0;
    float spawnTimer = 3.0f;
    
    std::vector<MonsterData> monsterData;
};



#endif