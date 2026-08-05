#include "pch.h"

#include <optier/YOLODetector.h>

namespace optier
{

    YOLODetector::YOLODetector(
        const std::string& modelPath)
        : m_modelLoader(modelPath)
    {
    }

    bool YOLODetector::Initialize()
    {
        return m_modelLoader.Load();
    }

    void YOLODetector::Shutdown()
    {
        m_modelLoader.Unload();
    }

    bool YOLODetector::Detect(
        VideoFrame& frame)
    {
        //
        // Validate image
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
        // Preprocess image
        //
        std::vector<float> inputTensor;

        if (!m_preprocessor.Preprocess(
            *frame.Image,
            inputTensor))
        {
            return false;
        }

        //
        // Run inference
        //
        std::vector<float> outputTensor;

        if (!m_modelLoader.RunInference(
            inputTensor,
            outputTensor))
        {
            return false;
        }

        //
        // Decode detections
        //
        if (!m_postProcessor.Process(
            outputTensor,
            frame.Detections))
        {
            return false;
        }

        return true;
    }

} // namespace optier