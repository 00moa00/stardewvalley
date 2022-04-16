#pragma once
#include "Items.h"
enum class MOVE
{
	INIT,
	Y_UP,
	Y_DOWN
};

// Ό³Έν :
class MiniStone : public Items
{
public:
	// constrcuter destructer
	MiniStone();
	~MiniStone();

	// delete Function
	MiniStone(const MiniStone& _Other) = delete;
	MiniStone(MiniStone&& _Other) noexcept = delete;
	MiniStone& operator=(const MiniStone& _Other) = delete;
	MiniStone& operator=(MiniStone&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

	float4 targetPos_;
	float4 TransformPos_;
	float4 Normal_ ;

	MOVE State_;
};

