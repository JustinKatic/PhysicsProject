#pragma once
#include <glm/glm.hpp>
#include <vector>


class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	// This will call the update of each physicsObj and updates internally.
	//This will handle collision detection and resolution
	void Update(float dt);

	void DebugScene();


	//called once per frame and handles the rendering of physicsObj
	//This will add to loop of gizmo objects to render
	void Draw();

	void SetGravity(const glm::vec2 a_gravity) { m_gravity = a_gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float GetTimeStep() const { return m_timeStep; }


protected:

	glm::vec2 m_gravity;
	float m_timeStep;

	std::vector<PhysicsObject*> m_actors;


};
