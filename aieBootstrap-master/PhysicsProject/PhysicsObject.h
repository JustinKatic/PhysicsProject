#pragma once
#include <glm/glm.hpp>

//this is a pure abstract class. it will be used as a base for the derived classes that will use FixedUpdate
enum ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX
};

class PhysicsObject
{
public:
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};



protected:
	ShapeType m_shapeID;

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

};

