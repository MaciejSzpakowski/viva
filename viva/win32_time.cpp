#include <viva/viva.h>
#include <viva/win32/win32.h>

namespace viva
{
    Win32Time::Win32Time()
    {
        LARGE_INTEGER li;
        if (!QueryPerformanceFrequency(&li))
            throw Error("QueryPerformanceFrequency()","QueryPerformanceFrequency() failed");
        frequency = double(li.QuadPart);
        QueryPerformanceCounter(&li);
        startTime = li.QuadPart;
        prevFrameTime = startTime;
    }

    void Win32Time::Activity()
    {
        LARGE_INTEGER currentTime;
        long long frameTickCount;
        QueryPerformanceCounter(&currentTime);
        frameTickCount = currentTime.QuadPart - prevFrameTime;
        frameTime = double(frameTickCount) / frequency;
        prevFrameTime = currentTime.QuadPart;
        gameTime = double(currentTime.QuadPart - startTime) / frequency;
    }
}