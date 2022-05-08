#pragma once
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "NpcData.h"
#include "Font.h"

// Ό³Έν :
class ItemDataBox : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemDataBox();
	~ItemDataBox();

	// delete Function
	ItemDataBox(const ItemDataBox& _Other) = delete;
	ItemDataBox(ItemDataBox&& _Other) noexcept = delete;
	ItemDataBox& operator=(const ItemDataBox& _Other) = delete;
	ItemDataBox& operator=(ItemDataBox&& _Other) noexcept = delete;

private:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* ItemDataBoxRenderer_;

	Font* NameFont_;
	Font* DataFont_;


private:
public:
	void SetData(std::string _Name, std::string _Data, float4 _Pos);

	void ItemDataBoxOn();
	void ItemDataBoxOff();



};

#pragma once
