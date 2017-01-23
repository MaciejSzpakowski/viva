#include "viva.h"

namespace viva
{
    class Win32Time : public Time
    {
    private:
        double frequency;
        long long startTime;
        long long prevFrameTime;
    public:
        Win32Time()
        {
            LARGE_INTEGER li;
            if (!QueryPerformanceFrequency(&li))
                throw Error("QueryPerformanceFrequency()", "QueryPerformanceFrequency() failed");
            frequency = double(li.QuadPart);
            QueryPerformanceCounter(&li);
            startTime = li.QuadPart;
            prevFrameTime = startTime;
        }

        void _Destroy() override
        {
            delete this;
        }

        void _Activity() override
        {
            LARGE_INTEGER currentTime;
            long long frameTickCount;
            QueryPerformanceCounter(&currentTime);
            frameTickCount = currentTime.QuadPart - prevFrameTime;
            frameTime = double(frameTickCount) / frequency;
            prevFrameTime = currentTime.QuadPart;
            gameTime = double(currentTime.QuadPart - startTime) / frequency;
        }
    };
}
