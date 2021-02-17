#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Input.h"

#include "PhysicsScene.h"
#include "Sphere.h"
#include"Box.h"
#include <vector>


class PhysicsProjectApp : public aie::Application
{
public:

	PhysicsProjectApp();
	virtual ~PhysicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	glm::vec2 worldPos;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	float extraForce = 20;
	float ballCollectedXPos = 130;

	PhysicsScene* m_physicsScene;



	void ChooseWhiteBallLocation(aie::Input* a_input);
	void ShootWhiteBall(aie::Input* a_input);
	bool IsWhiteBallFirstShot;
	bool HasBallsStopped;

	void AddBallsToBallList(Sphere* a_ball);
	std::vector<Sphere*> m_ListOfBalls;

	void AddPocketsToPocketList(Sphere* a_pocket);
	std::vector<Sphere*> m_ListOfPockets;

	void AddTexturesToList(aie::Texture* a_texture);
	std::vector<aie::Texture*> m_ListOfTextures;

	void AddBoxBoardersToList(Box* a_box);
	std::vector<Box*> m_listOfBoxes;

	bool IsBallVelocity0();

	void Createballs();

	void CreatePockets();

	void CreateBoxBoarders();

	void CreateTextures();

	void DrawBallTextures();

	aie::Texture* m_tableTexture;

public:
	void DrawRect();
	//void SphereAndPlane();
	//void SpringTest(int a_amount);
	//void TriggerTest();

};