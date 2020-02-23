#include <string>
#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){

	imageName = "1753842115-1";
	string path = "C:/Users/Christian Broms/Documents/NarrativeMaker/NarrativeMaker/bin/data/" + imageName + ".json";
	
	// load the data
	ifstream i(path);
	i >> data;

	cout << data["w"] << " " << data["h"] << endl;
	numberOfFrames = data["data"].size();

	// load the image
	img.load("1.jpg");

	// need to ensure the framerate is the same as when the recording was made
	ofSetFrameRate(15);
}	

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30);
	img.draw(data["x"], data["y"], data["w"], data["h"]);


	if (currentFrame < numberOfFrames - 5) {

		// do an average of the points around +/-5
		long totalX = 0;
		long totalY = 0;
		float totalMultipliers = 0;

		for (float i = -4; i <= 5; i++) {

			float multiplier = 1;

			// create a multiplier so that as the locations become closer to the current one, 
			// they are given more weight 
			//if (i == 0) { multiplier = 1 / 2.0; }
			//else { multiplier = abs((1 / i) / 2.0); }

			//totalMultipliers += multiplier;

			// add the locations to the total count for x and y
			totalX += static_cast<long>(data["data"][i + currentFrame]["gazeX"]);
			totalY += static_cast<long>(data["data"][i + currentFrame]["gazeY"]);
		}
		float x = totalX / 10;
		float y = totalY / 10;
		prevX = x;
		prevY = y;

		
		// alternate approach: only move if the next frame is greater than a certain distance threshold away

		/*int threshold = 20;

		if (data["data"][currentFrame]["fixationX"] > prevX + threshold ||
			data["data"][currentFrame]["fixationX"] < prevX - threshold) {
			prevX = data["data"][currentFrame]["fixationX"];
		}

		if (data["data"][currentFrame]["fixationY"] > prevY + threshold ||
			data["data"][currentFrame]["fixationY"] < prevY - threshold) {
			prevY = data["data"][currentFrame]["fixationY"];
		}*/

		//prevX  = data["data"][currentFrame]["gazeX"];
		//prevY = data["data"][currentFrame]["gazeY"];

		int topX = prevX - (cropW / 2);
		int topY = prevY - (cropH / 2);
		
		ofImage screen;
		screen.grabScreen(topX, topY, cropW, cropH);
		screen.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

		string path = "output/" + imageName + "-" + to_string(currentFrame) + ".png";
		screen.saveImage(path, OF_IMAGE_QUALITY_BEST);
	
		currentFrame++;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
}

