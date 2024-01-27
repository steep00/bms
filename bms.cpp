/*
    Copyright (c) 2024, steep00
    All rights reserved.

    This source code is licensed under the BSD-style license found in the
    LICENSE file in the root directory of this source tree.
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

struct Bms {
	std::map<std::string, std::string> header;
};

std::istream& operator>>(std::istream& is, Bms& bms)
{
	for (std::string line; std::getline(is, line); ) {

		std::smatch matches;

		static std::regex pat {"^#([A-Z0-9]+) (.+)"};

		if (std::regex_search(line, matches, pat))
			bms.header[matches[1]] = matches[2];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const Bms& bms)
{
	for (auto& [key, value] : bms.header)
		os << std::setw(16) << std::left << key << value << '\n';

	return os;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "arguments expected\n";
		return 1;
	}

	std::filesystem::path p {argv[1]};

	std::ifstream f {p};

	if (!f) {
		std::cerr << "couldn't open " << p << '\n';
		return 1;
	}

	Bms bms;

	f >> bms;

	std::cout << bms;
}
