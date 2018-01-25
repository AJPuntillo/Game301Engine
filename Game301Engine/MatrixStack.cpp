#include "MatrixStack.h"

using namespace ENGINE;

MatrixStack::MatrixStack()
{
	glm::mat4 identityMatrix(1.0f), identityMatrix2(1.0);
	m_projectionStack.push(identityMatrix);
	m_modelStack.push(identityMatrix2);
}

MatrixStack::~MatrixStack()
{
}

void MatrixStack::orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	m_projectionStack.top() = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);
	m_projectionStackDirty = true;
}


void MatrixStack::perspective(float fovy, float aspect, float nearZ, float farZ)
{
	m_projectionStack.top() = glm::perspective(fovy, aspect, nearZ, farZ);
	m_projectionStackDirty = true;
}


const glm::mat4 MatrixStack::getProjectionMatrix() const
{
	if (m_projectionStack.empty())
	{
		throw std::string("MatrixStack: retrieval of empty projection stack");
	}
	return m_projectionStack.top();
}


const glm::mat4 MatrixStack::getModelMatrix() const
{
	if (m_modelStack.empty())
	{
		throw std::string("MatrixStack: retrieval of empty model-view stack");
	}
	return m_modelStack.top();
}

const float* MatrixStack::getProjectionMatrixValue() const
{
	return glm::value_ptr(getProjectionMatrix());
}

const float* MatrixStack::getModelMatrixValue() const
{
	return glm::value_ptr(getModelMatrix());
}

void MatrixStack::getProjectionMatrixValue(float *values) const
{
	const float *vals = getProjectionMatrixValue();
	for (int i = 0; i < 16; i++) values[i] = vals[i];
}


void MatrixStack::getModelMatrixValue(float *values) const
{
	const float *vals = getModelMatrixValue();
	for (int i = 0; i < 16; i++) values[i] = vals[i];
}

void MatrixStack::setProjectionToIdentity()
{
	m_projectionStack.top() = glm::mat4(1.0);
	m_projectionStackDirty = true;
}


void MatrixStack::setModelViewToIdentity()
{
	m_modelStack.top() = glm::mat4(1.0);
	m_modelStackDirty = true;
}


void MatrixStack::pushModelView()
{
	m_modelStack.push(m_modelStack.top());
}


void MatrixStack::popModelView()
{
	if (m_modelStack.empty())
	{
		std::string("MatrixStack: Pop of empty stack");
	}
	m_modelStack.pop();
	m_modelStackDirty = true;
}

void MatrixStack::pushProjection()
{
	m_projectionStack.push(m_projectionStack.top());
}


void MatrixStack::popProjection()
{
	if (m_projectionStack.empty())
	{
		throw std::string("MatrixStack: Pop of empty stack");
	}
	m_projectionStack.pop();
	m_projectionStackDirty = true;
}


void MatrixStack::rotateBy(const glm::quat& q)
{
	float angle = glm::angle(q);
	glm::vec3 vect = glm::axis(q);

	m_modelStack.top() = m_modelStack.top() * glm::rotate(angle, vect);
	m_modelStackDirty = true;
}

void MatrixStack::rotateBy(float angle, float vx, float vy, float vz)
{
	m_modelStack.top() = m_modelStack.top() * glm::rotate(glm::radians(angle), glm::vec3(vx, vy, vz));
	m_modelStackDirty = true;
}


void MatrixStack::scaleBy(float xFactor, float yFactor, float zFactor)
{
	m_modelStack.top() = m_modelStack.top() * glm::scale(glm::vec3(xFactor, yFactor, zFactor));
	m_modelStackDirty = true;
}


void MatrixStack::translateBy(float xAmt, float yAmt, float zAmt)
{
	m_modelStack.top() = m_modelStack.top() * glm::translate(glm::vec3(xAmt, yAmt, zAmt));
	m_modelStackDirty = true;
}

void MatrixStack::lookAt(const glm::vec3& posn, const glm::vec3& at, const glm::vec3& up)
{
	m_modelStack.top() = glm::lookAt(posn, at, up);
	m_modelStackDirty = true;
}

void MatrixStack::lookAt(float camX, float camY, float camZ, float atX, float atY, float atZ, float upX, float upY, float upZ)
{
	lookAt(glm::vec3(camX, camY, camZ), glm::vec3(atX, atY, atZ), glm::vec3(upX, upY, upZ));
	m_modelStackDirty = true;
}

bool MatrixStack::isModelViewDirty() const
{
	return m_modelStackDirty;
}


bool MatrixStack::isProjectionDirty() const
{
	return m_projectionStackDirty;
}


void MatrixStack::clearModelViewDirty()
{
	m_modelStackDirty = false;
}


void MatrixStack::clearProjectionDirty()
{
	m_projectionStackDirty = false;
}