#pragma once

#include <memory>

#include <opencv2/core/mat.hpp>

#include <optier/IObjectDetector.h>
#include <optier/ImagePreprocessor.h>
#include <optier/ModelLoader.h>
#include <optier/DetectionPostProcessor.h>

namespace optier
{

    class YOLODetector final
        : public IObjectDetector
    {
    public:

        explicit YOLODetector(
            const std::string& modelPath);

        ~YOLODetector() override = default;

        bool Initialize() override;

        void Shutdown() override;

        bool Detect(
            VideoFrame& frame) override;

    private:

        ImagePreprocessor m_preprocessor;

        ModelLoader m_modelLoader;

        DetectionPostProcessor m_postProcessor;
    };

} // namespace optier