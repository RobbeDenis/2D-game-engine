#pragma once
#include <Component.h>
#include <TextRenderer.h>

namespace pacman
{
	class TypeName : public dae::Component
	{
	public:
		TypeName(dae::GameObject* gameObject);

		void Loaded() override;
		void Start() override;

		void MoveIndex(int dir);
		void ChangeCharacter(int offset);
		void ConfirmName();

	private:
		void UpdateName();

		dae::TextRenderer* m_pText;
		std::string m_Name;
		unsigned m_MaxLength;
		int m_Index;
	};
}