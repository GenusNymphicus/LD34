#ifndef PLAYER_H
#define PLAYER_H
#include <Graphics/Renderable.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Renderer/OGLRenderer.h>
#include "WeaponData.h"
#include "WeaponFactory.h"
#include <iostream>
class Player 
{
public:
    Player()
    {
	sprite.texture = "Hero";
	sprite.setScale(64,64);
	size = glm::vec2(64,100);
	pos = glm::vec2(400-32, 400);
	sprite.setPosition(400 - 32, 600 - 200 -64, 3);
	equip(currentWeaponStage);
	
	animations["FIST"].push_back(glm::vec4(10, 4, 60, 102));
	animations["FIST"].push_back(glm::vec4(112, 15, 40, 85));
	animations["FIST"].push_back(glm::vec4(186, 28, 105, 86));
	animations["FIST"].push_back(glm::vec4(186, 28, 105, 86));
	
	animations["KATAR"].push_back(glm::vec4(16, 135, 57, 93));
	animations["KATAR"].push_back(glm::vec4(115, 140, 50, 80));
	animations["KATAR"].push_back(glm::vec4(190, 140, 50, 80));
	animations["KATAR"].push_back(glm::vec4(115, 140, 50, 80));
	animations["KATAR"].push_back(glm::vec4(16, 135, 57, 93));
	animations["KATAR"].push_back(glm::vec4(290, 143, 95, 78));
	animations["KATAR"].push_back(glm::vec4(290, 143, 95, 78));
	
	animations["SWORD"].push_back(glm::vec4(16, 278, 72, 80));
	animations["SWORD"].push_back(glm::vec4(110, 248, 72, 102));
	animations["SWORD"].push_back(glm::vec4(214, 263, 98, 83));
	animations["SWORD"].push_back(glm::vec4(335, 248, 65, 100));
	animations["SWORD"].push_back(glm::vec4(110, 248, 72, 102));
	animations["SWORD"].push_back(glm::vec4(214, 263, 98, 83));
	animations["SWORD"].push_back(glm::vec4(335, 248, 65, 100));
	animations["SWORD"].push_back(glm::vec4(446, 223, 52, 120));
	animations["SWORD"].push_back(glm::vec4(543, 263, 160, 76));
	animations["SWORD"].push_back(glm::vec4(543, 263, 160, 76));
	
	
	animations["GIANT"].push_back(glm::vec4(52, 422, 127, 237));
	animations["GIANT"].push_back(glm::vec4(247, 378, 161, 282));
	animations["GIANT"].push_back(glm::vec4(427, 352, 150, 308));
	animations["GIANT"].push_back(glm::vec4(602, 364, 76, 356));
	animations["GIANT"].push_back(glm::vec4(760, 366, 89, 293));
	animations["GIANT"].push_back(glm::vec4(830, 802, 286, 167));
	animations["GIANT"].push_back(glm::vec4(830, 802, 286, 167));

	spiritTreshHolds.resize(4);
	//start fist
	spiritTreshHolds[0] = 0;
	//katar
	spiritTreshHolds[1] = 3;
	spiritTreshHolds[2] = 6;
	spiritTreshHolds[3] = 12;
	
	
	attackDir = glm::vec2(1,0);
    }
    
    void reset()
    {
	sprite.texture = "Hero";
	sprite.setScale(64,64);
	size = glm::vec2(64,100);
	pos = glm::vec2(400-32, 400);
	sprite.setPosition(400 - 32, 600 - 200 -64, 3);
	attackDir = glm::vec2(1,0);
	
	increaseDifficulty = false;
	currentWeaponStage = 0;
	currentAttackFrame = 0;
	attacking = false;
	attackTimer = 0.0f;
	spirit = 0;
	weaponUp = false;
	maxWeaponLevel = 0;
	currentRecoveryTimer = 0.0f;
	currentStartUpTimer = 0.0f;
	nextWeaponStage = 0;
	gameOver = 0;
	equip(currentWeaponStage);
    }
    void event(std::string message)
    {
	if(attacking == false && currentRecoveryTimer <= 0.0f) 
	{
	    if(message == "LEFT")
	    {
		attackDir = glm::vec2(-1,0);
		attack();
	    }
	    else if(message == "RIGHT")
	    {
		attackDir = glm::vec2(1, 0);
		attack();
	    }
	}

    }
    
    void attack() 
    {
	attacking = true;
	currentAttackFrame = 1;
	attackTimer = 0.0f;
	currentStartUpTimer = currentWeapon.startUpTime;
	updateHurtBoxes();

    }
    int getDamage() { return currentWeapon.damage; }
    
    int isGameOver() { return gameOver; }
    
    void updateHurtBoxes() 
    {
	currentHurtBoxes.clear();
	if(attacking)
	{
	    if(currentAttackFrame >= hurtBoxes.size())
		return;
	    
	    for(auto box : hurtBoxes[currentAttackFrame])
	    {
		if(attackDir.x < 0.0f)
		{
		    float deltaX =  -sprite.scaleX - box.scaleX +  2*(sprite.posX -(box.posX-sprite.scaleX));
		    box.posX += deltaX;
		}
		currentHurtBoxes.push_back(glm::vec4(box.posX, box.posY, box.scaleX, box.scaleY));
	    }
	}
    }
    void updateAnimation()
    {
	glm::vec4 rect = animations[currentWeapon.name][currentAttackFrame];
	

	if(attackDir.x < 0)
	    sprite.posX = pos.x - (rect.z - size.x);
	else 
	    sprite.posX = pos.x;
	
	if(attackDir.x > 0)
	    sprite.scaleX = -rect.z;
	else
	    sprite.scaleX = rect.z;

	sprite.scaleY = rect.a;
	sprite.posY = pos.y - sprite.scaleY; 
	sprite.posZ = 2;
	
	if(attackDir.x > 0)
	    sprite.posX += rect.z;
	
	rect.x /= 1024.0f;
	rect.z /= 1024.0f;
	rect.y /= 1024.0f;
	rect.a /= 1024.0f;
	sprite.setTextureRectangle(rect.x, rect.y, rect.z, rect.a);
    }
    
