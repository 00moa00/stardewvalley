#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class MenuLoad : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuLoad();
	~MenuLoad();

	// delete Function
	MenuLoad(const MenuLoad& _Other) = delete;
	MenuLoad(MenuLoad&& _Other) noexcept = delete;
	MenuLoad& operator=(const MenuLoad& _Other) = delete;
	MenuLoad& operator=(MenuLoad&& _Other) noexcept = delete;

private:
	void Start()override;
	void Render()override;
	void Update() override;

private:

	GameEngineRenderer* Load_;
	GameEngineCollision* NewGameCollision_;
	std::vector<GameEngineCollision*> ColList;

private:
	bool isMouseOver()
	{
		return (NewGameCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}
};

