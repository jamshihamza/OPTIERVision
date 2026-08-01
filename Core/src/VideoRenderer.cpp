#include "pch.h"

#include <optier/VideoRenderer.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

namespace optier
{

    VideoRenderer::VideoRenderer(
        std::string windowName)
        : m_windowName(std::move(windowName))
    {
        cv::namedWindow(
            m_windowName,
            cv::WINDOW_NORMAL);
    }

    VideoRenderer::~VideoRenderer()
    {
        cv::destroyWindow(
            m_windowName);
    }

    bool VideoRenderer::ProcessFrame(
        VideoFrame& frame)
    {
        if (!frame.Image)
        {
            return false;
        }

        if (frame.Image->empty())
        {
            return false;
        }

        std::lock_guard<std::mutex> lock(m_mutex);

        //
        // Keep our own copy.
        // Never render directly from the shared frame.
        //
        m_latestFrame = frame.Image->clone();

        return true;
    }

    void VideoRenderer::Display()
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_latestFrame.empty())
        {
            return;
        }

        cv::imshow(
            m_windowName,
            m_latestFrame);

        cv::waitKey(1);
    }

}