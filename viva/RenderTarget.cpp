#include "Proto.h"

namespace viva
{
	void RenderTarget::MoveToTop()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveToTop()\nThis render target is not on a render target list");

		if (it == parentContainer->begin())
			return;

		parentContainer->erase(it);
		parentContainer->insert(parentContainer->begin(), this);
	}

	void RenderTarget::MoveToBottom()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveToBottom()\nThis render target is not on a render target list");

		if (it == parentContainer->end() - 1)
			return;

		parentContainer->erase(it);
		parentContainer->push_back(this);
	}

	void RenderTarget::MoveUp()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveUp()\nThis render target is not on a render target list");

		if (it == parentContainer->begin())
			return;

		it--;
		auto temp = *it;
		*it = this;
		it++;
		*it = temp;
	}

	void RenderTarget::MoveDown()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::MoveDown()\nThis render target is not on a render target list");

		if (it == parentContainer->end() - 1)
			return;

		it++;
		auto temp = *it;
		*it = this;
		it--;
		*it = temp;
	}

	void RenderTarget::Insert(vector<RenderTarget*>* _parentContainer)
	{
		if(_parentContainer != nullptr)
			throw std::runtime_error("RenderTarget::Insert()\nThis render target has a container already");

		parentContainer = _parentContainer;
		parentContainer->push_back(this);
	}

	void RenderTarget::Remove()
	{
		auto it = parentContainer->begin();
		while (it != parentContainer->end() && *it != this)
			it++;

		if (it == parentContainer->end())
			throw std::runtime_error("RenderTarget::Remove()\nThis render target is not on a render target list");

		parentContainer->erase(it);
		parentContainer = nullptr;
	}
}