#pragma once
#include "Items.h"
// Ό³Έν :
class Block : public Items
{
public:
	// constrcuter destructer
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	//void Update() override;
	//void Render() override;
};

