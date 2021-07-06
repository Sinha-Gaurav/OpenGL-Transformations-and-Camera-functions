#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

/// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	YAW_CLKW,
	YAW_CCLKW
};

extern const float YAW;
extern const float PITCH;
extern const float ROLL;
extern const float SPEED;
extern const float SENSITIVITY;
extern const float ZOOM;


/**
* An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL.
*/
class Camera
{
public:
	glm::vec3 Position;///< postion of the camera.
	glm::vec3 Front;///< front vector.
	glm::vec3 Up;///< up vector.
	glm::vec3 Right;///< right vector.
	glm::vec3 WorldUp;///< world up vector.

	float Yaw;///< yaw value
	float Pitch;///< pitch value
	float Roll;///< roll value

	float MovementSpeed;///< speed used to compute the movement of the camera per frame.
	float MouseSensitivity;///< mouse sensitivity value.
	float Zoom;///< zoom value of the camera.

	/**
	* Constructor.
	* Constructs a camera object.
	* @param[in] position initial position of the camera.
	* @param[in] up the world up vector.
	* @param[in] yaw initial yaw value.
	* @param[in] pitch initial pitch value.
	* @param[in] roll initial roll value.
	*/
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL);

	/**
	* Function used to calculate the view matrix using Euler Angles and the LookAt Matrix.
`	* @return a mat4 view matrix
	*/
	glm::mat4 GetViewMatrix();

	/**
	* Function to processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems).
	* @param[in] direction direction of camera movement.
	* @param[in] deltaTime change in time between each render loop.
	* @return void
	*/ 
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	/**
	* Function to processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	* @param[in] xoffset change in cursor x-position.
	* @param[in] yoffset change in cursor y-position.
	* @param[in] constrainPitch a boolean to handle pitch locking.
	* @return void
	*/
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	/**
	* Function to processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis.
	* @param[in] yoffset change in cursor y-position.
	* @return void
	*/
	void ProcessMouseScroll(float yoffset);

private:
	/** 
	* Function to calculate the front vector from the Camera's (updated) Euler Angles.
	*/
	void updateCameraVectors();
};
#endif
