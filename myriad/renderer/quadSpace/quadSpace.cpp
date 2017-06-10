#include <algorithm>
#include <cmath>

#include "quadSpace.h"

namespace {
	unsigned int pow2(const unsigned int pwr)
	{
		return 1 << pwr;
	}

	unsigned int pow4(const unsigned int pwr)
	{
		return 1 << (pwr << 1);
	}
}

QuadSpace::QuadSpace()
{
	nodes = new unsigned char[nodeCount];
	
	std::fill(nodes, nodes + nodeCount, 0xFF);
}

QuadSpace::~QuadSpace()
{
	delete[] nodes;
}

QuadSpace::Node QuadSpace::query(const uint8_t scale)
{
	unsigned int node = 0;
	uint8_t currentScale = 0;

	if(!(nodes[node] & (1 << scale)))
		return Node(false);

	uint8_t x = 0;
	uint8_t y = 0;

	while(currentScale != scale)
	{
		unsigned int children = getChildren(node);
		unsigned int atomStride = pow2(6 - currentScale);
		uint8_t quarter;

		for(quarter = 0; quarter < 4; ++quarter)
			if(nodes[children + quarter] & (1 << scale))
				break;

		if(quarter == 1 || quarter == 3)
			x += atomStride;
		if(quarter > 1)
			y += atomStride;

		node = children + quarter;
		++currentScale;
	}

	nodes[node] = 0;
	if(scale != 0)
		validateParent(node, scale);

	return Node(true, x, y, node);
}

void QuadSpace::release(const Node node)
{
	const uint8_t scale = node.getLevel();

	nodes[node.getNode()] = 0xFF;
	if(scale != 0)
		validateParent(node.getNode(), scale);
}

void QuadSpace::validateParent(const unsigned short child, const uint8_t scale)
{
	const unsigned short node = getParent(child);
	const unsigned short children = getChildren(node);
	uint8_t newNode =
		nodes[children] |
		nodes[children + 1] |
		nodes[children + 2] |
		nodes[children + 3];

	if(!(
		nodes[children] &
		nodes[children + 1] &
		nodes[children + 2] &
		nodes[children + 3] &
		(1 << (scale - 1))))
		for(unsigned char i = scale; i-- > 0;)
			newNode &= ~(1 << i);

	if(nodes[node] != newNode)
	{
		nodes[node] = newNode;

		if(node)
			validateParent(node, scale - 1);
	}
}

unsigned short QuadSpace::getParent(const unsigned short node) const
{
	return (node - 1) >> 2;
}

unsigned short QuadSpace::getChildren(const unsigned short node) const
{
	return (node << 2) + 1;
}

QuadSpace::Node::Node(const bool valid, const uint8_t x, const uint8_t y, const uint16_t node)
:valid(valid), x(x), y(y), node(node) {}

uint8_t QuadSpace::Node::getX() const
{
	return x;
}

uint8_t QuadSpace::Node::getY() const
{
	return y;
}

uint16_t QuadSpace::Node::getNode() const
{
	return node;
}

uint8_t QuadSpace::Node::getLevel() const
{	
	return uint8_t(log(3 * (node + 1) + 1) / log(4) - 1);
}

bool QuadSpace::Node::getValid() const
{
	return valid;
}