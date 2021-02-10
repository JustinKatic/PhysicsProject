#include "RigidBody.h"

RigidBody::RigidBody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_mass = a_mass;
	m_rotation = a_rotation;
	m_angularVelocity = 0;
	m_isKinematic = false;
	m_elasticity = 0.8f;
}

void RigidBody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));
	m_position += GetVelocity() * a_timeStep;

	m_rotation += m_angularVelocity * a_timeStep;
}

void RigidBody::ApplyForce(glm::vec2 a_force, glm::vec2 a_pos)
{
	m_velocity += a_force / GetMass();
	m_angularVelocity += (a_force.y * a_pos.x - a_force.x * a_pos.y) / GetMoment();
}



void RigidBody::ResolveCollision(RigidBody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal)
{
	//Find the vector between their centers, or use the provided direction of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(a_collisionNormal ? *a_collisionNormal : a_otherActor->GetPosition() - GetPosition());

	//Get the vector perpendicular  to the collision normal
	glm::vec2 perpendicularColNorm(normal.y, -normal.x);

	//these are applied the the radius from axis to the application of force
	float radius1 = glm::dot(a_contact - m_position, -perpendicularColNorm);
	float radius2 = glm::dot(a_contact - a_otherActor->m_position, perpendicularColNorm);

	//Velocity of the contact point on this object 
	float cp_Velocity1 = glm::dot(m_velocity, normal) - radius1 * m_angularVelocity;
	//velocity of contact point of the other object 
	float cp_velocity2 = glm::dot(a_otherActor->GetVelocity(), normal) + radius2 * a_otherActor->m_angularVelocity;

	if (cp_Velocity1 > cp_velocity2) // they are moving closer
	{
		//this will calculate the effective mass at the contact point of each object (How  much it will move due to the forces applied)
		float mass1 = 1.0f / (1.0f / m_mass + (radius1 * radius1) / GetMoment());
		float mass2 = 1.0f / (1.0f / a_otherActor->m_mass + (radius2 * radius2) / a_otherActor->GetMoment());

		float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.0f;

		glm::vec2 impact = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (cp_Velocity1 - cp_velocity2) * normal;

		ApplyForce(-impact, a_contact - m_position);
		a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
	}
}
