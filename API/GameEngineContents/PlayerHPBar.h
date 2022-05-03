#pragma once

// Ό³Έν :
class PlayerHPBar
{
public:
	// constrcuter destructer
	PlayerHPBar();
	~PlayerHPBar();

	// delete Function
	PlayerHPBar(const PlayerHPBar& _Other) = delete;
	PlayerHPBar(PlayerHPBar&& _Other) noexcept = delete;
	PlayerHPBar& operator=(const PlayerHPBar& _Other) = delete;
	PlayerHPBar& operator=(PlayerHPBar&& _Other) noexcept = delete;

protected:

private:

};

