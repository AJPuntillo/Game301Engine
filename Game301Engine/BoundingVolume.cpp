#include "BoundingVolume.h"

using namespace ENGINE;

BoundingVolume::BoundingVolume() :
	m_minCorner(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_maxCorner(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

BoundingVolume::BoundingVolume(glm::vec3 &minCorner_, glm::vec3 &maxCorner_)
{
	m_minCorner = minCorner_;
	m_maxCorner = maxCorner_;
}

BoundingVolume::~BoundingVolume()
{
}

void BoundingVolume::setupVolume(Model &model_) {

	std::vector<float> vertexList = model_.getMesh()->getVertices();
	bool firstSet = true;

	int componentListSize = model_.getMesh()->vertexDescriptor->getSize();
	for (int i = 0; i < componentListSize; i++)
	{
		VertexComponentDescriptor vertexDesc = model_.getMesh()->vertexDescriptor->componentList[i];
		if (vertexDesc.type == VertexComponentDescriptor::VC_POSITION_3F)
		{
			int offset = vertexDesc.offset;
			int inc = model_.getMesh()->vertexDescriptor->getStride();

			//We don't want the whole list, we only want each row of vertices (every position value) -- Therefore divide by the stride value to get the number of vertices in the list
			int numOfVerts = vertexList.size() / inc;

			for (int j = 0; j < numOfVerts; j++)
			{
				if (firstSet) {
					m_maxCorner[0] = vertexList[offset];
					m_maxCorner[1] = vertexList[offset + 1];
					m_maxCorner[2] = vertexList[offset + 2];
					m_minCorner[0] = vertexList[offset];
					m_minCorner[1] = vertexList[offset + 1];
					m_minCorner[2] = vertexList[offset + 2];
					firstSet = false;
				}
				else {
					if (vertexList[offset] > m_maxCorner[0]) m_maxCorner[0] = vertexList[offset];
					if (vertexList[offset + 1] > m_maxCorner[1]) m_maxCorner[1] = vertexList[offset + 1];
					if (vertexList[offset + 2] > m_maxCorner[2]) m_maxCorner[2] = vertexList[offset + 2];

					if (vertexList[offset] < m_minCorner[0]) m_minCorner[0] = vertexList[offset];
					if (vertexList[offset + 1] < m_minCorner[1]) m_minCorner[1] = vertexList[offset + 1];
					if (vertexList[offset + 2] < m_minCorner[2]) m_minCorner[2] = vertexList[offset + 2];
				}
				offset += inc;
			}
		}
	}
}

bool BoundingVolume::isColliding(const BoundingVolume &bv) const
{
	if (((glm::vec3)m_minCorner)[0] > ((BoundingVolume&)bv).m_maxCorner[0]) return false;
	if (((glm::vec3)m_minCorner)[1] > ((BoundingVolume&)bv).m_maxCorner[1]) return false;
	if (((glm::vec3)m_minCorner)[2] > ((BoundingVolume&)bv).m_maxCorner[2]) return false;

	if (((glm::vec3)m_maxCorner)[0] < ((BoundingVolume&)bv).m_minCorner[0]) return false;
	if (((glm::vec3)m_maxCorner)[1] < ((BoundingVolume&)bv).m_minCorner[1]) return false;
	if (((glm::vec3)m_maxCorner)[2] < ((BoundingVolume&)bv).m_minCorner[2]) return false;

	return true;
}

void BoundingVolume::movedBy(glm::vec3 &amount_)
{
	//BoundingVolume* result(this);
	//result->m_minCorner = result->m_minCorner + amount_;
	//result->m_maxCorner = result->m_maxCorner + amount_;
	//return result;
	m_minCorner += amount_;
	m_maxCorner += amount_;
}

glm::vec3 BoundingVolume::getPositiveVertex(glm::vec3 &norm)
{
	glm::vec3 result(m_minCorner);

	if (norm[0] > 0) result[0] = m_maxCorner[0];
	if (norm[1] > 0) result[1] = m_maxCorner[1];
	if (norm[2] > 0) result[2] = m_maxCorner[2];

	return result;
}

glm::vec3 BoundingVolume::getNegativeVertex(glm::vec3 &norm)
{
	glm::vec3 result(m_minCorner);

	if (norm[0] < 0) result[0] = m_minCorner[0];
	if (norm[1] < 0) result[1] = m_minCorner[1];
	if (norm[2] < 0) result[2] = m_minCorner[2];

	return result;
}