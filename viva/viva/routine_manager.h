#pragma once

namespace viva
{
    struct IRoutine
    {
        // Remove from routine manager and delete.
        virtual void Destroy() = 0;

        // Stop executing.
        // Routine will still expire.
        virtual void Pause() = 0;

        // Start executing.
        // You don't have to call thi method at the beginning because
        // by default all new routines are executed.
        virtual void Resume() = 0;
    };

    class RoutineManager
    {
    private:
        struct Routine : public IRoutine
        {
            double tick;
            double lifeTime;
            double delay;
            double startTime;
            std::function<int()> Activity;
            wstring Name;
            double lastPulse;
            bool remove;
            bool pause;

            void Destroy() override
            {
                remove = true;
            }

            void Pause() override
            {
                pause = true;
            }

            void Resume() override
            {
                pause = false;
            }
        };

        vector<Routine*> routines;
        std::map<wstring, vector<std::function<void()>>> handlers;
    public:
        void _Activity();

        // Add a new routine.
        //func: code to execute by event (function pointer or closure)
        //      func must return an int. This is to make it easier to remove routines from inside. 
        //      If func returns 0, routine is destroyed.
        //delay: how long to wait before start running
        //lifeTime: destroy event after that time, 0 to never destroy
        //tick: run event once every tick seconds, 0 to run every frame
        IRoutine* AddRoutine(std::function<int()> func, wstring name = L"", double delay = 0, double lifeTime = 0, double tick = 0);

        // Find routine.
        // Note, this method performs linear search to find by name.
        // name: name of the routine
        IRoutine* FindRoutine(wstring name);

        void Trigger(wstring _event);

        void AddHandler(wstring _event, std::function<void()> handler);

        // Remove all handlers for that event.
        void ClearHandlers(wstring _event);

        // Remove all handlers.
        void ClearHandlers();

        // Remove all routines.
        // Don't call it from inside a routine.
        void ClearRoutines();

        void _Destroy();
    };
}