#pragma once

// Ό³Έν :
class PlayerHPFrame
{
public:
	// constrcuter destructer
	PlayerHPFrame();
	~PlayerHPFrame();

	// delete Function
	PlayerHPFrame(const PlayerHPFrame& _Other) = delete;
	PlayerHPFrame(PlayerHPFrame&& _Other) noexcept = delete;
	PlayerHPFrame& operator=(const PlayerHPFrame& _Other) = delete;
	PlayerHPFrame& operator=(PlayerHPFrame&& _Other) noexcept = delete;

protected:

private:

};

