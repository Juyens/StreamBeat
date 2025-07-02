#pragma once

#include "Widget.h"
#include "Interactive.h"
#include "FocusController.h"
#include "Console.h"
#include "List.h"

#include <vector>
#include <memory>
#include <type_traits>

namespace sb
{
	class Screen
	{
	public:
		explicit Screen(std::string id)
			: id_(std::move(id)) {}

		virtual void render()
		{
			for (const auto& widget : widgets_)
			{
				if (widget->isVisible())
					widget->render();
			}

			onRender();
		}

		virtual void onKeyPress(Key key) {}

		virtual void handleInput(const InputEvent& ev)
		{
			if (ev.specialKey.has_value()) 
			{
				Key key = *ev.specialKey;
				if (key == Key::Up || key == Key::Down || key == Key::Left || key == Key::Right) 
				{
					focusController_.handleNavigation(key);
				}

				onKeyPress(key);
			}

			if (auto* current = focusController_.getCurrent())
				current->handleInput(ev);
		}

		const std::string& getID() { return id_; }

		virtual void resetElements()
		{
			for (auto& widget : widgets_) 
			{
				widget->reset();
			}

			for (auto& interactive : interactives_) 
			{
				interactive->reset();
			}

			focusController_.focusFirst();

			onReset();
		}

		virtual void onRender() {};

		void setActive(bool active)
		{
			active_ = active;
		}

		bool isActive() const
		{
			return active_;
		}

		void suspend()
		{
			if (focusController_.getCurrent())
				focusController_.getCurrent()->deactivate();
		}

		void resume()
		{
			if (focusController_.getCurrent())
				focusController_.getCurrent()->activate();
		}

	protected:
		template<typename T, typename... Args>
		T* addElement(Args&&... args)
		{
			static_assert(std::is_base_of<Widget, T>::value, "T must inherit from Widget");

			auto element = std::make_unique<T>(std::forward<Args>(args)...);
			T* raw = element.get();

			if constexpr (std::is_base_of<Interactive, T>::value)
				interactives_.push_back(static_cast<Interactive*>(raw));

			widgets_.push_back(std::move(element));
			return raw;
		}

		virtual void onCreate() = 0;

		void initializeFocus()
		{
			focusController_.setInteractives(interactives_);
			focusController_.focusFirst();
		}

		virtual void onReset() {}

	protected:
		List<std::unique_ptr<Widget>> widgets_;
		List<Interactive*> interactives_;
		std::string id_;
		bool active_{ false };
		FocusController focusController_;
	};
}