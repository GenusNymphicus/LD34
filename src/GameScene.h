#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <Input/InputKeys.h>
#include <Core/IGameScene.h>
#include <Utility/Time.h>
#include "Level.h"
#include "Player.h"
#include "MonsterSpawner.h"
#include "Monster.h"

class GameScene : public cac::IGameScene 
{
public:
    virtual bool initialize() 
    {
	input->getKeyboard()->bind(cac::KEY_A, cac::KeyState::PRESSED, "LEFT");
	input->getKeyboard()->bind(cac::KEY_D, cac::KeyState::PRESSED, "RIGHT");
	
	float left = 0, right = 800, top = 0, bottom = 600, near = -0.01f, far = -100;
	camera.setOrthogonalProjection(left, right, bottom, top, near, far);
	renderer->setCamera(camera);
	
	engine->loadPackage("GAME");
	
	srand(cac::Time::getTimeInMs());
	
	menu.setScale(800,600);
	menu.posZ = 1;
	renderer->clearScreen(0,0,0);
	sound.audioFile = "intro";
	audio->play(sound);
	flash.setScale(800,600);
	flash.posZ = 1;
	showMenu();
	return true;
    }
    
    void reset()
    {
	player.reset();
	spawner.reset();
	flashScreen = false;
	flashTimer = 0.2f;

    }
    
    virtual void event(std::string message)
    {
	if(inputDelay <= 0.0f)
	{
	    if(!started)
		reset();
	    started = true;
	    player.event(message);
	}
    }
    
    
    void showMenu() 
    {
	menu.texture = "menuScreen";
    }
    void showWin() 
    {
	menu.texture = "winScreen";
	if(!playing)
	{
	    audio->stop(sound);
	    sound.audioFile = "win";
	    audio->play(sound);
	    playing = true;
	}
    }
    
    void showDeadEnd()
    {
	inputDelay = 1.0f;
	menu.texture = "loseScreen";
	started = false;
	
	if(!playing)
	{
	    audio->stop(sound);
	    sound.audioFile = "lose";
	    audio->play(sound);
	    playing = true;
	}
    }
    void flashScreenNow()
    {
	flashTimer = 0.1f;
	flashScreen = true;
	flash.setColor(1,1,1);
    }
    virtual void update(float dt) 
    { 
	int i = 0;
	if(!started)
	{
	    inputDelay -= dt;
	    renderer->render(menu);
	    return;
	}
	
	
	int gameOver = player.isGameOver();
	if(gameOver)
	{
	    if(gameOver == 1)
	    {
		showWin();
		renderer->render(menu);
		return;
	    }
	    else if(gameOver == 2)
	    {

		    showDeadEnd();
	
		
		renderer->render(menu);
		return;
	    }
	}
	else 
	{
	    if(player.difficultyIncrease())
	    {
		spawner.increaseDifficulty();

		sound.audioFile = "upgrade";
		audio->play(sound);
		flashScreenNow();
	    }
	    player.update(dt);
	    spawner.update(dt);
	    
	    std::vector<glm::vec4> hurtBoxes = player.getHurtBoxes();
	    
	    level.render(renderer);
	    spawnedMonster = spawner.getSpawnedMonster();
	    for(int i = 0; i<spawnedMonster->size(); i++)
	    {
		glm::vec4 hitBox = spawnedMonster->at(i).getHitBox();
		
		for(auto box : hurtBoxes)
		{
		    bool overlap = !(box.x > hitBox.x + hitBox.z
				||	hitBox.x > box.x + box.z
				||	box.y > hitBox.y + hitBox.a
				|| hitBox.y > box.y + box.a);
		    
		    if(overlap)
		    {
			spawnedMonster->at(i).damage(player.getDamage());
			player.addSpirit(spawnedMonster->at(i).getSpirit());
			sound.audioFile = "hit";
			audio->play(sound);
		    }
		}
		
		spawnedMonster->at(i).update(dt, player);
		spawnedMonster->at(i).render(renderer);
	    }
	
	}
	level.updateSoul(player.getSpirit());
	player.render(renderer);
	
	if(flashScreen)
	{
	    flashTimer -= dt;
	    if(flashTimer<=0.0f)
		flashScreen = false;
	    renderer->render(flash);
	}
    }
    
   
private:
    std::vector<Monster>* spawnedMonster;
    cac::Camera camera;
    Level level;
    Player player;
    MonsterSpawner spawner;
    cac::Renderable menu;
    cac::Sound sound;
    bool playing = false;
    float inputDelay = 0.0f;
    bool started = false;
    bool flashScreen = false;
    float flashTimer = 0.1f;
    cac::Renderable flash;
};

#endif