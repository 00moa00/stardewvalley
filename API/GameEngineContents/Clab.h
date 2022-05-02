#pragma once

// Ό³Έν :
class Clab
{
public:
	// constrcuter destructer
	Clab();
	~Clab();

	// delete Function
	Clab(const Clab& _Other) = delete;
	Clab(Clab&& _Other) noexcept = delete;
	Clab& operator=(const Clab& _Other) = delete;
	Clab& operator=(Clab&& _Other) noexcept = delete;

protected:

private:

};

