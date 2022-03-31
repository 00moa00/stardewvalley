#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "PlayerBody.h"
#include "PlayerHair.h"
#include "PlayerPants.h"
#include "PlayerShirts.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"

#include "PlayerHand.h"


// Ό³Έν :
class MyHouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MyHouseLevel();
	~MyHouseLevel();

	// delete Function
	MyHouseLevel(const MyHouseLevel& _Other) = delete;
	MyHouseLevel(MyHouseLevel&& _Other) noexcept = delete;
	MyHouseLevel& operator=(const MyHouseLevel& _Other) = delete;
	MyHouseLevel& operator=(MyHouseLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:
	PlayerBody* PlayerBody_;
	PlayerHand* PlayerHand_;

	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	PlayerHair* PlayerHair_;
	PlayerPants* PlayerPants_;
	PlayerShirts* PlayerShirts_;
	MainUI* MainUI_;

};