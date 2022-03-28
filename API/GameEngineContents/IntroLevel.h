#pragma once

// Ό³Έν :
class IntroLevel
{
public:
	// constrcuter destructer
	IntroLevel();
	~IntroLevel();

	// delete Function
	IntroLevel(const IntroLevel& _Other) = delete;
	IntroLevel(IntroLevel&& _Other) noexcept = delete;
	IntroLevel& operator=(const IntroLevel& _Other) = delete;
	IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;

protected:

private:

};

