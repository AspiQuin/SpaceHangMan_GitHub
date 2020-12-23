#include "ofApp.h"
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <string>
#include <time.h>
//using namespace std;


//--------------------------------------------------------------
void ofApp::setup(){
	//bgImage.allocate(ofGetWindowWidth(), ofGetWindowHeight(), OF_IMAGE_GRAYSCALE);
	//bgImage.setColor(0);
	state = Constants::GAMESTATES::MENU;
	//Google Fonts Erica One
	myFont.load("EricaOne-Regular.ttf", 52);//Licence: https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL
	exitFont.load("EricaOne-Regular.ttf", 30);//Licence: https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL

	lossRect = myFont.getStringBoundingBox(Constants::LOSS_DECLA, 0, 0);
	winRect = myFont.getStringBoundingBox(Constants::WIN_DECLA, 0, 0);
	exitRect = exitFont.getStringBoundingBox(Constants::EXIT_DECLA, 0, 0);

	spaceman.load("image/Asset 2.png");
	spaceTarget = 100;
	spacePos.x = 0;
	spacePos.y = ofGetWindowHeight() / 2;
	

	starySun.load("image/sun.PNG");

	spaceman.resize(spaceman.getWidth() / 24, spaceman.getHeight() / 24);
	spaceman.setAnchorPercent(0.5, 0.5);
	starySun.setAnchorPercent(0.5, 0.5);

	password = LoadRandomWord("words.txt");
	//std::cout << wordToGuess;
	for (int i = 0; i < STARS; i++) {
		//printf("test");
		starPos[i].x = ofRandomWidth();
		starPos[i].y = ofRandomHeight();
		//starPos[i].z = ofRandom(3);
		
		//starPos[i] = ofVec2f(ofRandom(0, ofGetWindowWidth()), ofRandom(0, 600));
	}
	//starPos[0].x = ofRandomWidth();
	//starPos[0].y = ofRandomHeight();
	//ofDrawCircle(50, 50, 50);
	//bgImage.getTexture().loadScreenData(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, ofGetWindowWidth(), ofGetWindowHeight());
	// ofBitmapFont();
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update(){
	//count++;
	//std::cout << "test";

	switch (state) {
	case(Constants::MENU):
		state = Constants::TUTORIAL;
		break;
	case(Constants::TUTORIAL):
		state = Constants::GAME;
		break;
	case(Constants::GAME):
		alphabet = PrintAvailableLetters(guesses);
		win = PrintWordAndCheckWin(password, guesses);
	
		if (win)
			state = Constants::END;

		cout << errors;
		switch (errors) {
		case(0):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.01);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(1):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(2):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(3):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(4):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(5):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		case(6):
			spacePos.x = lerp(spacePos.x, spaceTarget, 0.1);
			dead = true;
			state = Constants::END;
			//spaceTarget += ofGetWindowWidth() / 7;
			break;
		default:
			break;
		}
		
		break;
	case(Constants::END):
		if (dead) {
			spaceman.resize(lerp(spaceman.getWidth(), 0, 0.02), lerp(spaceman.getHeight(), 0, 0.02));
			spacePos.x = lerp(spacePos.x, ofGetWindowWidth() + 800, 0.02);
			state = Constants::END;
		}
		
		break;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(25);
	ofSetColor(255);
	
	//ofDrawCircle(starPos[0], 2);
	ofFill();
	createStars();

	switch (state) {
	case(Constants::MENU):
		break;
	case(Constants::TUTORIAL):
		break;
	case(Constants::GAME):
		myFont.drawString(wordToGuess, ofGetWindowWidth() / 2 - stringRect.getWidth() / 2, 100);
		myFont.drawString(alphabet, ofGetWindowWidth()/2 - alphabitRect.getWidth()/2, ofGetWindowHeight() - 100);

	
		//ofSetColor(255, 165, 0);
		//ofDrawCircle(ofGetWindowWidth(), ofGetWindowHeight() / 2, ofGetWindowHeight() / 2 - 20);
		starySun.draw(ofVec2f(ofGetWindowWidth(), ofGetWindowHeight() / 2));
		//spaceman.update();
		ofSetColor(255);

		
		spaceman.draw(spacePos);
		break;
	case(Constants::END):
		starySun.draw(ofVec2f(ofGetWindowWidth(), ofGetWindowHeight() / 2));

		spaceman.draw(spacePos);

		if (win)
		{
			myFont.drawString(Constants::WIN_DECLA, ofGetWindowWidth() / 2 - winRect.getWidth() / 2, ofGetWindowHeight() / 2);
		}
		if (dead) 
		{
			myFont.drawString(Constants::LOSS_DECLA, ofGetWindowWidth() / 2 - lossRect.getWidth() / 2, ofGetWindowHeight() / 2);
			exitFont.drawString(Constants::EXIT_DECLA, ofGetWindowWidth() / 2 - exitRect.getWidth() /2, ofGetWindowHeight() / 2+ 80);
		}

		break;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (state) {
	case(Constants::MENU):
		break;
	case(Constants::TUTORIAL):
		break;
	case(Constants::GAME):
		//std::cout<<ofToString(key);
		key = toupper(key);
		if (guesses.find(key) == string::npos)
			guesses += key;

		if (errors != TriesLeft(password, guesses)) {
			errors = TriesLeft(password, guesses);
			spaceTarget += ofGetWindowWidth() / 7;
		}
		break;
	case(Constants::END):
		if (key=' ') {
			ofExit();
		}
		break;
	}
	/*
	switch (key) {
	case('a'):
		printf("A");
		//PrintMessage("Guess the word", true, true);
		//
		break;
	case('b'):
		printf("B");
		break;
	case('c'):
		printf("C");
		break;
	case('d'):
		printf("D");
		break;
	case('e'):
		printf("E");
		break;
	case('f'):
		printf("F");
		break;
	case('g'):
		printf("G");
		break;
	case('h'):
		printf("H");
		break;
	case('i'):
		printf("I");
		break;
	case('j'):
		printf("J");
		break;
	case('k'):
		printf("K");
		break;
	case('l'):
		printf("L");
		break;
	case('m'):
		printf("M");
		break;
	case('n'):
		printf("N");
		break;
	case('o'):
		printf("O");
		break;
	case('p'):
		printf("P");
		break;
	case('q'):
		printf("Q");
		break;
	case('r'):
		printf("R");
		break;
	case('s'):
		printf("S");
		break;
	case('t'):
		printf("T");
		break;
	case('u'):
		printf("U");
		break;
	case('v'):
		printf("V");
		break;
	case('w'):
		printf("W");
		break;
	case('x'):
		printf("X");
		break;
	case('y'):
		printf("Y");
		break;
	case('z'):
		printf("Z");
		break;
	case(' '):
		printf(" ");
		cout << guesses;
		break;
	default:
		break;
	}*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::createStars() {
	for (int i = 0; i < STARS; i++) {
		ofDrawCircle(starPos[i], ofRandom(1, 3));
	}
}

int ofApp::TriesLeft(string word, string guessed)
{
	int error = 0;
	for (unsigned int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
			error++; 
	}
	
	return error;
}

string ofApp::LoadRandomWord(string path)
{
	int charCount = 0;
	string word;
	vector <string> v;
	//ifstream reader(path);
	//words.open(ofToDataPath(path), ofFile::ReadWrite, false);
	buff = ofBufferFromFile(path, false);
	//buff.getLines();
	if (buff.getData()!=nullptr)
	{
		for (auto line : buff.getLines()) {
			word = line;
			v.push_back(word);
		}
		

		int randomLine = rand() % v.size();

		word = v.at(randomLine);
		words.close();
		buff.clear();
	}
	else {
		printf("failed");
	}
	for (unsigned int i = 0; i < word.length(); i++)
	{
		word[i] -= 32;
	}
	PrintWordAndCheckWin(word, guesses);
	stringRect = myFont.getStringBoundingBox(word, 0, 0);
	return word;
}

bool ofApp::PrintWordAndCheckWin(string word, string guessed)
{
	bool won = true;
	string s = "";
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	wordToGuess = s;
	//PrintMessage(s, false, true);
	return won;
}

void ofApp::PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
	if (printTop)
	{
		cout << "+---------------------------------+" << endl;
		cout << "|";
	}
	else
	{
		cout << "|";
	}
	bool front = true;
	for (int i = message.length(); i < 33; i++)
	{
		if (front)
		{
			message = " " + message;
		}
		else
		{
			message = message + " ";
		}
		front = !front;
	}
	cout << message.c_str();

	if (printBottom)
	{
		cout << "|" << endl;
		cout << "+---------------------------------+" << endl;
	}
	else
	{
		cout << "|" << endl;
	}
}

void ofApp::Birdcage(int guessCount = 0)

{
	if (guessCount >= 1)
	{
		cout << "                                 |" << endl;
		cout << "                                  \\" << endl;
		cout << "                                   \\" << endl;
		cout << "                                    \\" << endl;
	}
	else
		PrintMessage("", false, false);

	if (guessCount >= 2)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
	}

	else
		PrintMessage("", false, false);

	if (guessCount >= 3)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
		cout << "                             ----------" << endl;
	}
	else
		PrintMessage("", false, false);

	if (guessCount == 4)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
		cout << "                             ----------" << endl;
		cout << "                             {" << endl;
		cout << "                             {" << endl;

	}

	if (guessCount == 5)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
		cout << "                             ----------" << endl;
		cout << "                             {         }" << endl;
		cout << "                             {         }" << endl;
	}

	else
		PrintMessage("", false, false);

	if (guessCount >= 6)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
		cout << "                             ----------" << endl;
		cout << "                             {         }" << endl;
		cout << "                             {    0    }" << endl;
	}
	else
		PrintMessage("", false, false);

	if (guessCount >= 7)
	{
		cout << "                                 |" << endl;
		cout << "                                / \\" << endl;
		cout << "                               /   \\" << endl;
		cout << "                              /     \\" << endl;
		cout << "                             ----------" << endl;
		cout << "                             {         }" << endl;
		cout << "                             {    00   }" << endl;
	}
	else
		PrintMessage("", false, false);

}


string ofApp::PrintLetters(string input, char from, char to)
{
	string s;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i) == string::npos)
		{
			s += i;
			s += " ";
		}
		else
			s += "  ";
	}
	return s;
}
string ofApp::PrintAvailableLetters(string taken)
{
	string letters;
	letters = PrintLetters(taken, 'A', 'M'); 
	letters += PrintLetters(taken, 'N', 'Z');
	alphabitRect = myFont.getStringBoundingBox(letters,0,0);
	return letters;
}

float ofApp::lerp(float a, float b, float t) {
	return a + (b - a)*t;
}