#pragma once
#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


namespace ENGINE {

	class GameObject; //Forward declare

	class SceneNode
	{
	public:
		typedef std::vector<ENGINE::GameObject*>::iterator model_iterator;
		SceneNode();
		SceneNode(const glm::vec3 &loc, const glm::vec4 &orient, const glm::vec3 &scaling);
		SceneNode(const SceneNode &other);

		~SceneNode();

		//Add a new child onto the end of the list of children for this node.
		void appendChild(SceneNode* node);

		//This removes the indicated child from the list of children of this node.
		//It does not recursively remove the children of the node being removed.
		//It does not delete the object being removed or any of its children.
		//If the indicated node is not a child of this node, no action is performed.
		void removeChild(SceneNode* node);

		//Add a new model to this scene node.  This does not check to see if the modelis already attached to the scene node, so multiple attachments are possible.
		void addModel(GameObject* model);

		//Remove a model to this scene node.  If the model is not attached to this node, no action is performed.  If attached multiple times, this will only detach one copy.
		void removeModel(GameObject* model);

		//Each scene node has a pointer to its first child and its next sibling. These form
		//chains which can be traversed to visit all the children of a node.  This method
		//retuns a pointer to the first child or NULL if there is no child.
		SceneNode* getFirstChild() const;

		//This method retuns a pointer to the next sibling or NULL if there is no sibling.
		SceneNode* getNextSibling() const;

		//This returns an STL iterator through the list of models attached to this scene node. This iterator references the first model in the list.
		model_iterator modelBegin();

		//This returns an STL past-the-end iterator for the list of models attached to this scene node.
		model_iterator modelEnd();

		//Getters

		int getNumberModels() const;
		//Return the current location of the scene node relative to its parent.
		glm::vec3 getLocation() const;
		//Return the location of this object in world space.  This means that it looks at the positions of all the parent nodes and adds them together to determine the position of this node in world space.
		glm::vec3 getWorldLocation() const;
		glm::vec4 getOrientation() const;
		void getRotateAbout(glm::vec3 &pt, glm::vec4 &rotation);
		glm::vec3 getScaleFactor() const;
		//This returns the pointer to the user data or NULL if no user data was set.
		void* getUserData() { return m_userData; }

		//Setters

		//Set the location of the scene node as an offset of the parent.
		void setLocation(const glm::vec3 &loc) { m_location = loc; }
		//Set the orientation of this node relative to its parent.
		void setOrientation(const glm::vec4 &orient) { m_orientation = orient; }
		//This will rotate the scene node about an arbitrary point in space.
		void setRotateAbout(const glm::vec3 &pt, const glm::vec4 &rotation) {
			m_rotateAboutPt = pt;
			m_rotateAboutOrientation = rotation;
		}
		//This will return the point and rotation used to rotate the object about an arbitrary point in space.
		void setScaleFactor(const glm::vec3 &scaling) { m_scale = scaling; }
		//User data is the universal extension mechanism where a user of the scene graph
		//can store any information they want in a scene node.  Internally, the user data
		//is stored as a void* pointer to the user data.  The user data is initialized to
		//NULL and will remain NULL unless the user changes it to point to another object.
		//If it has a non-null value, it will be deleted by the destructor for the scene node.
		void setUserData(void* userData_) { m_userData = userData_; }

		glm::mat4 getModelMatrix() { return m_modelMatrix; }
		glm::mat4 m_modelMatrix = glm::mat4();

	private:
		glm::vec3 m_location;
		glm::vec3 m_scale;
		glm::vec4 m_orientation;
		glm::vec3 m_rotateAboutPt;
		glm::vec4 m_rotateAboutOrientation;
		SceneNode* m_firstChild;
		SceneNode* m_lastChild;
		SceneNode* m_prevSibling;
		SceneNode* m_nextSibling;
		SceneNode* m_parent;
		std::vector<GameObject*> m_modelList;
		void* m_userData;
	};

}

#endif