#pragma once

#include <nlohmann/json.hpp>
#include "ofMain.h"

using json = nlohmann::json;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
	
		int currentFrame = 5;
		int numberOfFrames;
		
		float prevX = 0;
		float prevY = 0;

		int cropW = 500;
		int cropH = 300;

		json data;

		string imageName;
		ofImage img;
};
