#include <viva/viva.h>

namespace viva
{
    IRoutine* RoutineManager::AddRoutine
    (std::function<int()> func, wstring name, double delay, double lifeTime, double tick)
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

    IRoutine* RoutineManager::FindRoutine(wstring name)
    {
        for (int i = 0; i<routines.size(); i++)
            if (routines[i] && routines[i]->Name == name)
                return routines[i];

        throw Error("RoutineManager::RemoveRoutine()", "Routine not found");
    }

    void RoutineManager::_Activity()
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

    void RoutineManager::AddHandler(wstring _event, std::function<void()> handler)
    {
        handlers[_event].push_back(handler);
    }

    void RoutineManager::Trigger(wstring _event)
    {
        auto it = handlers.find(_event);

        if (it == handlers.end())
            return;

        for (auto& handler : it->second)
            handler();
    }

    void RoutineManager::ClearHandlers(wstring _event)
    {
        auto it = handlers.find(_event);

        if (it == handlers.end())
            return;

        it->second.clear();
    }

    void RoutineManager::ClearHandlers()
    {
        handlers.clear();
    }

    void RoutineManager::ClearRoutines()
    {
        for (int i = 0; i < routines.size(); i++)
            delete routines[i];

        routines.clear();
    }

    void RoutineManager::_Destroy()
    {
        ClearRoutines();
        ClearHandlers();

        delete this;
    }
}