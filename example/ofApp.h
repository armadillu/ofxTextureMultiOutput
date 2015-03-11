#pragma once

#include "ofMain.h"
#include "ofxTextureMultiOutput.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update(){};
	void draw();

	void keyPressed(int key){};
	void keyReleased(int key){};

	ofxTextureMultiOutput output;
	ofTexture tex;

};
