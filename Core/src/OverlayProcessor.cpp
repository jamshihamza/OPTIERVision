#include "pch.h"
#include <iomanip>
#include <sstream>

#include <optier/OverlayProcessor.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace optier
{

    OverlayProcessor::OverlayProcessor(
        std::string applicationName)
        : m_applicationName(std::move(applicationName))
    {
    }

    bool OverlayProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        //
        // Validate frame
        //
        if (!frame.Image)
        {
            return false;
        }

        if (frame.Image->empty())
        {
            return false;
        }

        //
        // Draw overlays
        //
        DrawApplicationName(frame);

		DrawFrameNumber(frame);

		DrawFPS(frame);

        return true;
    }

    void OverlayProcessor::DrawApplicationName(
        VideoFrame& frame)


    {
        DrawText(
            frame,
            m_applicationName,
            20,
            40);
    }

    void OverlayProcessor::DrawFrameNumber(
        VideoFrame& frame)
    {
        DrawText(
            frame,
            "Frame : " +
            std::to_string(frame.FrameNumber),
            20,
            75,
            0.7,
            2);
    }

    void OverlayProcessor::DrawFPS(
        VideoFrame& frame)
    {
        //
        // Count rendered frames
        //
        ++m_fpsFrameCounter;

        auto now =
            std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<
            std::chrono::milliseconds>(
                now - m_fpsStart);

        //
        // Update FPS every second
        //
        if (elapsed.count() >= 1000)
        {
            m_currentFPS =
                static_cast<double>(m_fpsFrameCounter) /
                (elapsed.count() / 1000.0);

            m_fpsFrameCounter = 0;

            m_fpsStart = now;
        }

        //
        // Format FPS text
        //
        std::ostringstream stream;

        stream
            << std::fixed
            << std::setprecision(2)
            << m_currentFPS;

        DrawText(
            frame,
            "FPS : " + stream.str(),
            20,
            105,
            0.7,
            2);
    }


    void OverlayProcessor::DrawText(
        VideoFrame& frame,
        const std::string& text,
        int x,
        int y,
        double scale,
        int thickness)
    {
        cv::putText(
            *frame.Image,
            text,
            cv::Point(x, y),
            cv::FONT_HERSHEY_SIMPLEX,
            scale,
            cv::Scalar(0, 255, 0),
            thickness,
            cv::LINE_AA);
    }

    void OverlayProcessor::DrawRectangle(
        VideoFrame& frame,
        int x,
        int y,
        int width,
        int height,
        const cv::Scalar& color,
        int thickness)
    {
        cv::rectangle(
            *frame.Image,
            cv::Rect(x, y, width, height),
            color,
            thickness,
            cv::LINE_AA);
    }

    void OverlayProcessor::DrawLine(
        VideoFrame& frame,
        int x1,
        int y1,
        int x2,
        int y2,
        const cv::Scalar& color,
        int thickness)
    {
        cv::line(
            *frame.Image,
            cv::Point(x1, y1),
            cv::Point(x2, y2),
            color,
            thickness,
            cv::LINE_AA);
    }

    void OverlayProcessor::DrawCircle(
        VideoFrame& frame,
        int x,
        int y,
        int radius,
        const cv::Scalar& color,
        int thickness)
    {
        cv::circle(
            *frame.Image,
            cv::Point(x, y),
            radius,
            color,
            thickness,
            cv::LINE_AA);
    }

} // namespace optier