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

        virtual const wstring& GetName() = 0;
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

        Routine(const std::function<int()>& activity, wstring name)
            : Activity(activity), Name(name)
        {
        }

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

        const wstring& GetName() override
        {
            return Name;
        }
    };

    class RoutineManager
    {
    private:
        vector<Routine*> routines;
        std::map<int, vector<std::function<void(int)>>> handlers;
    public:
        void _Activity()
        {
            double gameTime = time->GetGameTime();

            if (routines.size() == 0)
                return;

            //might be removed so backwards iteration
            for (int i = (int)routines.size() - 1; i >= 0; i--)
            {
                // destroy if remove flag is up
                if (routines.at(i) != nullptr && routines.at(i)->remove)
                {
                    delete routines.at(i);
                    routines.at(i) = nullptr;
                }

                //pop if last routine is empty
                if (routines.at(i) == nullptr && i == routines.size() - 1)
                {
                    routines.pop_back();
                    continue;
                }
                //if its empty but not last
                else if (routines.at(i) == nullptr)
                {
                    routines.at(i) = routines.back();
                    routines.pop_back();
                    continue;
                }

                int ret = 1;

                //if delay time has passed...
                if (gameTime - routines.at(i)->startTime > routines.at(i)->delay && !routines.at(i)->pause)
                    //...and it's time for next pulse then run
                    if (routines.at(i)->tick == 0 ||
                        (gameTime - routines.at(i)->lastPulse > routines.at(i)->tick))
                    {
                        ret = routines.at(i)->Activity();
                        routines.at(i)->lastPulse = gameTime;
                    }
                //if returned 0 or expired then remove
                if (ret == 0 || (routines.at(i)->lifeTime > 0 &&
                    gameTime - routines.at(i)->startTime > routines.at(i)->lifeTime))
                {
                    delete routines.at(i);
                    routines.at(i) = routines.back();
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
        IRoutine* AddRoutine(const std::function<int()>& func, const wstring& name, double delay, double lifeTime, double tick)
        {
            Routine* newRoutine = new Routine(func, name);
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
                if (routines.at(i) && routines.at(i)->Name == name)
                    return routines.at(i);

            throw Error(__FUNCTION__, "Routine not found");
        }

        void Trigger(int _event, int data)
        {
            auto it = handlers.find(_event);

            if (it == handlers.end())
                return;

            for (auto& handler : it->second)
                handler(data);
        }

        void AddHandler(int _event, const std::function<void(int)>& handler)
        {
            handlers[_event].push_back(handler);
        }

        // Remove all handlers for that event.
        void ClearHandlers(int _event)
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
            for (uint i = 0; i < routines.size(); i++)
                delete routines.at(i);

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
