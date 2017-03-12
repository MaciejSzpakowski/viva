#include "viva.h"

namespace viva
{
    struct Action
    {
        vector<Rect> uvTable;
        wstring name;
        double speed;

        Action(const vector<Rect>& _uvTable, const wstring& _name, double _speed)
            : name(_name), uvTable(_uvTable), speed(_speed)
        {
        }
    };

    class Animation : public Node, public Drawable
    {
    protected:
        vector<Action> actions;
        vector<std::function<void(int)>> onFrameChangedhandlers;
        vector<std::function<void(int)>> onActionLoopedHandlers;
        Action* currentAction;
        Sprite* sprite;

        // progress of the animation
        double indicator;
        
        // currently displayed frame
        int currentFrame;
    public:
        Animation()
            : indicator(0), currentFrame(0), currentAction(nullptr)
        {
        }

        // Get transform of the object.
        Transform* T() override
        {
            return sprite->T();
        }

        // Get transform of the object.
        Transform* GetTransform() override
        {
            return sprite->T();
        }

        void _Play()
        {
            if (currentAction != nullptr && currentAction->speed != 0)
            {
                indicator += currentAction->speed * time->GetFrameTime();
                if (indicator >= 1)
                {
                    indicator = 0;
                    NextFrame();
                }
                else if (indicator < 0)
                {
                    indicator = 1;
                    PreviousFrame();
                }
            }

            sprite->SetUV(currentAction->uvTable.at(currentFrame));
        }

        int GetFrameCount() const 
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            return currentAction->uvTable.size();
        }

        // Advances animation to the next frame.
        // If the current frame is the last then this method sets current frame to 0.
        void NextFrame()
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            currentFrame++;

            for (int i = 0; i < onFrameChangedhandlers.size(); i++)
                onFrameChangedhandlers.at(i)(currentFrame);

            if (currentFrame >= currentAction->uvTable.size())
            {
                currentFrame = 0;

                for (int i = 0; i < onActionLoopedHandlers.size(); i++)
                    onActionLoopedHandlers.at(i)(currentFrame);
            }
        }

        // Goes back in the animation.
        // If the current frame is the first then this method sets current frame to the last one.
        void PreviousFrame()
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            currentFrame--;

            for (int i = 0; i < onFrameChangedhandlers.size(); i++)
                onFrameChangedhandlers.at(i)(currentFrame);

            if (currentFrame < 0)
            {
                currentFrame = currentAction->uvTable.size() - 1;

                for (int i = 0; i < onActionLoopedHandlers.size(); i++)
                    onActionLoopedHandlers.at(i)(currentFrame);
            }
        }

        double GetSpeed() const 
        { 
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            return currentAction->speed;
        }

        void SetSpeed(double speed) 
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            currentAction->speed = speed;
        }

        void SetSpeed(double speed, const wstring& action)
        {
            for(auto& a : actions)
                if (a.name == action)
                {
                    a.speed = speed;
                    return;
                }

            throw new Error(__FUNCTION__, "Name not found");
        }

        int GetFrame() const 
        { 
            return currentFrame; 
        }

        void SetFrame(int _currentFrame) 
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            currentFrame = _currentFrame;

            if (currentFrame < 0)
                currentFrame = 0;
            else if (currentFrame >= currentAction->uvTable.size())
                currentFrame = currentAction->uvTable.size() - 1;
        }

        void SetAction(const wstring& name)
        {
            auto it = std::find_if(actions.begin(), actions.end(), [&](Action& e) { return e.name == name; });

            if (it == actions.end())
                throw Error(__FUNCTION__, "Name not found");

            currentAction = it._Ptr;
        }

        const wstring& GetAction() const
        {
            if (currentAction == nullptr)
                throw Error(__FUNCTION__, "Action not set");

            return currentAction->name;
        }

        void AddAction(const wstring& name, double speed, int columns, int rows, int first, int last)
        {
            vector<Rect> uvTable;

            float width = 1.0f / columns;
            float height = 1.0f / rows;

            try
            {
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < columns; j++)
                    {
                        if (columns * i + j >= first)
                            uvTable.push_back(Rect(width*j, height*i, width*(j + 1), height*(i + 1)));
                        if (columns * i + j >= last)
                            throw std::overflow_error(""); // exit double for loop
                    }
            }
            catch (std::overflow_error& exit)
            {
            }

            actions.push_back(Action(uvTable, name, speed));
        }

        void AddAction(const wstring& name, double speed, const vector<Rect>& uvTable)
        {
            actions.push_back(Action(uvTable, name, speed));
        }

        void AddOnFrameChangeHandler(const std::function<void(int)>& fun)
        {
            onFrameChangedhandlers.push_back(fun);
        }

        void AddOnActionLoopedHandler(const std::function<void(int)>& fun)
        {
            onActionLoopedHandlers.push_back(fun);
        }

        void ClearOnFrameChangeHandlers()
        {
            onFrameChangedhandlers.clear();
        }

        void ClearAddOnActionLoopedHandlers()
        {
            onActionLoopedHandlers.clear();
        }

        void _Draw() override
        {
        }

        Surface* GetSurface() const override
        {
            return sprite->GetSurface();
        }

        bool IsVisible() const override
        {
            return sprite->IsVisible();
        }

        Drawable* SetVisible(bool val) override
        {
            sprite->SetVisible(val);
            return this;
        }

        void _SetSurface(Surface* surface) override
        {
            sprite->_SetSurface(surface);
        }

        void _SetIndex(uint i) override
        {
            sprite->_SetIndex(i);
        }

        int _GetIndex() const override
        {
            return sprite->_GetIndex();
        }

        void Destroy() override
        {
            sprite->Destroy();
            delete this;
        }

        Node* GetNode() override
        {
            return this;
        }
    };
}