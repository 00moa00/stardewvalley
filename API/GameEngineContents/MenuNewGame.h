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


	bool GetIsClick() {

		return isClick_;
	}

	void SetIsClick(const bool b) {

		isClick_ = b;

	}



protected:

	void Start()override;
	void Render()override;
	void Update() override;


private:

	bool isClick_;

	GameEngineRenderer* NewGame_;


};

