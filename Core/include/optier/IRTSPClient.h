#pragma once

#include <string>

namespace optier
{

    struct VideoFrame;

    class IRTSPClient
    {
    public:

        virtual ~IRTSPClient() = default;

    public:

        virtual bool Connect(
            const std::string& url) = 0;

        virtual void Disconnect() = 0;

        virtual bool IsConnected() const = 0;

        virtual bool ReadFrame(
            VideoFrame& frame) = 0;
    };

}