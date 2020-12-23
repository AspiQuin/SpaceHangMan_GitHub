#pragma once

#include "ofMain.h"
#include "Constants.h"
//#include "graphics/ofImage.h"
#include<string>
#include<iostream>
#include <cctype>
using namespace std;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		int errors;
		int state;

		string guesses;
		string wordToGuess;
		string password;
		string alphabet;

		static const int STARS = 1000;
		ofImage bgImage;

		ofVec3f starPos[STARS];

		ofImage spaceman;
		ofVec2f spacePos;
		float spaceTarget;

		ofImage starySun;

		ofFile words;
		ofBuffer buff;

		ofTrueTypeFont myFont;
		ofTrueTypeFont exitFont;
		ofRectangle stringRect;
		ofRectangle alphabitRect;

		ofRectangle winRect;
		ofRectangle lossRect;
		ofRectangle exitRect;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		void createStars();
		int TriesLeft(string word, string guessed);
		string LoadRandomWord(string path);
		bool PrintWordAndCheckWin(string word, string guessed);
		void PrintMessage(string message, bool printTop, bool printBottom);
		void Birdcage(int guessCount);
		string PrintLetters(string input, char from, char to);
		string PrintAvailableLetters(string taken);

		float lerp(float a, float b, float t);

		int count;
		bool win;
		bool dead;
};
