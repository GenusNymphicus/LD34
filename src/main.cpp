#include <Core/GameEngine.h>
#include "GameScene.h"

int main()
{
    cac::GameEngine engine;
    engine.run(new GameScene, cac::WindowDesc("LD34", 800, 600));
}