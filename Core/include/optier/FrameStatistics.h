#pragma once
#include <chrono>
#include <string_view>
#include <vector>

namespace optier
{
	struct ProcessorTiming
	{
		std::string_view ProcessorName;

		std::chrono::microseconds Duration{ 0 };
	};

	struct FrameStatistics
	{
		 std::chrono::steady_clock::time_point CaptureTime;
		 std::chrono::steady_clock::time_point ProcessingStartTime;
		 std::chrono::steady_clock::time_point ProcessingEndTime;
		 std::chrono::microseconds ProcessingDuration{0};
		 std::vector<ProcessorTiming> ProcessorTimings;


		 void ClearProcessorTimings()
		 {
			 ProcessorTimings.clear();
		 }

		 void ReserveProcessorTimings(std::size_t processorCount)
		 {
			 ProcessorTimings.clear();
			 ProcessorTimings.reserve(processorCount);
		 }
	};


}