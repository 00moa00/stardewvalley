#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
// Ό³Έν :
class MenuButton : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuButton();
	~MenuButton();

	// delete Function
	MenuButton(const MenuButton& _Other) = delete;
	MenuButton(MenuButton&& _Other) noexcept = delete;
	MenuButton& operator=(const MenuButton& _Other) = delete;
	MenuButton& operator=(MenuButton&& _Other) noexcept = delete;

private:
	void Start()override;
	void Update() override;

private:
	GameEngineRenderer* ButtonRenderer_;
	GameEngineCollision* ButtonCollision_;
	std::vector<GameEngineCollision*> ColList;

	int Index_;

public:
	void CreateButtonRenderer(std::string _FileName, int _Index);
	void CreateButtonRenderer(std::string _FileName);

	void CreateButtonCollision(std::string _CollName, float4 _CollSize);
	
	void MouseOverChangeIndex();

	bool ButtomMouseOver();
	bool ButtonMouseOverAndLeftClick();

	GameEngineRenderer* GetRenderer()
	{
		return ButtonRenderer_;
	}

	GameEngineCollision* GetCollision()
	{
		return ButtonCollision_;
	}

};

