#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class PlayerCustomClothes : public GameEngineActor
{
public:
	static PlayerCustomClothes* MainPlayerCustomClothes;
	// constrcuter destructer
	PlayerCustomClothes();
	~PlayerCustomClothes();

	// delete Function
	PlayerCustomClothes(const PlayerCustomClothes& _Other) = delete;
	PlayerCustomClothes(PlayerCustomClothes&& _Other) noexcept = delete;
	PlayerCustomClothes& operator=(const PlayerCustomClothes& _Other) = delete;
	PlayerCustomClothes& operator=(PlayerCustomClothes&& _Other) noexcept = delete;

private:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineRenderer* ClothesShirts_;
	GameEngineRenderer* ClothesPants_;

public:
	void UpdateOn();
	void UpdateOff();
};

