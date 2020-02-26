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


		float minCropW = 1000;
		float minCropH = 600;

		float maxCropW = 500;
		float maxCropH = 300;

		bool constellationViz = false;

		list<glm::vec2> constPoints;

		json data;

		string imageName;
		ofImage img;
};