    void update(float dt)
    {
	if(attacking && currentStartUpTimer <= 0.0f)
	{
	    attackTimer += dt;
	    if(attackTimer >= ANIMATION_SPEED)
	    {
		currentAttackFrame++;
		if(currentAttackFrame >= currentWeapon.hurtBoxes.size()-1)
		{
		    attacking = false; 
		    currentRecoveryTimer = currentWeapon.recoveryTime;
		     if(currentWeaponStage >= spiritTreshHolds.size()-1)
		    {
			gameOver = 1;
		    }
		}
		attackTimer = 0;
		updateHurtBoxes();
	    }
	}
	if(currentRecoveryTimer <= 0.0f && !attacking)
	{
	    currentAttackFrame = 0;
	   
	}
	else 
	{
	    currentStartUpTimer -= dt;
	    currentRecoveryTimer -= dt;
	    
	    	    
	    if(!attacking && weaponUp)
	    {
		equip(nextWeaponStage);
		weaponUp = false;
	    }
	}
	

    }
    
    void equip(unsigned int weaponStage) 
    {
	if(weaponFactory.stageAvailable(weaponStage))
	{
	    this->currentWeaponStage = weaponStage;
	    if(weaponStage > maxWeaponLevel)
	    {
		maxWeaponLevel = weaponStage;
		increaseDifficulty = true;
	    }

	   currentWeapon = weaponFactory.getWeapon(weaponStage);
	   currentAttackFrame = 0;
	   
	   hurtBoxes.clear();
	   for(auto boxes : currentWeapon.hurtBoxes)
	   {
	       hurtBoxes.push_back(std::vector<cac::Renderable>());
		for(auto box : boxes)
		{
		    hurtBoxes.back().push_back(cac::Renderable());
		    hurtBoxes.back().back().setColor(1, 1, 0);
		    hurtBoxes.back().back().setPosition(pos.x + size.x + box.x, box.y + pos.y, 2);
		    hurtBoxes.back().back().setScale(box.z, box.a);
		}
	    }
	}
    }
    void render(cac::RenderEngine<cac::OGLRenderer>* renderer) 
    {
	updateAnimation();
	renderer->render(sprite);
	if(SHOW_HURTBOXES && attacking && currentStartUpTimer <= 0.0f)
	{
	    for(int i =0; i<hurtBoxes[currentAttackFrame].size(); i++)
	    {
		cac::Renderable box = hurtBoxes[currentAttackFrame][i];
		box.posX = currentHurtBoxes[i].x;
		if(attackDir.x < 0)
		    box.posX -= 16;
		renderer->render(box);
	    }
	}
    }
    
    glm::vec4 getHitBox() { return glm::vec4(pos.x, pos.y-size.y, size.x, size.y); }
    std::vector<glm::vec4> getHurtBoxes() { return  (currentStartUpTimer <= 0.0f? currentHurtBoxes : std::vector<glm::vec4>()); }
    void addSpirit(int spirit) 
    { 
	this->spirit += spirit; 
	if(currentWeaponStage+1 < spiritTreshHolds.size() && this->spirit >= spiritTreshHolds[currentWeaponStage+1])
	{
	    weaponUp = true;
	 
	    nextWeaponStage = currentWeaponStage+1;
	    
	    this->spirit = 0;
	    increaseDifficulty = true;
	    
	}
	if(spirit  < 0)
	{
	    gameOver = 2;
	    /*
	    int restSpirit = this->spirit;
	    int index = 0;
	    while(currentWeaponStage-index>0 && restSpirit < 0) 
	    {
		this->spirit = spiritTreshHolds[currentWeaponStage-index] + (restSpirit);
		restSpirit = this->spirit + restSpirit;
		index++;
	    };
	    if(currentWeaponStage-index <= 0 && restSpirit<0)
		std::cout<<"GAME OVER"<<std::endl;
	    else 
	    { 
		nextWeaponStage = currentWeaponStage-index;
	    
		weaponUp = true;
	    }*/
	}
    }
    
    float getSpirit()
    {
	if(currentWeaponStage+1 < spiritTreshHolds.size())
	    return (float)spirit/spiritTreshHolds[currentWeaponStage+1];
	    
	else 
	    return (float)spirit/100;
    }
    bool difficultyIncrease() 
    {
	if(increaseDifficulty)
	{
	    increaseDifficulty = false;
	    return true;
	}
	return false;
    }
private:
    const bool SHOW_HURTBOXES = false;
    cac::Renderable sprite;
    std::vector<glm::vec4> currentHurtBoxes;
    std::vector<std::vector<cac::Renderable>> hurtBoxes;
    WeaponData currentWeapon;
    WeaponFactory weaponFactory;
    glm::vec2 attackDir;
    const float ANIMATION_SPEED = 0.2f;
    bool increaseDifficulty = false;
    int currentWeaponStage = 0;
    unsigned int currentAttackFrame = 0;
    bool attacking = false;
    float attackTimer = 0.0f;
    int spirit = 0;
    bool weaponUp = false;
    int maxWeaponLevel = 0;
    float currentRecoveryTimer = 0.0f;
    float currentStartUpTimer = 0.0f;
    int nextWeaponStage = 0;
    int gameOver = 0;
    glm::vec2 size;
    glm::vec2 pos;
    std::map<std::string, std::vector<glm::vec4>> animations;
    std::vector<int> spiritTreshHolds;
};
#endif