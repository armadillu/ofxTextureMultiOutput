#include "ofApp.h"

/*
 
 Take this texture:

 <--- inX (8) --->
 +---+---+---+---+---+---+---+---+	|
 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | inY (1)
 +---+---+---+---+---+---+---+---+  |

 and re-draw it wit your custom layout:

 <--- outX (4) --->
 +---+---+---+---+
 | 0 | 1 | 2 | 3 |	|
 +---+---+---+---+ outY (2)
 | 4 | 5 | 6 | 7 |  |
 +---+---+---+---+
 
 */

void ofApp::setup(){
	ofBackground(22);
	ofLoadImage(tex, "test.png");
	//ofDisableArbTex();
	//ofEnableArbTex();
	output.setup(
				 8, 1,	//your input is 8 x 1
				 4, 2,	//define your output to 4 x 2
				 ofxTextureMultiOutput::ROTATE_180
				 );
}


void ofApp::draw(){

	float unitSizeX = 30;
	float unitSizeY = 50;
	float pad = 10; //ofGetMouseX();
	float y = pad;

	ofSetColor(ofColor::red);
	output.drawDebugInput(pad,
						  y,
						  unitSizeX * 8,
						  unitSizeY * 1
						  );

	y += unitSizeY + pad;

	ofSetColor(ofColor::green);
	output.drawDebugOutput(pad,
						   y,
						   unitSizeY * 4,
						   unitSizeX * 2
						   );

	y += unitSizeY * 2 + pad;
	y += pad;

	ofSetColor(255);

	//your canvas (input)
	tex.draw(pad, y, unitSizeX * 8, unitSizeY * 1);

	y += unitSizeY * 1 + pad;

	//your final output as defined, in the rect you want it in
	output.draw(tex, ofRectangle(pad,
								 y,
								 unitSizeY * 4,
								 unitSizeX * 2)
				);
}


