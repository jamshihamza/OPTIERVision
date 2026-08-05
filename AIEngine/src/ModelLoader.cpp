#include "pch.h"

#include <filesystem>
#include <iostream>
#include <optier/ModelLoader.h>

namespace optier
{

    ModelLoader::ModelLoader(
        const std::string& modelPath)
        : m_modelPath(modelPath)
    {
    }

    ModelLoader::~ModelLoader()
    {
        Unload();
    }

    bool ModelLoader::CreateEnvironment()
    {
        try
        {
            m_environment =
                std::make_unique<Ort::Env>(
                    ORT_LOGGING_LEVEL_WARNING,
                    "OPTIER");
        }
        catch (...)
        {
            return false;
        }

        return true;
    }

    bool ModelLoader::CreateSessionOptions()
    {
        if (!m_environment)
        {
            return false;
        }

        m_sessionOptions =
            std::make_unique<Ort::SessionOptions>();

        m_sessionOptions->SetGraphOptimizationLevel(
            GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

        m_sessionOptions->SetIntraOpNumThreads(1);

        return true;
    }

    bool ModelLoader::Load()
    {
        if (m_loaded)
        {
            return true;
        }

        if (!CreateEnvironment())
        {
            return false;
        }

        if (!CreateSessionOptions())
        {
            return false;
        }

        try
        {
            const std::filesystem::path modelPath(
                m_modelPath);

            m_session =
                std::make_unique<Ort::Session>(
                    *m_environment,
                    modelPath.c_str(),
                    *m_sessionOptions);
        }
        catch (const Ort::Exception&)
        {
            return false;
        }

        if (!ReadModelMetadata())
        {
            return false;
        }

        m_loaded = true;

        return true;
    }

    void ModelLoader::Unload()
    {
        m_session.reset();

        m_sessionOptions.reset();

        m_environment.reset();

        m_loaded = false;

        m_inputNames.clear();
        m_outputNames.clear();

        m_inputShape.clear();
        m_outputShape.clear();
    }

    bool ModelLoader::IsLoaded() const
    {
        return m_loaded;
    }

    const std::string& ModelLoader::ModelPath() const
    {
        return m_modelPath;
    }

    Ort::Session* ModelLoader::Session()
    {
        return m_session.get();
    }

    const std::vector<std::string>&
        ModelLoader::InputNames() const
    {
        return m_inputNames;
    }

    const std::vector<std::string>&
        ModelLoader::OutputNames() const
    {
        return m_outputNames;
    }

    const std::vector<int64_t>&
        ModelLoader::InputShape() const
    {
        return m_inputShape;
    }

    const std::vector<int64_t>&
        ModelLoader::OutputShape() const
    {
        return m_outputShape;
    }

    void ModelLoader::PrintModelInfo() const
    {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << " ONNX Model Information\n";
        std::cout << "========================================\n";

        std::cout
            << "Model : "
            << m_modelPath
            << "\n\n";

        std::cout
            << "Inputs : "
            << m_inputNames.size()
            << "\n";

        std::cout
            << "Outputs: "
            << m_outputNames.size()
            << "\n\n";

        if (!m_inputNames.empty())
        {
            std::cout
                << "Input Name : "
                << m_inputNames[0]
                << "\n";

            std::cout
                << "Input Shape: ";

            for (auto value : m_inputShape)
            {
                std::cout << value << " ";
            }

            std::cout << "\n\n";
        }

        if (!m_outputNames.empty())
        {
            std::cout
                << "Output Name: "
                << m_outputNames[0]
                << "\n";

            std::cout
                << "Output Shape: ";

            for (auto value : m_outputShape)
            {
                std::cout << value << " ";
            }

            std::cout << "\n";
        }

        std::cout
            << "========================================\n";
    }

    bool ModelLoader::ReadModelMetadata()
    {
        if (!m_session)
        {
            return false;
        }

        Ort::AllocatorWithDefaultOptions allocator;

        m_inputNames.clear();
        m_outputNames.clear();

        m_inputShape.clear();
        m_outputShape.clear();

        //
        // Input metadata
        //
        const std::size_t inputCount =
            m_session->GetInputCount();

        if (inputCount > 0)
        {
            auto inputName =
                m_session->GetInputNameAllocated(
                    0,
                    allocator);

            m_inputNames.emplace_back(
                inputName.get());

            auto inputTypeInfo =
                m_session->GetInputTypeInfo(0);

            auto tensorInfo =
                inputTypeInfo.GetTensorTypeAndShapeInfo();

            m_inputShape =
                tensorInfo.GetShape();
        }

        //
        // Output metadata
        //
        const std::size_t outputCount =
            m_session->GetOutputCount();

        if (outputCount > 0)
        {
            auto outputName =
                m_session->GetOutputNameAllocated(
                    0,
                    allocator);

            m_outputNames.emplace_back(
                outputName.get());

            auto outputTypeInfo =
                m_session->GetOutputTypeInfo(0);

            auto tensorInfo =
                outputTypeInfo.GetTensorTypeAndShapeInfo();

            m_outputShape =
                tensorInfo.GetShape();
        }

        return true;
    }

} // namespace optier