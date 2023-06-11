#pragma once
#include "Gamemode.h"

namespace pacman
{
    class Character;
	class Versus : public Gamemode
	{
    public:
        Versus(dae::GameObject* pGameObject);

        void Start() override;
        void SkipLevel() override;
        void AddPlayer(Character* player);
        void OnNotify(unsigned event) override;

    private:
        Character* m_pPlayer;
	};
}