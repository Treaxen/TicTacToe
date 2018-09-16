#include "Application.h"
#include "MyPhoton.h"

Application::Application()
{
	//FPS counter
	prevTime = glfwGetTime();
	initTime = glfwGetTime();
	frameCount = 0;

	//Sprite
	m_SpriteArray[0] = new Sprite("../media/OppTurn.png");
	m_SpriteArray[1] = new Sprite("../media/YourTurn.png");
	m_SpriteArray[2] = new Sprite("../media/Waiting.png");
	m_SpriteArray[3] = new Sprite("../media/tile.png");
	m_SpriteArray[4] = new Sprite("../media/YouWin.png");
	m_SpriteArray[5] = new Sprite("../media/OppWin.png");
	m_SpriteArray[6] = new Sprite("../media/DrawGame.png");
	m_SpriteArray[7] = new Sprite("../media/Forfeit.png");
	m_SpriteArray[8] = new Sprite("../media/Reset.png");

}

Application::~Application()
{
}

void Application::Start()
{
	std::cout << "Application is Started" << std::endl;

	Random::SetSeed(18374579302);


	//Init Photon
	MyPhoton::getInstance().connect();

	int count = 0;
	//=============Init Buttons=======================
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_gameobjectArray[count] = new GameObject(m_SpriteArray[3]);
			m_tttButtonArray[count] = m_gameobjectArray[count];
			m_tttButtonArray[count]->SetPos(Vector3(-110 + (110 * j), 110 + (-110 * i), 0));
			count++;
		}
	}

	//Header (showing which player's turn)
	m_gameobjectArray[count] = new GameObject(m_SpriteArray[2]);
	m_gameobjectArray[count]->SetPos(Vector3(0, 207.5, 0));
	count++;

	//Forfeit and reset button
	m_gameobjectArray[count] = new GameObject(m_SpriteArray[7]);
	m_gameobjectArray[count]->SetPos(Vector3(0, -207.5, 0));
	count++;

	//Set game condition
	m_gameCondition = GAMECONDITION::WAITING;

	ResetButtons();
}

void Application::Update()
{
	/*Calculate delta time and fps*/

	curTime = glfwGetTime();
	deltaTime = curTime - prevTime;
	prevTime = curTime;

	if (curTime - initTime >= 1.0f)
	{
		frameCount = 0;
		initTime = curTime;
	}
	else
		frameCount++;

	//================Network======================
	MyPhoton::getInstance().run();

	//=============Tic Tac Toe Update=============
	UpdateBoard();

	if (m_gameCondition == GAMECONDITION::PLAYING)
	{
		int condition = CheckWinCondition();

		if (condition == 1)
		{
			m_gameCondition = GAMECONDITION::P1WIN;
		}
		else if (condition == 2)
		{
			m_gameCondition = GAMECONDITION::P2WIN;
		}
		else if (condition == 3)
		{
			m_gameCondition = GAMECONDITION::DRAW;
		}
	}

	//SendMyData();
}

void Application::Draw()
{
	for (int i = 0; i < GAMEOBJECT_COUNT; i++)
	{
		if (m_gameobjectArray[i] != NULL)
		{
			m_gameobjectArray[i]->draw();
		}
	}
}

void Application::SendMyData(unsigned char data)
{
	MyPhoton::getInstance().sendEvent(data);
}

void Application::OnReceivedData(unsigned char data)
{
	if (data < 9)
	{
		if (m_isHost)
		{
			m_isOccupiedArray[data] = 2;
			m_isHostTurn = true;
		}
		else
		{
			m_isOccupiedArray[data] = 1;
			m_isHostTurn = false;
		}
	}
	else if (data == 9)
	{
		if (m_gameCondition == GAMECONDITION::PLAYING)
		{
			if (m_isHost)
				m_gameCondition = GAMECONDITION::P1WIN;
			else
				m_gameCondition = GAMECONDITION::P2WIN;
		}
		else if (m_gameCondition != GAMECONDITION::WAITING)
			ResetButtons();
	}
}

void Application::OnKeyPress(int key)
{
}

void Application::OnKeyRelease(int key)
{
}

void Application::OnKeyHold(int key)
{

}

