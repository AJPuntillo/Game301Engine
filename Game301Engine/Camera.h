#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Frustrum.h"
#include "InputManager.h"

namespace ENGINE {

	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);
		Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float moveSpeed, float sensitivity, float fov); //Overload for added camera settings
		~Camera();

		void createProjectionMatrix(int screenWidth, int screenHeight); //Initialize the Projection Matrix
		void createViewMatrix(); //Return the lookAt matrix (View matrix)
		glm::vec3 createRight(); //Cross product the up and front vector to create the right vector
		void processKeyboard(CameraMovement direction, float deltaTime); //Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM
		void processMouse(InputManager* inputManager_); //If the mouse has been moved, calculate the offset and call ProcessMouseMovement.
		void processMouseMovement(float xoffset, float yoffset); //Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void processMouseScroll(float yoffset); //Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis

		//Getters
		float getYaw() { return m_yaw; }
		float getPitch() { return m_pitch; }
		float getMoveSpeed() { return m_movementSpeed; }
		float getSensitivity() { return m_mouseSensitivity; }
		float getFOV() { return m_fov; }
		glm::vec3 getPos() { return m_pos; }
		glm::vec3 getFront() { return m_front; }
		glm::mat4& getView() { return m_view; }
		glm::mat4& getProj() { return m_projection; }
		Frustrum* getFrustrum() { return m_frustrum; }

		//Setters
		float setYaw(float yaw);
		float setPitch(float pitch);
		float setMoveSpeed(float moveSpeed);
		float setSensitivity(float mouseSensitivity);
		float setFOV(float fov);

	private:
		void calculateCameraVectors(); // Calculates the front vector from the Camera's (updated) Eular Angles

		//Camera Attributes		 //Defaults
		glm::vec3 m_pos			= glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_up			= glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_worldUp		= glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_right		= glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_front		= glm::vec3(0.0f, 0.0f, -1.0f); //Direction vector from look origin (what camera is looking at) to the camera's origin
		//Euler Angles
		float m_yaw				= -90.0f; //Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left
		float m_pitch			= 0.0f;
		//Camera Settings
		float m_movementSpeed	= 0.005f;
		float m_mouseSensitivity = 0.1f;
		float m_fov				= 45.0f;
		//Matrices
		glm::mat4 m_view;
		glm::mat4 m_projection;
		//Camera Movement
		double m_mouseCoordsX	= 0;
		double m_mouseCoordsY	= 0;
		double m_lastX			= 0; //Might need to set this to Window's width / 2 if "snapping" issue occurs
		double m_lastY			= 0; //Might need to set this to Window's height / 2 if "snapping" issue occurs
		bool m_firstMouse		= true;
		//Frustrum
		Frustrum* m_frustrum;
	};

}

#endif