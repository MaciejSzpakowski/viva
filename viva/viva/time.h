#pragma once

namespace viva
{
    class Time
    {
    protected:
        double gameTime;
        double frameTime;
    public:
        Time() :
            gameTime(0), 
            frameTime(0) {}

        // Time elapsed in seconds since the beginning of the game.
        double GetGameTime()
        {
            return gameTime;
        }

        // Time elapsed since last frame.
        double GetFrameTime() const 
        { 
            return frameTime; 
        }

        // Frames per second.
        double GetFps() const 
        { 
            return 1 / frameTime; 
        }

        virtual void Destroy() = 0;
    };
}