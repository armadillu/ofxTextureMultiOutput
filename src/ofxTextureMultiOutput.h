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

 */

class ofxTextureMultiOutput{

public:

	void setup(int inX, int inY, int outX, int outY);

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

	map<int, ofRectangle> inputs; 	//mapped [0..1]
	map<int, ofRectangle> outputs; 	//mapped [0..1]

};

#endif /* defined(__BaseApp__ofxTextureMultiOutput__) */
