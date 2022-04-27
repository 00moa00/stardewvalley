#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "ArrowButton.h"

// Ό³Έν :
class CustomBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	CustomBoard();
	~CustomBoard();

	// delete Function
	CustomBoard(const CustomBoard& _Other) = delete;
	CustomBoard(CustomBoard&& _Other) noexcept = delete;
	CustomBoard& operator=(const CustomBoard& _Other) = delete;
	CustomBoard& operator=(CustomBoard&& _Other) noexcept = delete;

private:
	void Start()override;
	void Update() override;

private:
	GameEngineRenderer* CustomBoardRenderer_;
	ArrowButton* ArrowButton_[6];

public:

	void CustomBoardOff();
	void CustomBoardOn();


	GameEngineRenderer* GetRenderer()
	{
		return CustomBoardRenderer_;
	}
};


