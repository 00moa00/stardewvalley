#pragma once

// Ό³Έν :
class Omelet
{
public:
	// constrcuter destructer
	Omelet();
	~Omelet();

	// delete Function
	Omelet(const Omelet& _Other) = delete;
	Omelet(Omelet&& _Other) noexcept = delete;
	Omelet& operator=(const Omelet& _Other) = delete;
	Omelet& operator=(Omelet&& _Other) noexcept = delete;

protected:

private:

};

