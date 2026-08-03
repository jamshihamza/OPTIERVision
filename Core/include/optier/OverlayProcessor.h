#pragma once

#include <string>

#include <opencv2/core/types.hpp>
#include <optier/IFrameProcessor.h>


namespace optier
{

class OverlayProcessor final : public IFrameProcessor
{
public:

    OverlayProcessor() = default;

    explicit OverlayProcessor(
        std::string applicationName);

    bool ProcessFrame(
        VideoFrame& frame) override;

private:

    //
    // High-level drawing routines
    //
    void DrawApplicationName(
        VideoFrame& frame);

    void DrawFrameNumber(
		VideoFrame& frame);

    void DrawFPS(
		VideoFrame& frame); 

    void DrawText(
        VideoFrame& frame,
        const std::string& text,
        int x,
        int y,
        double scale = 1.0,
        int thickness = 2);
    void DrawRectangle(
        VideoFrame& frame,
        int x,
        int y,
        int width,
        int height,
        const cv::Scalar& color,
        int thickness = 2);

    void DrawLine(
        VideoFrame& frame,
        int x1,
        int y1,
        int x2,
        int y2,
        const cv::Scalar& color,
        int thickness = 2);

    void DrawCircle(
        VideoFrame& frame,
        int x,
        int y,
        int radius,
        const cv::Scalar& color,
        int thickness = 2);

private:

    //
    // Overlay settings
    //
    std::string m_applicationName =
        "OPTIER Vision";

    std::uint64_t m_fpsFrameCounter = 0;

    double m_currentFPS = 0.0;

    std::chrono::steady_clock::time_point
        m_fpsStart =
        std::chrono::steady_clock::now();
};

} // namespace optier