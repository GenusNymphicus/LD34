#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include "Level.h"
#include "ELayer.h"

class LevelManager
{
public:
    LevelManager()
    {

    }
    
    void loadLevels() 
    {
	//World 1
	levels.push_back(std::vector<Level>());
	
	//Stage 1
	Level level;
	levels.back().push_back(level);

    }
    Level* getLevel(unsigned int world, unsigned int stage) { return &levels[world][stage]; }
    
private:
    std::vector<std::vector<Level>> levels;
};


#endif