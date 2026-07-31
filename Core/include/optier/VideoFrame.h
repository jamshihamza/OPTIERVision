#pragma once

#include <cstdint>
#include <chrono>


namespace optier
{

    struct VideoFrame
    {
       

        std::uint32_t Width = 0;

        std::uint32_t Height = 0;

        std::uint64_t FrameNumber = 0;

        std::chrono::steady_clock::time_point Timestamp;

		void* NativeFrame = nullptr;
    };

}