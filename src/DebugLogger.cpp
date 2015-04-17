#include "DebugLogger.h"
#include <fstream>
#include <string>

bool DebugLogger::outputTiming(int time)
{
	std::fstream file;
	
	if(optimized)
		file.open("debug/postOptimisations.txt");
	else
		file.open("debug/preOptimisations.txt");

	if(file.good())
	{
		std::string timeStr = std::to_string(time);
		timeStr += "\n";
		file.seekg(0, std::ios::end);
		//file << std::to_string(time);
		file << timeStr;
		file.close();
		return true;
	}
		else return false;
}
