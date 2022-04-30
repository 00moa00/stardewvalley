#pragma once

// Ό³Έν :
class MineLevel
{
public:
	// constrcuter destructer
	MineLevel();
	~MineLevel();

	// delete Function
	MineLevel(const MineLevel& _Other) = delete;
	MineLevel(MineLevel&& _Other) noexcept = delete;
	MineLevel& operator=(const MineLevel& _Other) = delete;
	MineLevel& operator=(MineLevel&& _Other) noexcept = delete;

protected:

private:

};

