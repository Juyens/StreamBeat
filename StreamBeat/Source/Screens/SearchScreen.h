#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"

#include <memory>

namespace sb
{
	class SearchScreen : public Screen
	{
	public:
		SearchScreen();

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
		
		Button* searchArtistBt_{ nullptr };
		Button* searchAlbumBt_{ nullptr };
		Button* searchSongBt_{ nullptr };
	};
}