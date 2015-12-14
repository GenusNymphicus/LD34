#ifndef WEAPON_FACTORY
#define WEAPON_FACTORY

#include <glm/glm.hpp>
#include "WeaponData.h"

class WeaponFactory 
{
public:
    enum WeaponType 
    {
	FIST = 0,
	KATAR = 1,
	SWORD = 2,
	GIANT_SWORD = 3
    };
    
    WeaponFactory()
    {
	//stage 0 weapon "Fist"
	weaponData.resize(4);
	weaponData[WeaponType::FIST].texture = "fist";
	weaponData[WeaponType::FIST].startUpTime = 0.5f;
	weaponData[WeaponType::FIST].recoveryTime = 0.1f;
	//hurtboxes = (xOffset player, yOffset player, width, height)
	weaponData[WeaponType::FIST].hurtBoxes.resize(4);
	weaponData[WeaponType::FIST].hurtBoxes[2].push_back(glm::vec4(32, -64, 16, 16));
	weaponData[WeaponType::FIST].name = "FIST";


	weaponData[WeaponType::KATAR].texture = "Katar";
	//hurtboxes = (xOffset player, yOffset player, width, height)
	weaponData[WeaponType::KATAR].hurtBoxes.resize(7);
	weaponData[WeaponType::KATAR].hurtBoxes[5].push_back(glm::vec4(0, -64, 32, 16));
	weaponData[WeaponType::KATAR].startUpTime = 0.1f;
	weaponData[WeaponType::KATAR].recoveryTime = 0.25f;
	weaponData[WeaponType::KATAR].name = "KATAR";
	
	weaponData[WeaponType::SWORD].texture = "Sword";
	weaponData[WeaponType::SWORD].hurtBoxes.resize(10);
	weaponData[WeaponType::SWORD].hurtBoxes[8].push_back(glm::vec4(32, -64, 48, 16));
	weaponData[WeaponType::SWORD].startUpTime = 0.2f;
	weaponData[WeaponType::SWORD].recoveryTime = 0.25f;
	weaponData[WeaponType::SWORD].name = "SWORD";
	
	weaponData[WeaponType::GIANT_SWORD].texture = "Giant";
	weaponData[WeaponType::GIANT_SWORD].hurtBoxes.resize(7);
	weaponData[WeaponType::GIANT_SWORD].startUpTime = 0.2f;
	weaponData[WeaponType::GIANT_SWORD].recoveryTime = 0.25f;
	weaponData[WeaponType::GIANT_SWORD].name = "GIANT";
    }
    
    WeaponData getWeapon(unsigned int stage) { return weaponData[stage]; } 
    bool stageAvailable(unsigned int weaponStage) { return weaponData.size() > weaponStage; } 
private:
    std::vector<WeaponData> weaponData;
};


#endif