#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"
#include "TextBox.h"

namespace sb
{
	class LibraryScreen : public Screen
	{
	public:
		LibraryScreen();

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
		Button* listArtistBt_{ nullptr };
		Button* listAlbumsBt_{ nullptr };
		Button* listPlayListBt_{ nullptr };
		TextBox* texBox_{ nullptr };
		Button* addPlaylistBt_{ nullptr };
		Button* backLb_{ nullptr };
	};
}