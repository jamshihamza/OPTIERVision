#pragma once

#include <chrono>
#include <string>

#include <opencv2/core/types.hpp>

#include <optier/BoundingBox.h>
#include <optier/DetectionMapper.h>
#include <optier/IFrameProcessor.h>

namespace optier
{

    class OverlayProcessor final
        : public IFrameProcessor
    {
    public:

        OverlayProcessor() = default;

        bool ProcessFrame(
            VideoFrame& frame) override;

    private:

        //
        // Overlay Components
        //
        void DrawApplicationName(
            VideoFrame& frame);

        void DrawFrameNumber(
            VideoFrame& frame);

        void DrawFPS(
            VideoFrame& frame);

        //
        // Drawing Primitives
        //
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

        //
        // High-Level Rendering
        //
        void DrawBoundingBox(
            VideoFrame& frame,
            const BoundingBox& box);

        void DrawBoundingBoxes(
            VideoFrame& frame,
            const std::vector<BoundingBox>& boxes);

    private:

        //
        // FPS Statistics
        //
        std::chrono::steady_clock::time_point
            m_fpsStart =
            std::chrono::steady_clock::now();

        std::uint64_t
            m_fpsFrameCounter = 0;

        double
            m_currentFPS = 0.0;
    };

} // namespace optier