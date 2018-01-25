#include "Camera.h"

using namespace ENGINE;

Camera::Camera()
{
	//Default values
	createRight();
	calculateCameraVectors();

	//Setup Frustrum
	m_frustrum = new Frustrum();
	m_frustrum->windowResized(getFOV(), (float)800 / (float)600, 0.1f, 100.0f);
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
{
	m_pos = pos;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;

	createRight();
	calculateCameraVectors();
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float moveSpeed, float sensitivity, float fov)
{
	m_pos = pos;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	m_movementSpeed = moveSpeed;
	m_mouseSensitivity = sensitivity;
	m_fov = fov;

	createRight();
	calculateCameraVectors();
}

Camera::~Camera()
{
	//Empty
}

void Camera::createProjectionMatrix(int screenWidth, int screenHeight)
{
	m_projection = glm::perspective(getFOV(), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void Camera::createViewMatrix()
{
	m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::vec3 Camera::createRight()
{
	return m_right = glm::cross(m_front, m_up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	float cameraSpeed = m_movementSpeed;// *deltaTime;

	if (direction == FORWARD)
		m_pos += m_front * cameraSpeed;
	if (direction == BACKWARD)
		m_pos -= m_front * cameraSpeed;
	if (direction == LEFT)
		m_pos -= m_right * cameraSpeed;
	if (direction == RIGHT)
		m_pos += m_right * cameraSpeed;

	//Recalculate Frustrum
	m_frustrum->cameraChanged(m_pos, m_right, m_up, -m_front);
}

void Camera::processMouse(InputManager* inputManager_)
{
	if (inputManager_->wasMouseMoved()) {
		//Prevents screen from jumping to your mouses initial local
		if (m_firstMouse) {
			m_lastX = inputManager_->getMouseCoordsX();
			m_lastY = inputManager_->getMouseCoordsY();
			m_firstMouse = false;
		}

		float xoffset = inputManager_->getMouseCoordsX() - m_lastX;
		float yoffset = m_lastY - inputManager_->getMouseCoordsY(); //Reversed since y-coords range from bottom to top
		m_lastX = inputManager_->getMouseCoordsX();
		m_lastY = inputManager_->getMouseCoordsY();

		processMouseMovement(xoffset, yoffset);
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	//Constraints -- So that we lock our view to 90 degrees upwards and downwards -- So that we can't look behind us and invert the camera
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	//Update Front, Right and Up Vectors using the updated Eular angles
	calculateCameraVectors();

	//Recalculate Frustrum
	m_frustrum->cameraChanged(m_pos, m_right, m_up, -m_front);
}

void Camera::calculateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 newfront;
	newfront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	newfront.y = sin(glm::radians(m_pitch));
	newfront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(newfront);

	//Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));  //Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

void Camera::processMouseScroll(float yoffset)
{
	//Constraints so that it does not exceed 45.0
	if (m_fov >= 1.0f && m_fov <= 45.0f)
		m_fov -= yoffset;
	if (m_fov <= 1.0f)
		m_fov = 1.0f;
	if (m_fov >= 45.0f)
		m_fov = 45.0f;
}

float Camera::setYaw(float yaw)
{
	return m_yaw = yaw;
}

float Camera::setPitch(float pitch)
{
	return m_pitch = pitch;
}

float Camera::setMoveSpeed(float moveSpeed)
{
	return m_movementSpeed = moveSpeed;
}

float Camera::setSensitivity(float mouseSensitivity)
{
	return m_mouseSensitivity = mouseSensitivity;
}

float Camera::setFOV(float fov)
{
	return m_fov = fov;
}