#pragma once
#include <GameEngine/GameEngineLevel.h>



#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"
#include "MainUI.h"
#include "TitleBackGround.h"
#include "Player.h"
#include "RendererEnum.h"
#include "Inventory.h"
#include "Items.h"
#include "Mouse.h"

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

	MainUI* MainUI_;

	Player* Player_;
	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	TitleBackGround* TitleBackGround_;

};