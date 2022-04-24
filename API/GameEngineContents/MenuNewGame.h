#pragma once
#include <GameEngine/GameEngineActor.h>

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

	void MouseEvent();
	bool MouseOver();

protected:

	void Start()override;
	void Render()override;
	void Update() override;


private:

	bool isMouseOver_;

	GameEngineRenderer* NewGame_;
	GameEngineCollision* NewGameCollision_;

};

