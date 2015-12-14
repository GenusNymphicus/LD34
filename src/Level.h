#ifndef LEVEL_H
#define LEVEL_H
#include <Graphics/RenderEngine.h>
#include <Graphics/Renderer/OGLRenderer.h>
#include <Graphics/Renderable.h>

class Level 
{
public:
    Level() 
    {
	background.setPosition(0, -50, 10);
	background.setScale(800,600);
	background.texture = "Background";	
	
	soulMeter.setPosition(24,400,8);
	soulMeter.setScale(150,200);
	soulMeter.texture = "SoulMeter";

	soulFill.texture = "SoulFill";
    }
    
    void updateSoul(float soul)
    {	
	float scaledSoul = soulMeter.scaleY * soul;
	this->soulValue = soul;
	
	soulFill.setPosition(soulMeter.posX, soulMeter.posY + soulMeter.scaleY - scaledSoul + 3, 9);
	soulFill.setScale(150, scaledSoul);
    }
    
    void render(cac::RenderEngine<cac::OGLRenderer>* renderer) 
    {
	renderer->render(background);
	if(soulValue > 0)
	    renderer->render(soulFill);
	renderer->render(soulMeter);
    }
    
private:
    cac::Renderable background;
    cac::Renderable soulMeter;
    cac::Renderable soulFill;
   float soulValue = 0;
};
#endif