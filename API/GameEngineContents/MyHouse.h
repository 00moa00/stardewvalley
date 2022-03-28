#pragma once

// Ό³Έν :
class MyHouse
{
public:
	// constrcuter destructer
	MyHouse();
	~MyHouse();

	// delete Function
	MyHouse(const MyHouse& _Other) = delete;
	MyHouse(MyHouse&& _Other) noexcept = delete;
	MyHouse& operator=(const MyHouse& _Other) = delete;
	MyHouse& operator=(MyHouse&& _Other) noexcept = delete;

protected:

private:

};

