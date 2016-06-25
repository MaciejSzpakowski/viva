#pragma once

namespace viva
{
    class Win32Time : public Time
    {
    private:
        double frequency;
        long long startTime;
        long long prevFrameTime;
    public:
        Win32Time();

        void Destroy() override
        {
            delete this;
        }

        void Activity();
    };
}