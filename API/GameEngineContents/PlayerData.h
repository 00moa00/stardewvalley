#pragma once

class PlayerDir {

public:

	PlayerDir() :
		isFrontDir_(false),
		isBackDir_(false),
		isRightDir_(false),
		isLeftDir_(false),
		isInit_(false)
	{

	}

	~PlayerDir() {

	}

public:

	bool isFrontDir_ = false;
	bool isBackDir_ = false;
	bool isRightDir_ = false;
	bool isLeftDir_ = false;
	bool isInit_ = false;

	void SetFrontDir(bool b) {
		isFrontDir_ = b;
		isBackDir_ = false;
		isRightDir_ = false;
		isLeftDir_ = false;
	}

	void SetBackDir(bool b) {
		isFrontDir_ = false;
		isBackDir_ = b;
		isRightDir_ = false;
		isLeftDir_ = false;
	}

	void setRightDir(bool b) {
		isFrontDir_ = false;
		isBackDir_ = false;
		isRightDir_ = b;
		isLeftDir_ = false;
	}

	void SetLeftDir(bool b) {
		isFrontDir_ = false;
		isBackDir_ = false;
		isRightDir_ = false;
		isLeftDir_ = b;
	}

	void SetDirInit(bool b) {

		isInit_ = b;
	}
};

enum class PLAYERSTATE {
	INIT = 0,
	TOOL_USE,
	MOVE,
};
