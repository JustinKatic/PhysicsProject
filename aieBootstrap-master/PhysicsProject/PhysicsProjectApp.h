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

	//glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

protected:
	glm::vec2 worldPos;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	float extraForce = 20;
	float ballCollectedXPos = 130;

	PhysicsScene* m_physicsScene;

	//const float m_aspectRatio = 16.0f / 9.0f;
	//const float m_extents = 100;

	aie::Texture* m_tableTexture;

	void ChooseWhiteBallLocation(aie::Input* a_input);
	void ShootWhiteBall(aie::Input* a_input);
	bool IsWhiteBallFirstShot;
	bool HasBallsStopped;

	void AddBallsToBallList(Sphere* a_ball);
	std::vector<Sphere*> m_ListOfBalls;

	void AddPocketsToPocketList(Sphere* a_pocket);
	std::vector<Sphere*> m_ListOfPockets;

	bool IsBallVelocity0();

	void Createballs();

	void CreatePockets();


	void CreateBoxBoarders();


	aie::Texture* m_testTexture;


	aie::Texture* m_whiteBallTexture;


	aie::Texture* m_ball1Texture;
	aie::Texture* m_ball2Texture;
	aie::Texture* m_ball3Texture;
	aie::Texture* m_ball4Texture;
	aie::Texture* m_ball5Texture;
	aie::Texture* m_ball6Texture;
	aie::Texture* m_ball7Texture;
	aie::Texture* m_ball8Texture;
	aie::Texture* m_ball9Texture;
	aie::Texture* m_ball10Texture;
	aie::Texture* m_ball11Texture;
	aie::Texture* m_ball12Texture;
	aie::Texture* m_ball13Texture;
	aie::Texture* m_ball14Texture;
	aie::Texture* m_ball15Texture;


	Sphere* whiteBall;
	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;
	Sphere* ball5;
	Sphere* ball6;
	Sphere* ball7;
	Sphere* ball8;
	Sphere* ball9;
	Sphere* ball10;
	Sphere* ball11;
	Sphere* ball12;
	Sphere* ball13;
	Sphere* ball14;
	Sphere* ball15;

	Box* box1;
	Box* box2;
	Box* box3;
	Box* box4;
	Box* box5;
	Box* box6;

	Sphere* pocket1;
	Sphere* pocket2;
	Sphere* pocket3;
	Sphere* pocket4;
	Sphere* pocket5;
	Sphere* pocket6;



public:
	void DrawRect();
	void SphereAndPlane();
	void SpringTest(int a_amount);
	void TriggerTest();

};