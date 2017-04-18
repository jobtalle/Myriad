#pragma once

#include <cstdint>

class QuadSpace
{
public:
	class Node
	{
	public:
		Node() {};
		Node(const bool valid, const uint8_t x = 0, const uint8_t y = 0, const uint16_t node = 0);
		uint8_t getX() const;
		uint8_t getY() const;
		uint16_t getNode() const;

	private:
		uint8_t x;
		uint8_t y;
		uint8_t valid:1;
		uint16_t node:15;
	};

	static const unsigned char dimensions = 128;

	QuadSpace();
	~QuadSpace();
	Node query(const uint8_t scale);
	void release(const Node node);

private:
	static const unsigned int nodeCount = 21845;
	unsigned char *nodes;

	uint8_t level(const Node node) const;
	void validateParent(const unsigned int child, const uint8_t scale);
	unsigned int getParent(const unsigned int node) const;
	unsigned int getChildren(const unsigned int node) const;
};