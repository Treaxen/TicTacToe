#ifndef APPLICATION_H
#define APPLICATION_H
#endif // !1

#include <iostream>
#include "GameObject.h"
#include <time.h>
#include "Random.h"
#include "ParticleSystemh.h"


const int RESOLUTION_X = 640;
const int RESOLUTION_Y = 480;
const int GAMEOBJECT_COUNT = 11;

class Application
{
private:

	//For fps counter
	float prevTime;
	float initTime;
	int frameCount;
	float deltaTime, curTime;

	//Sprites
	Sprite* m_SpriteArray[9];

	//Gameobject array
	GameObject* m_gameobjectArray[GAMEOBJECT_COUNT];

	//Input management
	bool isLeftMouseDown;
	bool isRightMouseDown;

	//Tic tac toe
	GameObject* m_tttButtonArray[9];
	int m_isOccupiedArray[9];
	bool m_isHostTurn;
	bool m_isHost;

	enum GAMECONDITION
	{
		WAITING = 0,
		PLAYING,
		P1WIN,
		P2WIN,
		DRAW,
	};

	GAMECONDITION m_gameCondition;

public:
	Application();

	static Application& GetInstance()
	{
		static Application instance;
		return instance;
	}

	virtual void SendMyData(unsigned char data);
	virtual void OnReceivedData(unsigned char data);

	virtual ~Application();
	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual void OnKeyPress(int key);
	virtual void OnKeyRelease(int key);
	virtual void OnKeyHold(int key);
	virtual void OnMousePress(int key, double xPos, double yPos);
	virtual void OnMouseRelease(int key, double xPos, double yPos);
	virtual void OnMouseHold(int key);

	//Tic tac toe functions
	void OnButtonInteract(unsigned char index, bool isHost);
	void OnServerJoin(int playerCount);
	void ResetButtons(void);
	void UpdateBoard(void);
	int CheckWinCondition(void);

};

#pragma once
