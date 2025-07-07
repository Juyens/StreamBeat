#pragma once

#include "SubScreen.h"
#include "Song.h"
#include "UI.h"
#include "Console.h"
#include "ScreenManager.h"
#include "Label.h"
#include "Color.h"

#include <memory>
#include <sstream>

namespace sb
{
	class SubInfoScreen : public SubScreen
	{
	public:
		explicit SubInfoScreen(std::shared_ptr<Song> song)
			: SubScreen(), song_(std::move(song))
		{
			onCreate();
		}

	protected:
		void onCreate() override
		{
			using namespace Color;

			const auto consoleSize = Console::getViewportSize();
			int y = 5;

			// Titulo general
			titleLb_ = addElement<Label>();
			titleLb_->setText("[ StreamBeat - Cancion >> " + song_->getName() + " ]");
			titleLb_->centerX(consoleSize.x());
			titleLb_->setY(1);

			// Informacion
			addLabelPair(">> Nombre <<", song_->getName(), y, Background::LightYellow, consoleSize.x()); y += 4;

			std::stringstream durationStream;
			durationStream << song_->getDuration() / 60 << "m " << song_->getDuration() % 60 << "s";
			addLabelPair(">> Duracion <<", durationStream.str(), y, Background::LightCyan, consoleSize.x()); y += 4;

			addLabelPair(">> Reproducciones <<", std::to_string(song_->getReproductions()), y, Background::LightGreen, consoleSize.x()); y += 4;

			// Generos
			addLabelPair(">> Generos <<", "", y, Background::LightMagenta, consoleSize.x()); y += 1;
			for (uint i = 0; i < song_->getGenres().size(); ++i)
			{
				addCenteredValue(song_->getGenres()[i], y++, consoleSize.x());
			}
			y += 3;

			// Autores
			addLabelPair(">> Autores <<", "", y, Background::LightRed, consoleSize.x()); y += 1;
			for (uint i = 0; i < song_->getCredits().getAuthors().size(); ++i)
			{
				addCenteredValue(song_->getCredits().getAuthors()[i], y++, consoleSize.x());
			}
			y += 3;

			// Discografia
			addLabelPair(">> Discografia <<", song_->getCredits().getDiscography(), y, Background::LightBlue, consoleSize.x());
		}

		void onKeyPress(Key key) override
		{
			if (auto* focused = focusController_.getCurrent())
			{
				if (focused->wantsExclusiveInput())
					return;
			}

			if (key == Key::Escape)
			{
				ScreenManager::instance().goBack();
			}
		}

	private:
		std::shared_ptr<Song> song_;

		void addLabelPair(const std::string& title, const std::string& value, int y, WORD bg, int consoleWidth)
		{
			auto* titleLabel = addElement<Label>();
			titleLabel->setText(title);
			titleLabel->setY(y);
			titleLabel->setTextForeground(Color::Foreground::Black);
			titleLabel->setTextBackground(bg);
			titleLabel->centerX(consoleWidth);

			if (!value.empty())
			{
				auto* valueLabel = addElement<Label>();
				valueLabel->setText(value);
				valueLabel->setY(y + 1);
				valueLabel->setTextForeground(Color::Foreground::White);
				valueLabel->centerX(consoleWidth);
			}
		}

		void addCenteredValue(const std::string& text, int y, int consoleWidth)
		{
			auto* label = addElement<Label>();
			label->setText(text);
			label->setY(y);
			label->setTextForeground(Color::Foreground::White);
			label->centerX(consoleWidth);
		}
	};
}
