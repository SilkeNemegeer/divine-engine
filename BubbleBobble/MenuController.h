#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
namespace divengine
{
	class GameObject;
	class RenderComponent;
}
class Button;
class MenuController : public divengine::BaseComponent
{
public:
	enum ButtonType : unsigned int
	{
		singleplayer,
		coop,
		pvp,
		exit,
		COUNT
	};

	MenuController();
	~MenuController();
	void NavigateUp();
	void NavigateDown();
	void Select();

	virtual void Update() override;
	virtual void Render() override {};
	virtual void Initialize() override;
	/*virtual void Load(std::istream& istream) override;
	virtual void Save(std::ostream& istream) override;	*/
	virtual void Load(divengine::BinaryReader& istream) override;
	virtual void Save(divengine::BinaryWriter& istream) override;

private:
	divengine::GameObject* CreateButton(const std::string& text, const glm::vec2& pos);
	divengine::GameObject* m_pSelectIcon;
	void CreateButtons();
	std::vector<divengine::GameObject*> m_pButtons;
	void SelectButton(int id, int oldId);
	int m_CurrentButtonId;
	glm::vec2 m_OffsetIcon;
};

