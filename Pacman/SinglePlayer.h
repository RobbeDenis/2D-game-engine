#pragma once
#include "Gamemode.h"

namespace pacman
{
    class Character;
    class SinglePlayer final : public Gamemode
    {
    public:
        SinglePlayer(dae::GameObject* pGameObject);

        void Loaded() override;
        void Start() override;
        void SkipLevel() override;
        void AddPlayer(Character* player);
        void OnNotify(unsigned event) override;

    private:
        Character* m_pPlayer;
    };
}