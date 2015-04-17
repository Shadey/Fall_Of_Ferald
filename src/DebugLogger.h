#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H
#include <chrono>

class DebugLogger
{
	private:
		const bool optimized = false;
	public:
		DebugLogger(){}
		~DebugLogger(){}
		bool outputTiming(int time);
};
#endif // DEBUGLOGGER_H
