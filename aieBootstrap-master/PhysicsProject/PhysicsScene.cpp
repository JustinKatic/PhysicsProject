#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <list>
#include "RigidBody.h"
#include <iostream>


PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end())
		m_actors.erase(it);
}

void PhysicsScene::Update(float dt)
{
	static std::list<PhysicsObject*> dirty; //MUST REMOVE
	static float accumlatedTime = 0.0f;
	accumlatedTime += dt;

	while (accumlatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumlatedTime -= m_timeStep;

		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
					continue;
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
				if (pRigid->CheckCollision(pOther) == true)
				{
					pRigid->ApplyForceToOther(dynamic_cast<RigidBody*>(pOther), pRigid->GetVelocity() * pRigid->GetMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
	}
}

void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << "  :  ";
		pActor->Debug();
		count++;
	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->MakeGizmo();
	}
}
