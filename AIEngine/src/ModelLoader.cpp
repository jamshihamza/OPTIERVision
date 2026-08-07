#include "pch.h"

#include <optier/ModelLoader.h>

#include <array>
#include <iostream>
#include <filesystem>

namespace optier
{

    ModelLoader::ModelLoader(
        const std::string& modelPath)
        :
        m_modelPath(modelPath),
        m_environment(
            ORT_LOGGING_LEVEL_WARNING,
            "OPTIER")
    {
    }

    ModelLoader::~ModelLoader()
    {
        Unload();
    }

    bool ModelLoader::Load()
    {
        if (m_loaded)
        {
            return true;
        }

        try
        {
            m_sessionOptions.SetGraphOptimizationLevel(
                GraphOptimizationLevel::ORT_ENABLE_ALL);

            std::filesystem::path modelPath(m_modelPath);

            m_session =
                std::make_unique<Ort::Session>(
                    m_environment,
                    modelPath.c_str(),
                    m_sessionOptions);

            Ort::AllocatorWithDefaultOptions allocator;

            m_inputNames.clear();
            m_outputNames.clear();

            std::size_t inputCount =
                m_session->GetInputCount();

            for (std::size_t i = 0; i < inputCount; ++i)
            {
                auto name =
                    m_session->GetInputNameAllocated(
                        i,
                        allocator);

                m_inputNames.emplace_back(
                    name.get());
            }

            std::size_t outputCount =
                m_session->GetOutputCount();

            for (std::size_t i = 0; i < outputCount; ++i)
            {
                auto name =
                    m_session->GetOutputNameAllocated(
                        i,
                        allocator);

                m_outputNames.emplace_back(
                    name.get());
            }

            PrintModelInfo();

            m_loaded = true;

            return true;
        }
        catch (const Ort::Exception& e)
        {
            std::cout
                << "ONNX Runtime Error : "
                << e.what()
                << '\n';

            return false;
        }
    }

    void ModelLoader::Unload()
    {
        m_session.reset();

        m_inputNames.clear();

        m_outputNames.clear();

        m_loaded = false;
    }

    bool ModelLoader::IsLoaded() const
    {
        return m_loaded;
    }

    void ModelLoader::PrintModelInfo()
    {
        if (!m_session)
        {
            return;
        }

        std::cout << "\n========================================\n";
        std::cout << "MODEL INFORMATION\n";
        std::cout << "========================================\n";

        std::cout
            << "Inputs  : "
            << m_inputNames.size()
            << "\n";

        std::cout
            << "Outputs : "
            << m_outputNames.size()
            << "\n";

        for (const auto& name : m_inputNames)
        {
            std::cout
                << "Input : "
                << name
                << "\n";
        }

        for (const auto& name : m_outputNames)
        {
            std::cout
                << "Output : "
                << name
                << "\n";
        }

        std::cout << "========================================\n\n";
    }

    bool ModelLoader::RunInference(
        const std::vector<float>& inputTensor,
        std::vector<float>& outputTensor)
    {
        if (!m_loaded)
        {
            return false;
        }

        if (!m_session)
        {
            return false;
        }

        constexpr std::int64_t inputShape[] =
        {
            1,
            3,
            640,
            640
        };

        Ort::MemoryInfo memoryInfo =
            Ort::MemoryInfo::CreateCpu(
                OrtArenaAllocator,
                OrtMemTypeDefault);

        Ort::Value inputValue =
            Ort::Value::CreateTensor<float>(
                memoryInfo,
                const_cast<float*>(inputTensor.data()),
                inputTensor.size(),
                inputShape,
                4);

        std::vector<const char*> inputNames;

        for (const auto& name : m_inputNames)
        {
            inputNames.push_back(name.c_str());
        }

        std::vector<const char*> outputNames;

        for (const auto& name : m_outputNames)
        {
            outputNames.push_back(name.c_str());
        }

        auto outputs =
            m_session->Run(
                Ort::RunOptions{ nullptr },
                inputNames.data(),
                &inputValue,
                1,
                outputNames.data(),
                outputNames.size());

        if (outputs.empty())
        {
            return false;
        }

       /* std::cout << "\n========================================\n";
        std::cout << "ONNX OUTPUT INFORMATION\n";
        std::cout << "========================================\n";

        for (std::size_t i = 0; i < outputs.size(); ++i)
        {
            auto tensorInfo =
                outputs[i].GetTensorTypeAndShapeInfo();

            auto shape =
                tensorInfo.GetShape();

            std::cout
                << "Output "
                << i
                << "\n";

            std::cout
                << "Shape : ";

            for (auto dim : shape)
            {
                std::cout
                    << dim
                    << " ";
            }

            std::cout << "\n";

            std::cout
                << "Elements : "
                << tensorInfo.GetElementCount()
                << "\n\n";
        }*/

        auto tensorInfo =
            outputs[0].GetTensorTypeAndShapeInfo();

        auto shape =
            tensorInfo.GetShape();

        static bool printed = false;

        if (!printed)
        {
            std::cout
                << "\n========== ONNX OUTPUT ==========\n";

            std::cout
                << "Dimensions : ";

            for (auto dimension : shape)
            {
                std::cout
                    << dimension
                    << " ";
            }

            std::cout
                << "\n";

            std::cout
                << "Element Count : "
                << tensorInfo.GetElementCount()
                << "\n";

            printed = true;
        }

        float* data =
            outputs[0].GetTensorMutableData<float>();

        std::size_t count =
            tensorInfo.GetElementCount();

        outputTensor.assign(
            data,
            data + count);

        return true;
    }

} // namespace optier