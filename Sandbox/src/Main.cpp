#include "pch.h"
#include <iostream>

#include <optier/FrameQueue.h>
#include <optier/VideoFrame.h>

using namespace optier;

int main()
{
    FrameQueue queue(3);

    std::cout << "Capacity : " << queue.Capacity() << '\n';
    std::cout << "Empty    : " << std::boolalpha << queue.Empty() << '\n';

    VideoFrame frame1;
    VideoFrame frame2;
    VideoFrame frame3;
    VideoFrame frame4;

    std::cout << "\n=== Push Test ===\n";

    std::cout << "Push 1 : " << queue.Push(std::move(frame1)) << '\n';
    std::cout << "Push 2 : " << queue.Push(std::move(frame2)) << '\n';
    std::cout << "Push 3 : " << queue.Push(std::move(frame3)) << '\n';
    std::cout << "Push 4 : " << queue.Push(std::move(frame4)) << '\n';

    std::cout << "\nSize : " << queue.Size() << '\n';
    std::cout << "Full : " << queue.Full() << '\n';

    std::cout << "\n=== Pop Test ===\n";

    VideoFrame output;

    std::cout << "Pop 1 : " << queue.Pop(output) << '\n';
    std::cout << "Pop 2 : " << queue.Pop(output) << '\n';
    std::cout << "Pop 3 : " << queue.Pop(output) << '\n';
    std::cout << "Pop 4 : " << queue.Pop(output) << '\n';

    std::cout << "\nSize  : " << queue.Size() << '\n';
    std::cout << "Empty : " << queue.Empty() << '\n';

    return 0;
}