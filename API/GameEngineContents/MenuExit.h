#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class MenuExit : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuExit();
	~MenuExit();

	// delete Function
	MenuExit(const MenuExit& _Other) = delete;
	MenuExit(MenuExit&& _Other) noexcept = delete;
	MenuExit& operator=(const MenuExit& _Other) = delete;
	MenuExit& operator=(MenuExit&& _Other) noexcept = delete;

private:
	void Start()override;
	void Render()override;
	void Update() override;

private:

	GameEngineRenderer* MenuExit_;
	GameEngineCollision* NewGameCollision_;

	std::vector<GameEngineCollision*> ColList;

private:
	bool isMouseOver()
	{
		return (NewGameCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}
};

