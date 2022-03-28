#pragma once

// Ό³Έν :
class MapleTree
{
public:
	// constrcuter destructer
	MapleTree();
	~MapleTree();

	// delete Function
	MapleTree(const MapleTree& _Other) = delete;
	MapleTree(MapleTree&& _Other) noexcept = delete;
	MapleTree& operator=(const MapleTree& _Other) = delete;
	MapleTree& operator=(MapleTree&& _Other) noexcept = delete;

protected:

private:

};

