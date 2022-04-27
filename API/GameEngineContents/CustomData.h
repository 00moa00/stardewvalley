#pragma once
#include <string>
// Ό³Έν :
class CustomData
{
public:
	// constrcuter destructer
	CustomData();
	~CustomData();

	// delete Function
	CustomData(const CustomData& _Other) = delete;
	CustomData(CustomData&& _Other) noexcept = delete;
	CustomData& operator=(const CustomData& _Other) = delete;
	CustomData& operator=(CustomData&& _Other) noexcept = delete;

private:
	static CustomData* Inst_;

public:
	static CustomData* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}


private:

	std::string HairFileName_;
	std::string ShirtsFileName_;
	std::string HandFileName_;
	std::string PantsName_;

public:

	void SetHairFileName(std::string _Name)
	{
		HairFileName_ = _Name;
	}

	void SetShirtsFileName(std::string _Name)
	{
		ShirtsFileName_ = _Name;
	}	

	void SetHandFileName(std::string _Name)
	{
		HandFileName_ = _Name;
	}	
	
	void SetPantsFileName(std::string _Name)
	{
		PantsName_ = _Name;
	}	

	std::string GetHairFileName()
	{
		return HairFileName_;
	}

	std::string GetShirtsFileName()
	{
		return ShirtsFileName_;
	}

	std::string GetHandFileName()
	{
		return HandFileName_;
	}

	std::string GetPantsFileName()
	{
		return PantsName_;
	}

};

