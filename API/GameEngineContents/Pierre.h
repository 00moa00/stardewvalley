#pragma once

// Ό³Έν :
class Pierre
{
public:
	// constrcuter destructer
	Pierre();
	~Pierre();

	// delete Function
	Pierre(const Pierre& _Other) = delete;
	Pierre(Pierre&& _Other) noexcept = delete;
	Pierre& operator=(const Pierre& _Other) = delete;
	Pierre& operator=(Pierre&& _Other) noexcept = delete;

protected:

private:

};

