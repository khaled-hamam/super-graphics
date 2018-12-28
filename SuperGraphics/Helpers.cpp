#include "SuperGraphicsEngine.h"

void updateCameraPositionToHero(FPCamera *camera)
{
    if (camera->bindedHero) {
        glm::vec3 heroPosition = camera->bindedHero->position;
        camera->setPosition(glm::vec3(
            heroPosition.x + camera->positionOffset.x, 
            heroPosition.y + camera->positionOffset.y,
            camera->positionOffset.z
        ));
    }
}


void updateCameraHeroControls(FPCamera *camera, CameraMode mode) {
    if (!camera->bindedHero)
        return;

    if (mode == BACK_CAMERA) {
        camera->bindedHero->setControls(false); 
    } else {
        camera->bindedHero->setControls(true);
    }
}