#pragma once

// Ό³Έν :
class BakedFish
{
public:
	// constrcuter destructer
	BakedFish();
	~BakedFish();

	// delete Function
	BakedFish(const BakedFish& _Other) = delete;
	BakedFish(BakedFish&& _Other) noexcept = delete;
	BakedFish& operator=(const BakedFish& _Other) = delete;
	BakedFish& operator=(BakedFish&& _Other) noexcept = delete;

protected:

private:

};

