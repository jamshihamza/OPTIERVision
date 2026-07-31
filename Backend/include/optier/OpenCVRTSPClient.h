#pragma once

#include <memory>
#include <string>

#include <optier/IRTSPClient.h>
#include <optier/StreamState.h>

namespace optier
{

    class OpenCVRTSPClient final : public IRTSPClient
    {
    public:

        OpenCVRTSPClient();

        ~OpenCVRTSPClient() override;

    public:

        bool Connect(
            const std::string& url) override;

        void Disconnect() override;

        bool IsConnected() const override;

        bool ReadFrame(
            VideoFrame& frame) override;

    private:

        class Impl;

        std::unique_ptr<Impl> m_impl;
    };

}