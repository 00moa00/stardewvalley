#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :
class MenuNewGame : public GameEngineActor
{
public:
	// constrcuter destructer
	MenuNewGame();
	~MenuNewGame();

	// delete Function
	MenuNewGame(const MenuNewGame& _Other) = delete;
	MenuNewGame(MenuNewGame&& _Other) noexcept = delete;
	MenuNewGame& operator=(const MenuNewGame& _Other) = delete;
	MenuNewGame& operator=(MenuNewGame&& _Other) noexcept = delete;

private:
	void Start()override;
	void Render()override;
	void Update() override;


private:
	bool isMouseOver_;
	bool CustomBoardOpen_;

	GameEngineRenderer* NewGame_;
	GameEngineCollision* NewGameCollision_;

	std::vector<GameEngineCollision*> ColList;


private:
	bool isMouseOver()
	{
		return (NewGameCollision_->CollisionResult("MouseCursor", ColList, CollisionType::Rect, CollisionType::Rect));
	}

public:
	bool GetisCustomBoardOpen()
	{
		return CustomBoardOpen_;
	}

};

