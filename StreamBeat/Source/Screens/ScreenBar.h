#pragma once

#include "UI.h"
#include "Console.h"
#include "ScreenNames.h"
#include "Screen.h"
#include "List.h"
#include "HashTable.h"

#include <memory>
#include <string>

namespace sb
{
	class ScreenButton : public Button 
	{
	public:
		ScreenButton() = default;

		void setTargetScreen(const std::string& screenId) { screenId_ = screenId; }
		const std::string& getTargetScreen() const { return screenId_; }

	private:
		std::string screenId_{ ScreenNames::None };
	};

	class ScreenBar
	{
	public:
		void initialize(const std::string id);
		void render();
		void handleNavigation(const InputEvent& ev);
		void focus();
		void blur();
		bool hasFocus() const;
		const std::string& getTargetScreen() const;
		void clearTargetScreen();

	private:
		void onCreate();
		Interactive* findClosestHorizontal(Key key);

		template<typename T, typename... Args>
		T* addElement(const std::string& key, Args&&... args)
		{
			static_assert(std::is_base_of<Interactive, T>::value, "T must inherit from Widget");

			auto element = std::make_unique<T>(std::forward<Args>(args)...);
			T* raw = element.get();

			interactives_.push_back(std::move(element));
			screenMap_.insert(key, static_cast<Interactive*>(raw));
			return raw;
		}

	private:
		List<std::unique_ptr<ScreenButton>> interactives_;
		HashTable<std::string, Interactive*> screenMap_;
		Interactive* current_ = nullptr;
		bool hasFocus_{ false };
		std::string targetScreen_ = ScreenNames::None;
		ScreenButton* music_{ nullptr };
		ScreenButton* main_{ nullptr };
		ScreenButton* explore_{ nullptr };
		ScreenButton* profile_{ nullptr };
		ScreenButton* library_{ nullptr };
		ScreenButton* history_{ nullptr };
		ScreenButton* search_{ nullptr };
	};
}