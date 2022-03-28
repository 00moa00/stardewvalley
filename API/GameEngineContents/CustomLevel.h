#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "PlayerCustomBoard.h"


#include "Player.h"
#include "PlayerHair.h"
#include "PlayerPants.h"
#include "PlayerShirts.h"
#include "TitleBackGround.h"
#include "PlayerBackGround.h"
#include "RightArrow.h"
#include "LeftArrow.h"


// Ό³Έν :
class CustomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CustomLevel();
	~CustomLevel();

	// delete Function
	CustomLevel(const CustomLevel& _Other) = delete;
	CustomLevel(CustomLevel&& _Other) noexcept = delete;
	CustomLevel& operator=(const CustomLevel& _Other) = delete;
	CustomLevel& operator=(CustomLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart() override;

private:
	
	TitleBackGround* BackGround_;
	PlayerBackGround* PlayerBackGround_;
	PlayerCustomBoard* PlayerCustomBoard_;

	Player* Player_;
	PlayerHair* PlayerHair_;
	PlayerPants* PlayerPants_;
	PlayerShirts* PlayerShirts_;

	RightArrow* RightArrow_[3];
	LeftArrow* LeftArrow_[3];

};

