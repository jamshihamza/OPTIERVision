#pragma once

#include <memory>
#include <string>
#include <vector>

#include <onnxruntime_cxx_api.h>

namespace optier
{

    class ModelLoader
    {
    public:

        explicit ModelLoader(
            const std::string& modelPath);

        ~ModelLoader();

        bool Load();

        void Unload();

        bool IsLoaded() const;

        bool RunInference(
            const std::vector<float>& inputTensor,
            std::vector<float>& outputTensor);

    private:

        void PrintModelInfo();

    private:

        std::string m_modelPath;

        bool m_loaded = false;

        Ort::Env m_environment;

        Ort::SessionOptions m_sessionOptions;

        std::unique_ptr<Ort::Session> m_session;

        std::vector<std::string> m_inputNames;

        std::vector<std::string> m_outputNames;
    };

} // namespace optier