#include "PhysicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"


PhysicsProjectApp::PhysicsProjectApp() {

}

PhysicsProjectApp::~PhysicsProjectApp() {

}

bool PhysicsProjectApp::startup()
{
	//increases the 2D line count to maximise the number of objects we an draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, 0));


	//lower the value, the more accurate the simulation will be
	// but it will increase the processing time required.
	//If it is to high it causes the sim to stutter and reduce stability
	m_physicsScene->SetTimeStep(0.01f);

	DrawPoolGame();
	//DrawRect();
	//SphereAndPlane();

	return true;
}

void PhysicsProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsProjectApp::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRation = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRation, 100 / aspectRation, -1.0f, 1.0f));


	// draw your stuff here!

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}



void PhysicsProjectApp::DrawRect()
{
	m_physicsScene->AddActor(new Sphere(glm::vec2(20, 10), glm::vec2(-10, -17), 1, 3, glm::vec4(1, 0, 0, 1)));
	m_physicsScene->AddActor(new Plane(glm::vec2(-0.65, 0.75), -25));

	Box* box1 = new Box(glm::vec2(-20, 0), glm::vec2(16, -4), 1, 4, 8, 4, glm::vec4(1, 0, 0, 1));
	box1->SetRotation(0.5f);
	m_physicsScene->AddActor(box1);

	Box* box2 = new Box(glm::vec2(10, 0), glm::vec2(-4, 0), 1, 4, 8, 4, glm::vec4(0, 1, 0, 1));
	box2->SetRotation(0.5f);
	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);

	box1->ApplyForce(glm::vec2(30, 0), glm::vec2(0));
	box2->ApplyForce(glm::vec2(-15, 0), glm::vec2(0));

	Sphere* ball = new Sphere(glm::vec2(5, -10), glm::vec2(0), 1, 3, glm::vec4(0, 0, 1, 1));
	ball->SetRotation(0.5f);
	m_physicsScene->AddActor(ball);
	ball->SetKimematic(true);
}

void PhysicsProjectApp::SphereAndPlane()
{
	Sphere* ball1;
	ball1 = new Sphere(glm::vec2(-30, 10), glm::vec2(0), 3.0f, 4, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball1);

	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(30, 10), glm::vec2(0), 3.0f, 4, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball2);


	ball1->ApplyForce(glm::vec2(30, 0), glm::vec2(0));
	ball2->ApplyForce(glm::vec2(-30, 0), glm::vec2(0));

	Plane* plane = new Plane();
	m_physicsScene->AddActor(plane);
}

void PhysicsProjectApp::DrawPoolGame()
{
	Sphere* WhiteBall;
	WhiteBall = new Sphere(glm::vec2(-60, 0), glm::vec2(0, 0), 3.0f, 2, glm::vec4(1, 1, 1, 1));
	m_physicsScene->AddActor(WhiteBall);

	WhiteBall->ApplyForce(glm::vec2(400, 0), glm::vec2(0));

	//frontRow
	Sphere* ball1;
	ball1 = new Sphere(glm::vec2(40, 0), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball1);

	//secondRow
	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(45, 2.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball2);
	Sphere* ball3;
	ball3 = new Sphere(glm::vec2(45, -2.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball3);

	//thirdRow
	Sphere* ball4;
	ball4 = new Sphere(glm::vec2(50, 5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball4);
	Sphere* ball5;
	ball5 = new Sphere(glm::vec2(50, -5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball5);
	Sphere* ball6;
	ball6 = new Sphere(glm::vec2(50, 0), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball6);

	//fourthRow
	Sphere* ball7;
	ball7 = new Sphere(glm::vec2(55, 7.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball7);
	Sphere* ball8;
	ball8 = new Sphere(glm::vec2(55, -7.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball8);
	Sphere* ball9;
	ball9 = new Sphere(glm::vec2(55, 2.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball9);
	Sphere* ball10;
	ball10 = new Sphere(glm::vec2(55, -2.5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball10);



	//fifthRow
	Sphere* ball11;
	ball11 = new Sphere(glm::vec2(60, 10), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball11);
	Sphere* ball12;
	ball12 = new Sphere(glm::vec2(60, -10), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball12);
	Sphere* ball13;
	ball13 = new Sphere(glm::vec2(60, 5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball13);
	Sphere* ball14;
	ball14 = new Sphere(glm::vec2(60, 0), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball14);
	Sphere* ball15;
	ball15 = new Sphere(glm::vec2(60, -5), glm::vec2(0, 0), 3.0f, 2, glm::vec4(0, 1, 1, 1));
	m_physicsScene->AddActor(ball15);

	//Bottom pool table border
	Box* box1 = new Box(glm::vec2(45, -45), glm::vec2(0, 0), 0, 4, 40, 3, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box1);
	Box* box2 = new Box(glm::vec2(-45, -45), glm::vec2(0, 0), 0, 4, 40, 3, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box2);

	//Top pool table border
	Box* box3 = new Box(glm::vec2(45, 45), glm::vec2(0, 0), 0, 4, 40, 3, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box3);
	Box* box4 = new Box(glm::vec2(-45, 45), glm::vec2(0, 0), 0, 4, 40, 3, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box4);

	//Left pool table border
	Box* box5 = new Box(glm::vec2(-95, 0), glm::vec2(0, 0), 0, 4, 3, 40, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box5);

	//Right pool table border
	Box* box6 = new Box(glm::vec2(95, 0), glm::vec2(0, 0), 0, 4, 3, 40, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(box6);

	//BottomMidHole
	Sphere* pocket1;
	pocket1 = new Sphere(glm::vec2(0, -47), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket1);

	//BottomRightHole
	Sphere* pocket5;
	pocket5 = new Sphere(glm::vec2(90, -45), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket5);

	//BottomLeftHole
	Sphere* pocket6;
	pocket6 = new Sphere(glm::vec2(-90, -45), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket6);

	//TopMidHole
	Sphere* pocket2;
	pocket2 = new Sphere(glm::vec2(0, 47), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket2);

	//TopLeftHole
	Sphere* pocket3;
	pocket3 = new Sphere(glm::vec2(-90, 45), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket3);

	//TopRightHole
	Sphere* pocket4;
	pocket4 = new Sphere(glm::vec2(90, 45), glm::vec2(0, 0), 3.0f, 4.5, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(pocket4);

}
