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
class Weeds : public GameEngineActor
{
public:
	// constrcuter destructer
	Weeds();
	~Weeds();

	// delete Function
	Weeds(const Weeds& _Other) = delete;
	Weeds(Weeds&& _Other) noexcept = delete;
	Weeds& operator=(const Weeds& _Other) = delete;
	Weeds& operator=(Weeds&& _Other) noexcept = delete;

	bool isPlayerHas() {
		return isPlayerHas_;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:

	bool isPlayerHas_ = false;

	GameEngineRenderer* Weeds_;

};

