#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <Input/InputKeys.h>
#include <Core/IGameScene.h>
#include "Level/LevelManager.h"

//initial scene with title screen/world select

class GameScene : public cac::IGameScene 
{
public:
    virtual bool initialize() 
    {
	
	
	levelManager.loadLevels();
	currentLevel = levelManager.getLevel(0,0);
	currentLevel->setRenderer(renderer);
	
	input->getKeyboard()->bind(cac::KEY_Q, cac::KeyState::PRESSED, "Q");
	input->getKeyboard()->bind(cac::KEY_W, cac::KeyState::PRESSED, "W");
	return true;
    }
    
    virtual void event(std::string message)
    {
	currentLevel->event(message);
    }
    
    virtual void update(float dt) 
    { 
	currentLevel->update(dt);
	currentLevel->render(renderer);
    }
    
private:
    Level* currentLevel;
    LevelManager levelManager;
};

#endif