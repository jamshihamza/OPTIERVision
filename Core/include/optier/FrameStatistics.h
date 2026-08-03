#pragma once
#include <chrono>

namespace optier
{
	struct FrameStatistics
	{
		 std::chrono::steady_clock::time_point CaptureTime;
		 std::chrono::steady_clock::time_point ProcessingStartTime;
		 std::chrono::steady_clock::time_point ProcessingEndTime;
		 std::chrono::microseconds ProcessingDuration{0};

	};
}