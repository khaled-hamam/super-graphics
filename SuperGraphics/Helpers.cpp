#include "SuperGraphicsEngine.h"

void updateCameraPositionToHero(FPCamera *camera)
{
    if (camera->bindedHero) {
        glm::vec3 heroPosition = camera->bindedHero->position;
        camera->setPosition(glm::vec3(
            heroPosition.x + camera->positionOffset.x, 
            heroPosition.y + camera->positionOffset.y,
            heroPosition.z + camera->positionOffset.z
        ));
    }
}