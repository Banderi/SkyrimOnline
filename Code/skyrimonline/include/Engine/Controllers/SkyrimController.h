#pragma once

#include <stdafx.h>

#include "SkyrimTest.h"
#include <Engine/Interfaces/IController.h>
#include <skse/GameReferences.h>
#include <Engine/World.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			class SkyrimUserInterface : public Interfaces::IUserInterface
			{
			public:

				SkyrimUserInterface();
				~SkyrimUserInterface();

				void Debug(const std::string& acString);
			};

			class SkyrimPlayer : public Interfaces::IPlayer
			{
			public:

				SkyrimPlayer();
				~SkyrimPlayer();

				const std::string GetName();

			private:

				Actor* m_pPlayer;
			};

			class SkyrimController : public Interfaces::IController
			{
			public:

				SkyrimController();
				~SkyrimController();
				
				void Update();

				void EnableInput();
				void DisableInput();

				Interfaces::IUserInterface* GetUI();
				Interfaces::IPlayer* GetPlayer();
				
				void SendMessage(Packet* apPacket);
				void SendReliableMessage(Packet* apPacket);

			private:

				SkyrimUserInterface m_userInterface;
				SkyrimPlayer m_player;
				World m_world;
				SkyrimTest m_test;
			};
		}
	}
}