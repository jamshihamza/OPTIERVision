#include "pch.h"

#include <optier/Application.h>

int main()
{
    optier::Application application;

    if (!application.Initialize())
    {
        return -1;
    }

    application.Run();

    application.Shutdown();

    return 0;
}