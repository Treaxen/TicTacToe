#include "MyPhoton.h"
#include <iostream>
#include "Application.h"

static const ExitGames::Common::JString appId = L"101139e2-8c94-4c62-9e00-e1b2e479632f"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static const ExitGames::Common::JString PLAYER_NAME = L"Windows";


// functions
MyPhoton::MyPhoton() : mLoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::TCP)
{
}

void MyPhoton::connect(void)
{
	std::wcout<<"Connecting..."<<std::endl;
	mLoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues(), PLAYER_NAME);
}

void MyPhoton::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

/*
void MyPhoton::opCreateRoom(void)
{
	ExitGames::Common::JString name;
	name += GETTIMEMS();
	mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(4).setPlayerTtl(INT_MAX/2).setEmptyRoomTtl(10000));
	//mStateAccessor.setState(STATE_JOINING);
	//mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room ") + name + L"...");
}

void MyPhoton::opJoinRandomRoom(void)
{
	mLoadBalancingClient.opJoinRandomRoom();
}

void MyPhoton::opJoinOrCreateRoom(void)
{
	ExitGames::Common::JString name("DemoLoadBalancing");
	mLoadBalancingClient.opJoinOrCreateRoom(name);
	//mStateAccessor.setState(STATE_JOINING);
	//mpOutputListener->writeLine(ExitGames::Common::JString(L"joining or creating room ") + name + L"...");
}
*/

void MyPhoton::run(void)
{
	mLoadBalancingClient.service();
}

void MyPhoton::sendEvent(unsigned char packedData)
{
	//int myID = 113695;
	//mLoadBalancingClient.opRaiseEvent(false, myID, 0);

	mLoadBalancingClient.opRaiseEvent(true, packedData, 1);
}

// protocol implementations

void MyPhoton::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
}

void MyPhoton::connectionErrorReturn(int errorCode)
{
	std::wcout<<"connectionErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::clientErrorReturn(int errorCode)
{
	std::wcout<<"clientErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::warningReturn(int warningCode)
{
	std::wcout<<"warningReturn : "<<warningCode<<std::endl;
}

void MyPhoton::serverErrorReturn(int errorCode)
{
	std::wcout<<"serverErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	std::wcout<<"joinRoomEventAction, Player Count: "<< playerNr <<std::endl;
	Application::GetInstance().OnServerJoin(playerNr);
}

void MyPhoton::leaveRoomEventAction(int playerNr, bool isInactive)
{
	std::wcout<<"leaveRoomEventAction"<<std::endl;
}

void MyPhoton::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	// you do not receive your own events, unless you specify yourself as one of the receivers explicitly, so you must start 2 clients, to receive the events, which you have sent, as sendEvent() uses the default receivers of opRaiseEvent() (all players in same room like the sender, except the sender itself)
	//int receivedData = ExitGames::Common::ValueObject<int>(eventContent).getDataCopy();
	//std::cout << "received : " << receivedData << std::endl;

	unsigned char data = ExitGames::Common::ValueObject<unsigned char>(eventContent).getDataCopy();

	Application::GetInstance().OnReceivedData(data);
}

void MyPhoton::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster)
{
	if(errorCode)
		std::wcout<<"Failed to connect : "<<errorString.cstr()<<std::endl;
	else
	{
		std::wcout<<"Connected to Photon Server."<<std::endl;
		
		std::wcout<<"Trying to join a random room..."<<std::endl;
		mLoadBalancingClient.opJoinRandomRoom();
	}
}

void MyPhoton::disconnectReturn(void)
{
	std::wcout<<"disconnected"<<std::endl;
}

void MyPhoton::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"createRoomReturn"<<std::endl;
}

void MyPhoton::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinOrCreateRoomReturn"<<std::endl;
}

void MyPhoton::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinRoomReturn"<<std::endl;
}

void MyPhoton::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinRandomRoomReturn"<<std::endl;

	if(errorCode)
	{
		std::wcout<<"Failed to join a random room : "<<errorCode<<", "<<errorString.cstr()<<std::endl;

		if(errorCode == 32760) //no match found error code
		{
			std::wcout<<"Creating a room..."<<std::endl;
			//try to create a room and wait;
			ExitGames::Common::JString name;
			name += GETTIMEMS();
			mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(4));
		}

		return;
	}
}

void MyPhoton::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"leaveRoomReturn"<<std::endl;
}

void MyPhoton::joinLobbyReturn(void)
{
	std::wcout<<"joinLobbyReturn"<<std::endl;
}

void MyPhoton::leaveLobbyReturn(void)
{
	std::wcout<<"leaveLobbyReturn"<<std::endl;
}

void MyPhoton::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout<<"onLobbyStatsResponse"<<std::endl;
}

void MyPhoton::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout<<"onLobbyStatsUpdate"<<std::endl;
}

void MyPhoton::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
//	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls / %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
//	mpOutputListener->writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
	// select first region from list
	//mpOutputListener->writeLine(L"selecting region: " + availableRegions[0]);
	mLoadBalancingClient.selectRegion(availableRegions[0]);
}
