#include "viva.h"

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

    class RoutineManager
    {
    private:
        vector<Routine*> routines;
        std::map<wstring, vector<std::function<void()>>> handlers;
    public:
        void _Activity()
        {
            double gameTime = time->GetGameTime();

            //might be removed so backwards iteration
            for (int i = (int)routines.size() - 1; i >= 0; i--)
            {
                // destroy if remove flag is up
                if (routines[i] != nullptr && routines[i]->remove)
                {
                    delete routines[i];
                    routines[i] = nullptr;
                }

                //pop if last routine is empty
                if (routines[i] == nullptr && i == routines.size() - 1)
                {
                    routines.pop_back();
                    continue;
                }
                //if its empty but not last
                else if (routines[i] == nullptr)
                {
                    routines[i] = routines.back();
                    routines.pop_back();
                    continue;
                }

                int ret = 1;

                //if delay time has passed...
                if (gameTime - routines[i]->startTime > routines[i]->delay && !routines[i]->pause)
                    //...and it's time for next pulse then run
                    if (routines[i]->tick == 0 ||
                        (gameTime - routines[i]->lastPulse > routines[i]->tick))
                    {
                        ret = routines[i]->Activity();
                        routines[i]->lastPulse = gameTime;
                    }
                //if returned 0 or expired then remove
                if (ret == 0 || (routines[i]->lifeTime > 0 &&
                    gameTime - routines[i]->startTime > routines[i]->lifeTime))
                {
                    delete routines[i];
                    routines[i] = routines.back();
                    routines.pop_back();
                }
            }
        }

        // Add a new routine.
        //func: code to execute by event (function pointer or closure)
        //      func must return an int. This is to make it easier to remove routines from inside. 
        //      If func returns 0, routine is destroyed.
        //delay: how long to wait before start running
        //lifeTime: destroy event after that time, 0 to never destroy
        //tick: run event once every tick seconds, 0 to run every frame
        IRoutine* AddRoutine(std::function<int()> func, wstring name, double delay, double lifeTime, double tick)
        {
            Routine* newRoutine = new Routine;
            newRoutine->tick = tick;
            newRoutine->lifeTime = lifeTime;
            newRoutine->delay = delay;
            newRoutine->startTime = time->GetGameTime();
            newRoutine->Activity = func;
            newRoutine->Name = name;
            newRoutine->lastPulse = 0;
            newRoutine->remove = false;
            newRoutine->pause = false;

            routines.push_back(newRoutine);
            return newRoutine;
        }

        // Find routine.
        // Note, this method performs linear search to find by name.
        // name: name of the routine
        IRoutine* FindRoutine(wstring name)
        {
            for (int i = 0; i<routines.size(); i++)
                if (routines[i] && routines[i]->Name == name)
                    return routines[i];

            throw Error("RoutineManager::RemoveRoutine()", "Routine not found");
        }

        void Trigger(wstring _event)
        {
            auto it = handlers.find(_event);

            if (it == handlers.end())
                return;

            for (auto& handler : it->second)
                handler();
        }

        void AddHandler(wstring _event, std::function<void()> handler)
        {
            handlers[_event].push_back(handler);
        }

        // Remove all handlers for that event.
        void ClearHandlers(wstring _event)
        {
            auto it = handlers.find(_event);

            if (it == handlers.end())
                return;

            it->second.clear();
        }

        // Remove all handlers.
        void ClearHandlers()
        {
            handlers.clear();
        }

        // Remove all routines.
        // Don't call it from inside a routine.
        void ClearRoutines()
        {
            for (int i = 0; i < routines.size(); i++)
                delete routines[i];

            routines.clear();
        }

        void _Destroy()
        {
            ClearRoutines();
            ClearHandlers();

            delete this;
        }
    };
}
