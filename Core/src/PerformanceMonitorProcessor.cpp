#include "pch.h"

#include <optier/PerformanceMonitorProcessor.h>

#include <iostream>
#include <iomanip>

namespace optier
{

    void PerformanceMonitorProcessor::ProcessFrame(
        const VideoFrame& frame)
    {
        //
        // Read processing time
        //
        auto processingTime =
            frame.Statistics.ProcessingDuration;

        //
        // Update statistics
        //
        ++m_frameCounter;

        m_totalTime += processingTime;

        if (processingTime < m_minTime)
        {
            m_minTime = processingTime;
        }

        if (processingTime > m_maxTime)
        {
            m_maxTime = processingTime;
        }

        //
        // Report every 30 frames
        //
        if (m_frameCounter < 30)
        {
            return;
        }

        auto now =
            std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now - m_lastReport);

        double fps = 0.0;

        if (elapsed.count() > 0)
        {
            fps =
                static_cast<double>(m_frameCounter) /
                (elapsed.count() / 1000.0);
        }

        auto averageTime =
            m_totalTime.count() /
            static_cast<long long>(m_frameCounter);

        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << " Performance Report\n";
        std::cout << "========================================\n";

        std::cout
            << "Frames        : "
            << m_frameCounter
            << "\n";

        std::cout
            << std::fixed
            << std::setprecision(2);

        std::cout
            << "FPS           : "
            << fps
            << "\n";

        std::cout
            << "Average Time  : "
            << averageTime
            << " us\n";

        std::cout
            << "Minimum Time  : "
            << m_minTime.count()
            << " us\n";

        std::cout
            << "Maximum Time  : "
            << m_maxTime.count()
            << " us\n";

        std::cout
            << "========================================\n\n";

        //
        // Reset statistics
        //
        m_frameCounter = 0;

        m_totalTime =
            std::chrono::microseconds{ 0 };

        m_minTime =
            std::chrono::microseconds::max();

        m_maxTime =
            std::chrono::microseconds{ 0 };

        m_lastReport =
            std::chrono::steady_clock::now();
    }

} // namespace optier