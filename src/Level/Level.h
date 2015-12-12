#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <Graphics/RenderEngine.h>
#include <Graphics/Renderer/OGLRenderer.h>
#include "ELayer.h"
#include <iostream>
#include "MonsterSpawn.h"
#include <../../CyberRush/src/Monster.h>

class Level 
{
public:
    Level()
    {
	ground.resize(4);
	ground[0].setScale(350, 100);
	ground[0].setPosition(0, 500, ELayers::BACKGROUND-1);
	ground[0].setColor(0,1,0);
	
	ground[1].setScale(150, 50);
	ground[1].setPosition(350, 550, ELayers::BACKGROUND-1);
	ground[1].setColor(0,1,0);
	
	ground[2].setScale(12000, 100);
	ground[2].setPosition(500, 500, ELayers::BACKGROUND-1);
	ground[2].setColor(0,1,0);
	
	ground[3].setScale(400, 100);
	ground[3].setPosition(500, 200, ELayers::BACKGROUND-1);
	ground[3].setColor(0,1,0);
	
	background.setScale(800, 600);
	background.setPosition(0, 0, ELayers::BACKGROUND);
	background.setColor(0,0,0.5f);
	
	monsterSpawn.push_back(MonsterSpawn(1000, "Gumba"));
	monsterSpawn.push_back(MonsterSpawn(1500, "Gumba"));
	monsterSpawn.push_back(MonsterSpawn(2000, "Gumba"));
	
	
	character.setScale(64, 64);
	character.setColor(0.75f,0,0);
	reset();
    }

    void reset() 
    {
	character.setPosition(0, 300, ELayers::CHARACTER);
    }
    
    void setRenderer(cac::RenderEngine<cac::OGLRenderer>* renderer) 
    {
	float left = 0, right = 800, top = 0, bottom = 600, near = -0.01f, far = -100;
	camera.setOrthogonalProjection(left, right, bottom, top, near, far);
	renderer->setCamera(camera);
    }
    
    void update(float dt)
    {
	inputTimer -= dt;
	if(inputTimer <= 0.0f)
	{
	    std::cout<<"Input: ";
	    for(auto s : inputBuffer)
		std::cout<<s;
		
	    std::cout<<std::endl;
	    resolveSpell();
	    inputBuffer.clear();
	    
	    inputTimer = inputDuration;
	}
	if(velY < -0.1f)
	    characterSpeed = 100;
	else characterSpeed = 100.0f;
	
	if(character.posX - 200 + 800 < 12000)
	    character.posX += (characterSpeed*dt);
	character.posY += (GRAVITY*gravAccY* dt) + velY * dt;
	camera.setPosition(-character.posX +200, 0);
	
	velY *= 0.95f;
	gravAccY *= 1.02f;

	for(auto& plane : ground)
	{
	    if(plane.posX < character.posX + character.scaleX && plane.posX + plane.scaleX > character.posX )
	    {
		if(character.posY + character.scaleY > plane.posY && character.posY + character.scaleY < plane.posY + plane.scaleY)
		{
		    character.posY = plane.posY - character.scaleY;
		    velY = 0.0f;
		    gravAccY = 1.0f;
		    break;
		}
	    }
	}
    
    for(auto& plane : ground)
    {
	if(plane.posY < character.posY + character.scaleY && plane.posY + plane.scaleY > character.posY + character.scaleY)
	{
	    if(character.posX + character.scaleX > plane.posX && character.posX + character.scaleX < plane.posX + plane.scaleX)
	    {
		character.posX = plane.posX - character.scaleX;
		break;
	    }
	}
    }
    
    if(character.posY + character.scaleY >= 800)
	reset();
    
    
    for(auto& spawn : monsterSpawn)
    {
	if(spawn.spawned == false && character.posX - 200 + camera.getResolution().x)
	{
	    cac::Renderable monster;
	    monster.setScale(32,32);
	    monster.setPosition(spawn.triggerPosX+monster.scaleX, 500-monster.scaleY, ELayers::CHARACTER);
	    spawn.spawned = true;
	    monster.setColor(0.7f, 0.2f, 0.3f);
	    monsters.push_back(monster);
	}
    }
    
    for(auto& monster : monsters)
    {
	monster.posX -= (dt*20.0f);
    }
    }
    void render(cac::RenderEngine<cac::OGLRenderer>* renderer)
    {
	renderer->render(character);
	renderer->render(background);
	
	for(auto& renderable : ground)
	    renderer->render(renderable);
	
	for(auto& renderable : monsters)
	    renderer->render(renderable);
    }
    
    void event(std::string message) 
    {
	if(message == "W")
	{
	    inputBuffer.push_back("W");
	    inputTimer = inputDuration;
	}
	else if(message == "Q")
	{
	    inputBuffer.push_back("Q");
	    inputTimer = inputDuration;
	}
    }
   
    void resolveSpell() 
    {
	unsigned int inputCount = inputBuffer.size();
	
	if(inputCount == 1)
	{
	    if(inputBuffer[0] == "W")
		jump();
	}
    }
    
    void jump()
    {
	if(velY == 0.0f)
	    velY = -700.0f;
    }
    
    bool finished() { return false; }
private:
    cac::Camera camera;
    cac::Renderable background;
    std::vector<cac::Renderable> ground;
    cac::Renderable character;
    std::vector<std::string> inputBuffer;
    
    std::vector<cac::Renderable> monsters;
    std::vector<MonsterSpawn> monsterSpawn;
    
    float inputTimer = 0.0f;
    const float inputDuration = 0.3f;
    float characterSpeed = 50.0f;
    const float GRAVITY = 100.0f;
    float velY =0.0f;
    float gravAccY = 1.0f;
};
#endif