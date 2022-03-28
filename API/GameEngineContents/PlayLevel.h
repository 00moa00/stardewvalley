#pragma once
#include <GameEngine/GameEngineLevel.h>

#include "Player.h"
#include "PlayerHair.h"
#include "PlayerPants.h"
#include "PlayerShirts.h"

#include "PlayerEnergyBar.h"
#include "PlayerEnergyFrame.h"


// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:
	Player* Player_;
	PlayerEnergyBar* PlayerEnergyBar_;
	PlayerEnergyFrame* PlayerEnergyFrame_;
	PlayerHair* PlayerHair_;
	PlayerPants* PlayerPants_;
	PlayerShirts* PlayerShirts_;

};