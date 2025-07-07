#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"
#include "TableView.h"
#include "Song.h"

namespace sb
{
	class HistoryScreen : public Screen
	{
	public:
		HistoryScreen();
		void update() override;

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
		TableView<Song>* tableView_{ nullptr };
		uint prevHistorySize_{ 0 };
		void refreshHistory();
	};
}