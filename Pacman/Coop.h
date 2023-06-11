#pragma once
#include "Gamemode.h"
#include <TestCommands.h>

namespace pacman
{
    class Character;
	class Coop final : public Gamemode
	{
    public:
        Coop(dae::GameObject* pGameObject);

        void Start() override;
        void SkipLevel() override;
        void OnNotify(unsigned event) override;

        void AddPlayer1(Character* p);
        void AddPlayer2(Character* p);

    private:
        Character* m_pPlayer1;
        Character* m_pPlayer2;
        unsigned m_PlayersKilled;
	};
}