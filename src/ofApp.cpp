#include <string>
#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){

	imageName = "1855695784-1";
	string path = "C:/Users/Christian Broms/Documents/NarrativeMaker/NarrativeMaker/bin/data/" + imageName + ".json";
	
	// load the data
	ifstream i(path);
	i >> data;

	cout << data["w"] << " " << data["h"] << endl;
	numberOfFrames = data["data"].size();

	// load the image
	img.load("1.jpg");

	// need to ensure the framerate is the same as when the recording was made
	ofSetFrameRate(30);
}	

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30);
	img.draw(data["x"], data["y"], data["w"], data["h"]);


	if (constellationViz) { // constellation visualization, draw outlines
		ofSetColor(255);
		
		if (currentFrame < numberOfFrames) {
			// add the current point to the list of points
			constPoints.push_back(glm::vec2(data["data"][currentFrame]["gazeX"], data["data"][currentFrame]["gazeY"]));
			currentFrame++;
		}

		// iterate through the list and draw the lines over the image
		glm::vec2 prev = glm::vec2(0, 0);

		list<glm::vec2>::iterator it;
		for (it = constPoints.begin(); it != constPoints.end(); it++)
		{
			if (prev == glm::vec2(0, 0)) {
				prev = *it;
			}
			else {
				// only draw the line if it's closer than 200 pixels to the last one
				// (accounts for weird noise and differences between each recording,
				// since it's all from one file
				if (abs(prev.x - (*it).x) < 200 && abs(prev.y - (*it).y) < 200) {
					ofDrawLine(prev.x, prev.y, (*it).x, (*it).y);
				}
				prev = glm::vec2((*it).x, (*it).y);
			}
		}
	}
	else { // export the video frames for the other visualization

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


			// calculate the difference in distance between prev location and current location
			float moveDiff = abs(prevX - x) + abs(prevY - y);

			// map the distance diff to the small and large widths and heights, so the frame zoom 
			// is determined by the difference in distance
			int zoomValW = (moveDiff - 0) / (100.0 - 0) * (minCropW - maxCropW) + maxCropW;
			int zoomValH = (moveDiff - 0) / (100.0 - 0) * (minCropH - maxCropH) + maxCropH;

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


			// calculate the top right position of the new frame, with the zoom 
			int topX = prevX - (zoomValW / 2);
			int topY = prevY - (zoomValH / 2);


			// grab the screen at the position and export as an image
			ofImage screen;
			screen.grabScreen(topX, topY, zoomValW, zoomValH);
			screen.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
			// for some stupid reason resizing changes the image colors 
			//screen.resize(minCropW, minCropH);
			string path = "output/" + imageName + "-" + to_string(currentFrame) + ".png";
			screen.saveImage(path, OF_IMAGE_QUALITY_BEST);

			currentFrame++;
		}
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
}

