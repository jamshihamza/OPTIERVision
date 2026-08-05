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

        ModelLoader(
            const ModelLoader&) = delete;

        ModelLoader& operator=(
            const ModelLoader&) = delete;

    public:

        bool Load();

        void Unload();

        bool IsLoaded() const;

        const std::string& ModelPath() const;

        Ort::Session* Session();

        const std::vector<std::string>& InputNames() const;

        const std::vector<std::string>& OutputNames() const;

        const std::vector<int64_t>& InputShape() const;

        const std::vector<int64_t>& OutputShape() const;

        void PrintModelInfo() const;

    private:

        bool CreateEnvironment();

        bool CreateSessionOptions();

        bool ReadModelMetadata();

    private:

        //
        // Model
        //
        std::string m_modelPath;

        bool m_loaded = false;

        //
        // ONNX Runtime
        //
        std::unique_ptr<Ort::Env> m_environment;

        std::unique_ptr<Ort::SessionOptions> m_sessionOptions;

        std::unique_ptr<Ort::Session> m_session;

        //
        // Model Metadata
        //
        std::vector<std::string> m_inputNames;

        std::vector<std::string> m_outputNames;

        std::vector<int64_t> m_inputShape;

        std::vector<int64_t> m_outputShape;
    };

} // namespace optier