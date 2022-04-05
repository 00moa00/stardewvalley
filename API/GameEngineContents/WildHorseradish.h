#pragma once
#include "Items.h"
#include <GameEngine/GameEngineRenderer.h>

enum class Type {
	TOOL,
	DRINK,
	ADDITEM
};

struct ItemData
{
	std::string ItemName_;


};



// Ό³Έν :
class WildHorseradish : public GameEngineActor
{
public:
	// constrcuter destructer
	WildHorseradish();
	~WildHorseradish();

	// delete Function
	WildHorseradish(const WildHorseradish& _Other) = delete;
	WildHorseradish(WildHorseradish&& _Other) noexcept = delete;
	WildHorseradish& operator=(const WildHorseradish& _Other) = delete;
	WildHorseradish& operator=(WildHorseradish&& _Other) noexcept = delete;

	bool isPlayerHas() {
		return isPlayerHas_;
	}
	void thisCreateActor();

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	bool isPlayerHas_ = false;

	GameEngineRenderer* WildHorseradish_;

};

