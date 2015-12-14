#ifndef MONSTER_H
#define MONSTER_H

#include "MonsterData.h"
#include "Player.h"
#include <Graphics/Renderable.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Renderer/OGLRenderer.h>

class Monster 
{
public:
    Monster(MonsterData data, glm::vec2 pos, glm::vec2 direction) : data(data), direction(direction)
    {
	sprite.setScale(data.scale.x, data.scale.y);
	sprite.texture = data.texture;
	
	this->size.x = data.size.x;
	this->size.y = data.size.y;
	this->pos.y = pos.y;
	this->pos.x = pos.x;
	
	float tmp = direction.x;
	
	if(tmp>0)
	{
	    speed.x = tmp;
	    this->direction.x = 1;
	}
	else 
	{
	    speed.x = -tmp;
	    this->direction.x = -1;
	}


	
	sprite.posZ = 5;
	currentHealth = data.health;
	currentStartUpTime = data.attackStartupTime;
	currentRecoveryTime = 0.0f;
	currentFrame = 0;
	animationTimer = 0.0f;
    }
    
    void update(float dt, Player& player) 
    {
	pos.x+= (speed.x*direction.x);
	pos.y += direction.y;
	
	glm::vec4 hitBox = player.getHitBox();
// 	updateAnimation();
	bool isAttacking = false;
	//left
	if(direction.x == 1)
	{
	    if(pos.x + size.x> hitBox.x && pos.x + size.x< hitBox.x + hitBox.z)
	    {
		pos.x = hitBox.x - size.x;
		isAttacking = true;
	    }
	}
	//right
	if(direction.x == -1)
	{
	    if(pos.x < hitBox.x+ hitBox.z && pos.x> hitBox.x)
	    {
		pos.x = hitBox.x + hitBox.z;
		isAttacking = true;
	    }
	}
	
	if(isAttacking)
	{
	    currentAnimation = "ATTACK";
	}
	else 
	{
	    currentAnimation = "WALK";
	    if(animationTimer <= 0.0f)
	    {
		currentFrame++;
		animationTimer = 0.2f;
		if(data.animations["WALK"].size() < currentFrame+1)
		    currentFrame = 0;
	    }
	    else
	    {
		animationTimer-=dt;
	    }
	}
	
	if(isAttacking && currentRecoveryTime<=0.0f)
	{
	    if(currentStartUpTime <= 0.0f)
	    {
		currentFrame = 2;
		attack(player);
		animationTimer = 0.2f;
	    }
	    else
	    {
		currentFrame = 1;
		currentStartUpTime -= dt;
	    }
	}
	else if(isAttacking && animationTimer <= 0.0f)
	{
	    currentRecoveryTime -= dt;
	    currentFrame = 0;
	}
	else if(isAttacking)
	    animationTimer -= dt;
    }
    
    void attack(Player& player) 
    {
	player.addSpirit(-data.spiritDrain);
	currentRecoveryTime = data.attackRecoveryTime;
	currentStartUpTime = data.attackStartupTime;
    }
    //TODO: Behaviour script(knockback, flying/jumping path, teleport, splitting)
    
    void render(cac::RenderEngine<cac::OGLRenderer>* renderer) 
    {
	updateAnimation();
	renderer->render(sprite);
    }
    
    void updateAnimation()
    {
	glm::vec4 rect = data.animations[currentAnimation][currentFrame];
	sprite.posX = pos.x - (rect.z - size.x);
	sprite.scaleX = rect.z * direction.x;

	sprite.scaleY = rect.a;
	sprite.posY = pos.y - sprite.scaleY; 
	
	if(direction.x < 0)
	    sprite.posX += rect.z;
	rect.x /= data.textureSize.x;
	rect.z /= data.textureSize.x;
	rect.y /= data.textureSize.y;
	rect.a /= data.textureSize.y;
	sprite.setTextureRectangle(rect.x, rect.y, rect.z, rect.a);
    }
    
    glm::vec4 getHitBox()
    { 
	return glm::vec4(pos.x, pos.y-size.y, size.x, size.y);
    }
    void damage(int dmg) { currentHealth -= dmg; }
    
    bool isAlive() { return currentHealth>0; }
    int getSpirit() { return data.spiritGain; }
    
    
private:
    MonsterData data;
    cac::Renderable sprite;
    glm::vec2 direction;
    int currentHealth;
    float currentAttackTimer = 0.0f;
    float currentStartUpTime = 0.0f;
    float currentRecoveryTime = 0.0f;
    std::string currentAnimation = "WALK";
    unsigned int currentFrame = 0;
    float animationTimer = 0.0f;
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 speed;
};


#endif