void Application::OnMousePress(int key, double xPos, double yPos)
{
	double xOffset, yOffset;

	xOffset = xPos - RESOLUTION_X * 0.5;
	yOffset = -yPos + RESOLUTION_Y * 0.5;

	if (key == GLFW_MOUSE_BUTTON_LEFT)
	{
		//std::cout << "ClickPos : " << xPos << ", " << yPos << std::endl;
		//std::cout << "OffsetPos : " << xOffset << ", " << yOffset << std::endl;

		if (isLeftMouseDown) return;

		isLeftMouseDown = true;

		//Check if within play area
		if (xOffset >= -160.0 && xOffset <= 160.0 && yOffset >= -160 && yOffset <= 160)
		{
			//Check which button was pressed

			//first column
			if (xOffset <= -53.3)
			{
				//first row
				if (yOffset >= 53.3) 
				{
					OnButtonInteract(0, m_isHost);
					return;
				}
				//second row
				else if (yOffset >= -53.3) 
				{
					OnButtonInteract(3, m_isHost);
					return;
				}
				//third row
				else if (yOffset < -53.3)
				{
					OnButtonInteract(6, m_isHost);
					return;
				}
			}
			//second column
			else if (xOffset <= 53.3)
			{
				//first row
				if (yOffset >= 53.3)
				{
					OnButtonInteract(1, m_isHost);
					return;
				}
				//second row
				else if (yOffset >= -53.3)
				{
					OnButtonInteract(4, m_isHost);
					return;
				}
				//third row
				else if (yOffset < -53.3)
				{
					OnButtonInteract(7, m_isHost);
					return;
				}
			}
			//third column
			else if (xOffset >= 53.3)
			{
				//first row
				if (yOffset >= 53.3) 
				{
					OnButtonInteract(2, m_isHost);
					return;
				}
				//second row
				else if (yOffset >= -53.3)
				{
					OnButtonInteract(5, m_isHost);
					return;
				}
				//third row
				else if (yOffset < -53.3)
				{
					OnButtonInteract(8, m_isHost);
					return;
				}
			}
		}

		else if (xOffset >= -112.5 && xOffset <= 112.5 && yOffset >= -232.5 && yOffset <= -182.5)
		{
			OnButtonInteract(9, m_isHost);
		}
	}
}

void Application::OnMouseRelease(int key, double xPos, double yPos)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (isLeftMouseDown)
			isLeftMouseDown = false;
	}
}

void Application::OnMouseHold(int key)
{
}

void Application::OnButtonInteract(unsigned char index, bool isHost)
{
	if (m_gameCondition == GAMECONDITION::PLAYING)
	{
		//Mark button
		if (index < 9)
		{
			if (m_isHostTurn == isHost)
			{
				if (m_isOccupiedArray[index] == 0)
				{
					m_isOccupiedArray[index] = 2 - isHost;

					m_isHostTurn = !isHost;

					SendMyData(index);
				}
			}
		}

		//Forfeit
		else if (index == 9)
		{
			if (m_isHostTurn == isHost)
			{
				SendMyData(index);
				if (isHost)
					m_gameCondition = GAMECONDITION::P2WIN;
				else
					m_gameCondition = GAMECONDITION::P1WIN;
			}
		}
	}
	//Reset
	else if (m_gameCondition != GAMECONDITION::WAITING)
	{
		if (index == 9)
		{
			if (m_gameCondition == GAMECONDITION::P1WIN && isHost)
			{
				SendMyData(9);
				ResetButtons();
			}
			else if (m_gameCondition == GAMECONDITION::P2WIN && !isHost)
			{
				SendMyData(9);
				ResetButtons();
			}
		}
	}
}

void Application::OnServerJoin(int playerCount)
{
	if (playerCount == 1)
	{
		m_isHost = true;
	}

	if (playerCount == 2)
		m_gameCondition = GAMECONDITION::PLAYING;
}

void Application::ResetButtons(void)
{
	for (int i = 0; i < 9; i++)
	{
		m_isOccupiedArray[i] = 0;
	}

	m_isHostTurn = true;

	if (m_gameCondition != GAMECONDITION::WAITING)
	{
		m_gameCondition = GAMECONDITION::PLAYING;
	}
}

