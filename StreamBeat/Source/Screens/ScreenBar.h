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
		void initialize(const std::string& id);
		void render();
		void handleNavigation(const InputEvent& ev);
		void focus();
		void blur();
		bool hasFocus() const;
		const std::string& getTargetScreen() const;
		void clearTargetScreen();

	private:
		void onCreate();
		ScreenButton* findClosestHorizontal(Key key);

		ScreenButton* addElement(const std::string& key)
		{
			auto element = std::make_unique<ScreenButton>();
			ScreenButton* raw = element.get();
			raw->setTargetScreen(key);
			interactives_.push_back(std::move(element));
			screenMap_.insert(key, raw);
			return raw;
		}

	private:
		List<std::unique_ptr<ScreenButton>> interactives_;
		HashTable<std::string, ScreenButton*> screenMap_;
		ScreenButton* current_ = nullptr;
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