#pragma once
#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stack>

namespace ENGINE {

	class MatrixStack
	{
	public:
		MatrixStack();
		~MatrixStack();

		void orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		void perspective(float fovy, float aspect, float nearZ, float farZ);
		void lookAt(const glm::vec3& posn, const glm::vec3& at, const glm::vec3& up);
		void lookAt(float camX, float camY, float camZ, float atX, float atY, float atZ, float upX, float upY, float upZ);
		
		const glm::mat4 getProjectionMatrix() const;
		const glm::mat4 getModelMatrix() const;
		const float* getProjectionMatrixValue() const;
		const float* getModelMatrixValue() const;
		void getProjectionMatrixValue(float *values) const;
		void getModelMatrixValue(float *values) const;

		void pushModelView();
		void popModelView();
		void pushProjection();
		void popProjection();

		void rotateBy(const glm::quat &quat);
		void rotateBy(float angle, float vx, float vy, float vz);
		void scaleBy(float xFactor, float yFactor, float zFactor);
		void translateBy(float xAmt, float yAmt, float zAmt);

		void setProjectionToIdentity();
		void setModelViewToIdentity();

		bool isModelViewDirty() const;
		bool isProjectionDirty() const;

		void clearModelViewDirty();
		void clearProjectionDirty();

	private:
		std::stack<glm::mat4> m_modelStack;
		std::stack<glm::mat4> m_projectionStack;
		bool m_modelStackDirty = true;
		bool m_projectionStackDirty = true;
	};

}

#endif