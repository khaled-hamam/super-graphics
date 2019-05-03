#ifndef FPCamera_h__
#define FPCamera_h__

#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Hero;

enum CameraMode {
    FREE_CAMERA,
    SIDE_CAMERA,
    BACK_CAMERA
};

class FPCamera
{
	glm::vec3 mPosition;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mDirection;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;
    Hero* bindedHero;
    Hero* prevBindedHero;
    glm::vec3 positionOffset;

	glm::vec3 GetLookDirection();

public:
	FPCamera(void);
	~FPCamera(void);

	void UpdateViewMatrix();
	glm::mat4 GetViewMatrix();
	void SetPerspectiveProjection(float FOV, float aspectRatio, float near, float far);
	glm::mat4 GetProjectionMatrix();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    void bindHero(Hero *hero, glm::vec3 positionOffset = glm::vec3(-5.f, 1.5f, -0.5f));
    void updatePositionToHero();
    friend void updateCameraPositionToHero(FPCamera *camera);
    friend void updateCameraHeroControls(FPCamera *camera, CameraMode mode);
    void setCameraMode(CameraMode mode);
    void handleInput(GLFWwindow* window);
	void Reset(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
	void Reset(const glm::vec3 &eye, const glm::vec3 &center, glm::vec3  &up);


#pragma region Rotations
	/// <summary>
	/// Rotates the axes (N, R) about the U-axis with the specified angle. This is equivalent to
	/// a left-turn.
	/// </summary>//y--->z--->x
	void Yaw(float angleDegrees);

	/// <summary>
	/// Rotates the axes (U, N) about the R-axis with the specified angle. This is equivalent
	/// to a look-up (up turn).
	/// </summary>//x--->y--->z
	void Pitch(float angleDegrees);

	/// <summary>
	/// Rotates the axes (R, U) about the N-axis with the specified angle.
	/// </summary>//z--->x--->y
	void Roll(float angleDegrees);
#pragma endregion

#pragma region Translations

	/// <summary>
	/// Moves the eye point a distance dist forward == -dist * N
	/// Walk
	/// </summary>
	void Walk(float dist);

	/// <summary>
	/// Moves the eye point a distance dist to the right == +dist * R
	/// Strafe
	/// </summary>
	void Strafe(float dist);

	/// <summary>
	/// Moves the eye point a distance dist upward == +dist * U
	/// Fly
	/// </summary>
	void Fly(float dist);

#pragma endregion

	/// <summary>
	/// Moves the eye position a distance stepR along the vector R,
	/// a distance stepU along the vector U, and a distance stepD
	/// along the vector N.
	/// </summary>
	void Slide(float stepR, float stepU, float stepD);
};

#endif // FPCamera_h__