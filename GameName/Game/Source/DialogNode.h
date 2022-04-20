#pragma once
#include <vector>
#include <string>

struct DialogNode
{
	// The dialog text
	std::string text;

	// The dialog ID of next nodes
	std::vector<size_t> nodes;

	// The dialog text for the options
	std::vector<std::string> options;
};