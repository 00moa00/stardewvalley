#pragma once

// Ό³Έν :
class Golem
{
public:
	// constrcuter destructer
	Golem();
	~Golem();

	// delete Function
	Golem(const Golem& _Other) = delete;
	Golem(Golem&& _Other) noexcept = delete;
	Golem& operator=(const Golem& _Other) = delete;
	Golem& operator=(Golem&& _Other) noexcept = delete;

protected:

private:

};

