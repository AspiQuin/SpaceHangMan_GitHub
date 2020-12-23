#pragma once
#include "ofApp.h"

namespace Constants {
	static const string WIN_DECLA = "Congratulations! You survived!";
	static const string LOSS_DECLA = "Sizzle... Game Over!";
	static const string EXIT_DECLA = "Press spacebar to exit";
	

	enum GAMESTATES {
		MENU,
		TUTORIAL,
		GAME,
		END
	};
}