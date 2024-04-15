#pragma once

#include <string>
#include <unordered_map>

class Service {
private:
	double min_val = 0;
	double max_val = 1;
public:
	Service();
	std::unordered_map<std::string, std::string> getConfigFile(std::string file_name);
	void run();
};
