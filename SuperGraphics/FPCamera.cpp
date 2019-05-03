#include "FPCamera.h"

FPCamera::FPCamera(void)
{
	this->Reset(-5, 1.5, -.5, 
		1, 0.f, -.5, 
		0, 1, 0);

	SetPerspectiveProjection(45.0f, 1200.0f / 750.0f, 0.1f, 100.0f);
    this->bindedHero = nullptr;
    this->prevBindedHero = nullptr;
}

FPCamera::~FPCamera(void)
{
}

glm::vec3 FPCamera::GetLookDirection()
{
	return -mDirection;
}

void FPCamera::setCameraMode(CameraMode mode)
{
    switch (mode)
    {
    case FREE_CAMERA:
        if (this->bindedHero) {
            this->prevBindedHero = this->bindedHero;
            this->bindedHero = nullptr;
        }
        break;
    case SIDE_CAMERA:
        this->Reset(
            0, 0, 5, 
		    0, 0, 0, 
		    0, 1, 0
        );
        this->positionOffset = glm::vec3(2.f, 1.f, 7.f);
        if (this->prevBindedHero) {
            this->bindedHero = this->prevBindedHero;
            this->prevBindedHero = nullptr;
        }
        break;
    case BACK_CAMERA:
        this->Reset(
            -5, 1.5, -.5, 
		     1, 0.f, -.5, 
		     0, 1, 0
        );
        this->positionOffset = glm::vec3(-5.f, 1.5f, -0.5f);
        if (this->prevBindedHero) {
            this->bindedHero = this->prevBindedHero;
            this->prevBindedHero = nullptr;
        }
        break;
    default:
        break;
    }
}

void FPCamera::handleInput(GLFWwindow* window)
{

    float step = 0.05f;
    float angle = 1.f;

    if (!this->bindedHero) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            this->Walk(step);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            this->Walk(-step);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            this->Strafe(step);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            this->Strafe(-step);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            this->Fly(step);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            this->Fly(-step);
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
            this->Pitch(angle);
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            this->Pitch(-angle);
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            this->Yaw(angle);
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            this->Yaw(-angle);
        }

    }

    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        updateCameraHeroControls(this, BACK_CAMERA);
        this->setCameraMode(BACK_CAMERA);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        updateCameraHeroControls(this, SIDE_CAMERA);
        this->setCameraMode(SIDE_CAMERA);
    }
    if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        this->setCameraMode(FREE_CAMERA);
    }

    this->updatePositionToHero();
    this->UpdateViewMatrix();
}

void FPCamera::Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	glm::vec3 eyePt(eyeX, eyeY, eyeZ);
	glm::vec3 centerPt(centerX, centerY, centerZ);
	glm::vec3 upVec(upX, upY, upZ);
	Reset(eyePt, centerPt, upVec);
}

void FPCamera::Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3 &up)
{
	mPosition = eye;
	//still needs normalization
		mDirection = eye - center;
	//i = j x k
		mRight = glm::cross( up,mDirection );
	//j = k x i
		mUp = glm::cross(mDirection, mRight );
	//normalize all
		mUp = glm::normalize(mUp);
		mRight = glm::normalize(mRight);
		mDirection = glm::normalize(mDirection);
	UpdateViewMatrix();
}

glm::mat4 FPCamera::GetViewMatrix()
{
	return mViewMatrix;
}

void FPCamera::UpdateViewMatrix()
{
	glm::vec3 center = mPosition + this->GetLookDirection();
	mViewMatrix = glm::lookAt(mPosition,center,mUp);
}

glm::mat4 FPCamera::GetProjectionMatrix()
{
	return mProjectionMatrix;
}

glm::vec3 FPCamera::getPosition()
{
    return this->mPosition;
}

void FPCamera::bindHero(Hero * hero, glm::vec3 positionOffset)
{
    this->bindedHero = hero;
    this->positionOffset = positionOffset;
}

void FPCamera::updatePositionToHero()
{
    updateCameraPositionToHero(this);
}

void FPCamera::setPosition(glm::vec3 position)
{
    mPosition = position;
}

void FPCamera::SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far)
{
	mProjectionMatrix = glm::perspective(FOV,aspectRatio,near,far);
}

void FPCamera::Slide(float stepR, float stepU, float stepD)
{
	mPosition += stepR *mRight;
	mPosition += stepU * mUp;
	//next transition needs to be tested!!.
	mPosition += stepD * mDirection;
}

void FPCamera::Yaw(float angleDegrees)
{
	// 2ldirection 2lle howa 2l z byt7rk m3a 2l 2tgah.
	
	mDirection	= glm::rotate(mDirection,angleDegrees,mUp);
	mRight		= glm::rotate(mRight,	 angleDegrees,mUp);
}

void FPCamera::Pitch(float angleDegrees)
{
	// 2ldirection 2lle howa 2l z byt7rk m3a 2l 2tgah.
	mUp			= glm::rotate(mUp,		 angleDegrees,mRight);
	mDirection	= glm::rotate(mDirection,angleDegrees,mRight);
}

void FPCamera::Roll(float angleDegrees)
{
	// hna 3shan 7walen 2l Z hnlef 7waleh fa msh hyt7rk.

	// bm3na 2s7, kol vector btlef 7waleh, 2l 2 vectors 2ltanyen btlf 7walehom.
	mRight	= glm::rotate(mRight,angleDegrees,mDirection);
	mUp		= glm::rotate(mUp,	 angleDegrees,mDirection);
}

void FPCamera::Walk(float dist)
{
	 mPosition -= dist * mDirection; // bmshy 3ks 2ldirection 3shan 2l Z n7yty.
}

void FPCamera::Strafe(float dist)
{
	mPosition += dist *mRight;
}

void FPCamera::Fly(float dist)
{
	mPosition += dist * mUp;
}
