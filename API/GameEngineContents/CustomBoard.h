#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>
#include "ArrowButton.h"
#include "MenuButton.h"
#include "Font.h"

// Ό³Έν :

enum class CUSTOM_STATE
{
	WAIT,

	HAIR_ADD,
	HAIR_SUB,

	SHIRTS_ADD,
	SHIRTS_SUB,

	PANTS_ADD,
	PANTS_SUB,

	CHANGE_RIGHT,
	CHANGE_LEFT,

	NEXT,

	MAX
};



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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

	GameEngineRenderer* CustomBody_;
	GameEngineRenderer* CustomHand_;
	GameEngineRenderer* CustomShirts_;
	GameEngineRenderer* CustomPants_;
	GameEngineRenderer* CustomHair_;


	GameEngineRenderer* CustomBoardRenderer_;

	ArrowButton* HairAddButton_;
	ArrowButton* HairSubButton_;
	ArrowButton* ShirtAddButton_;
	ArrowButton* ShirtSubButton_;
	ArrowButton* PantsAddButton_;
	ArrowButton* PantsSubButton_;

	ArrowButton* DirChangeRightArrow_;
	ArrowButton* DirChangeLeftArrow_;


	MenuButton* OKButton_;

	Font* HairFont_;
	Font* ShirtFont_;
	Font* PantsFont_;

	CUSTOM_STATE CustomUpdate_;

	bool isCustomUpdate_;

	int HairIndex_;
	int ShirtIndex_;
	int PantsIndex_;

	int DirIndex_;


	std::string HairString[3];
	std::string ShirtsString[5];
	std::string PantsString[2];


public:

	void CustomBoardOff();
	void CustomBoardOn();


	GameEngineRenderer* GetRenderer()
	{
		return CustomBoardRenderer_;
	}
};


