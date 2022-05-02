#pragma once

// Ό³Έν :
class Bat
{
public:
	// constrcuter destructer
	Bat();
	~Bat();

	// delete Function
	Bat(const Bat& _Other) = delete;
	Bat(Bat&& _Other) noexcept = delete;
	Bat& operator=(const Bat& _Other) = delete;
	Bat& operator=(Bat&& _Other) noexcept = delete;

protected:

private:

};

