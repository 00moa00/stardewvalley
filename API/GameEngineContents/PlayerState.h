#pragma once

// Ό³Έν :
class PlayerState
{
public:
	// constrcuter destructer
	PlayerState();
	~PlayerState();

	// delete Function
	PlayerState(const PlayerState& _Other) = delete;
	PlayerState(PlayerState&& _Other) noexcept = delete;
	PlayerState& operator=(const PlayerState& _Other) = delete;
	PlayerState& operator=(PlayerState&& _Other) noexcept = delete;

	bool isFrontWalk_;
	bool isBackWalk_;
	bool isRightWalk_;
	bool isLeftWalk_;
	bool isInit_;


	bool GetIsFrontWalk() {
		return isFrontWalk_;
	}

	bool GetIsBackWalk() {
		return isBackWalk_;
	}

	bool GetIsLeftWalk() {
		return isLeftWalk_;
	}

	bool GetIsRightWalk() {
		return isRightWalk_;
	}

	bool GetIsWalkInit() {
		return isInit_;
	}

	void SetFrontWalk(bool b) {
		isFrontWalk_ = b;
		isBackWalk_ = false;
		isRightWalk_ = false;
		isLeftWalk_ = false;
	}

	void SetBackWalk(bool b) {
		isFrontWalk_ = false;
		isBackWalk_ = b;
		isRightWalk_ = false;
		isLeftWalk_ = false;
	}

	void setRightWalk(bool b) {
		isFrontWalk_ = false;
		isBackWalk_ = false;
		isRightWalk_ = b;
		isLeftWalk_ = false;
	}

	void SetLeftWalk(bool b) {
		isFrontWalk_ = false;
		isBackWalk_ = false;
		isRightWalk_ = false;
		isLeftWalk_ = b;
	}

	void SetWalkInit(bool b) {
		isInit_ = b;
	}

	void ResetAllState() {
		isFrontWalk_ = false;
		isBackWalk_ = false;
		isRightWalk_ = false;
		isLeftWalk_ = false;
	}

protected:



private:

};

