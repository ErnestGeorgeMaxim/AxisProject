#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>

int main()
{
	std::vector<std::string> listOfLines;

	std::regex lineFormat{ R"(\d\d/\d\d \d\d:\d\d:\d\d (INFO|TRACE|WARNING|EVENT|PROTERR)\s*:\.+(\w|_)+: .*)" };

	std::string line;
	for (std::ifstream in{ "server.log" }; !in.eof();)
	{
		std::getline(in, line);

		if (std::regex_match(line, lineFormat))
		{
			listOfLines.push_back(std::move(line));
		}
	}

	std::cout << "Size of vector: " << listOfLines.size() << '\n';  // 353 - 69 = 284?

	return 0;
}