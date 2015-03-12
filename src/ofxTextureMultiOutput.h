//
//  ofxTextureMultiOutput.h
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 11/03/15.
//
//

#ifndef __BaseApp__ofxTextureMultiOutput__
#define __BaseApp__ofxTextureMultiOutput__

#include "ofMain.h"

/*

 This will take any Fbo you provide and split it from your specified grid layout
 into your specified output layout. The input fbo will be drawn

 Your provided Texture (input):

 <--- inX (8) --->
 +---+---+---+---+---+---+---+---+	|
 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | inY (1)
 +---+---+---+---+---+---+---+---+  |

 Drawn Texture Layout (output):
 
 <--- outX (4) --->
 +---+---+---+---+
 | 0 | 1 | 2 | 3 |	|
 +---+---+---+---+ outY (2)
 | 4 | 5 | 6 | 7 |  |
 +---+---+---+---+
 
 You can also decide rotation on each individual section

 */

class ofxTextureMultiOutput{

public:

	enum Rotation{
		NO_ROTATE = 0, //using the enum val as the number of 90º rotations!
		ROTATE_90 = 1,
		ROTATE_180 = 2,
		ROTATE_270 = 3
	};

	void setup(int inX, int inY, int outX, int outY, Rotation r);
	void setScreenRotationForIndex(Rotation r, int screenIndex);

	void draw(ofTexture& tex, ofRectangle whereToDraw);

	//mostly for dev
	void drawDebugInput(float x, float y, float w, float h);
	void drawDebugOutput(float x, float y, float w, float h);

private:

	int num;
	int inX;
	int inY;
	int outX;
	int outY;

	Rotation rotation;
	map<int, ofRectangle> 	inputs; 	//mapped [0..1]
	map<int, ofRectangle> 	outputs; 	//mapped [0..1]
	map<int, Rotation>		rotations;


};

#endif /* defined(__BaseApp__ofxTextureMultiOutput__) */