void Application::UpdateBoard(void)
{
	if (m_gameCondition != GAMECONDITION::WAITING)
	{
		for (int i = 0; i < 9; i++)
		{
			if (m_isOccupiedArray[i] == 1)
			{
				if (m_isHost)
					m_tttButtonArray[i]->SetColor(Color::blue);
				else
					m_tttButtonArray[i]->SetColor(Color::red);
			}
			else if (m_isOccupiedArray[i] == 2)
			{
				if (m_isHost)
					m_tttButtonArray[i]->SetColor(Color::red);
				else
					m_tttButtonArray[i]->SetColor(Color::blue);
			}
			else
				m_tttButtonArray[i]->SetColor(Color::white);
		}

		if (m_isHost)
		{
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[m_isHostTurn]);
		}
		else
		{
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[!m_isHostTurn]);
		}
	}

	if (m_gameCondition == GAMECONDITION::PLAYING)
	{
		m_gameobjectArray[10]->SetSprite(m_SpriteArray[7]);
		m_gameobjectArray[10]->SetColor(Color::white);
	}
	else
	{
		m_gameobjectArray[10]->SetSprite(m_SpriteArray[7]);
		m_gameobjectArray[10]->SetColor(Color(0.5, 0.5, 0.5));
	}

	if (m_gameCondition == GAMECONDITION::P1WIN)
	{
		if (m_isHost)
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[4]);
		else
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[5]);
	}
	else if (m_gameCondition == GAMECONDITION::P2WIN)
	{
		if (m_isHost)
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[5]);
		else
			m_gameobjectArray[9]->SetSprite(m_SpriteArray[4]);
	}
	else if (m_gameCondition == GAMECONDITION::DRAW)
	{
		m_gameobjectArray[9]->SetSprite(m_SpriteArray[6]);
	}

	if (m_gameCondition != GAMECONDITION::WAITING && m_gameCondition != GAMECONDITION::PLAYING)
	{
		if (m_gameCondition == GAMECONDITION::P1WIN && m_isHost)
		{
			m_gameobjectArray[10]->SetColor(Color::white);
			m_gameobjectArray[10]->SetSprite(m_SpriteArray[8]);
		}
		else if (m_gameCondition == GAMECONDITION::P2WIN && !m_isHost)
		{
			m_gameobjectArray[10]->SetColor(Color::white);
			m_gameobjectArray[10]->SetSprite(m_SpriteArray[8]);
		}
	}
}

int Application::CheckWinCondition(void)
{
	//Check for valid win conditions
	if (m_isOccupiedArray[0] != 0)
	{
		if (m_isOccupiedArray[0] == m_isOccupiedArray[1] && m_isOccupiedArray[0] == m_isOccupiedArray[2])
		{
			return m_isOccupiedArray[0];
		}
		else if (m_isOccupiedArray[0] == m_isOccupiedArray[3] && m_isOccupiedArray[0] == m_isOccupiedArray[6])
		{
			return m_isOccupiedArray[0];
		}
		else if (m_isOccupiedArray[0] == m_isOccupiedArray[4] && m_isOccupiedArray[0] == m_isOccupiedArray[8])
		{
			return m_isOccupiedArray[0];
		}
	}
	else if (m_isOccupiedArray[3] != 0)
	{
		if (m_isOccupiedArray[3] == m_isOccupiedArray[4] && m_isOccupiedArray[3] == m_isOccupiedArray[5])
		{
			return m_isOccupiedArray[3];
		}
	}
	else if (m_isOccupiedArray[6] != 0)
	{
		if (m_isOccupiedArray[6] == m_isOccupiedArray[4] && m_isOccupiedArray[6] == m_isOccupiedArray[2])
		{
			return m_isOccupiedArray[6];
		}
		else if (m_isOccupiedArray[6] == m_isOccupiedArray[7] && m_isOccupiedArray[6] == m_isOccupiedArray[8])
		{
			return m_isOccupiedArray[6];
		}
	}
	else if (m_isOccupiedArray[2] != 0)
	{
		if (m_isOccupiedArray[2] == m_isOccupiedArray[5] && m_isOccupiedArray[2] == m_isOccupiedArray[8])
		{
			return m_isOccupiedArray[2];
		}
	}
	else if (m_isOccupiedArray[1] != 0)
	{
		if (m_isOccupiedArray[1] == m_isOccupiedArray[4] && m_isOccupiedArray[1] == m_isOccupiedArray[7])
		{
			return m_isOccupiedArray[1];
		}
	}
	
	//Check if all spaces are filled
	for (int i = 0; i < 9; i++)
	{
		if (m_isOccupiedArray[i] == 0)
		{
			return 0;
		}
	}
	
	return 3;
}
