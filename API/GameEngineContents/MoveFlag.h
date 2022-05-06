#pragma once
#include "Items.h"

// Ό³Έν :
class MoveFlag : public Items
{
public:
	// constrcuter destructer
	MoveFlag();
	~MoveFlag();

	// delete Function
	MoveFlag(const MoveFlag& _Other) = delete;
	MoveFlag(MoveFlag&& _Other) noexcept = delete;
	MoveFlag& operator=(const MoveFlag& _Other) = delete;
	MoveFlag& operator=(MoveFlag&& _Other) noexcept = delete;

private:
	void Start() override;

public:
	void CreateMoveFlag(std::string _CollName) override;
	void ChnageImageFile(std::string _FileName) override;
	void CreateSubCollision(std::string _CollName, float4 _Size) override;
};

