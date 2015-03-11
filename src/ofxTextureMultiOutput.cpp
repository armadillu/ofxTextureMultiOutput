//
//  ofxTextureMultiOutput.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 11/03/15.
//
//

#include "ofxTextureMultiOutput.h"


void ofxTextureMultiOutput::setup(int inX_, int inY_, int outX_, int outY_){
	inX = inX_;
	inY = inY_;
	outX = outX_;
	outY = outY_;

	int numIn = inX * inY;
	int numOut = outX * outY;

	if (numIn != numOut){
		ofLogError("ofxTextureMultiOutput") << "Num Inputs and Num Outputs don't match!";
		return;
	}
	num = numIn;

	float inW = 1.0f / inX;
	float inH = 1.0f / inY;
	int c = 0;
	for(int j = 0; j < inY; j++){
		for(int i = 0; i < inX; i++){
			ofRectangle r = ofRectangle(0,0, inW, inH);
			r.x = i * inW;
			r.y = j * inH;
			inputs[c] = r;
			c++;
		}
	}

	float outW = 1.0f / outX;
	float outH = 1.0f / outY;
	c = 0;
	for(int j = 0; j < outY; j++){
		for(int i = 0; i < outX; i++){
			ofRectangle r = ofRectangle(0,0, outW, outH);
			r.x = i * outW;
			r.y = j * outH;
			outputs[c] = r;
			c++;
		}
	}
}


void ofxTextureMultiOutput::draw(ofTexture& t, ofRectangle whereToDraw){

	//per unit sizes
	float outW = whereToDraw.width / outX;
	float outH = whereToDraw.height / outY;

	ofPushMatrix();
	ofTranslate(whereToDraw.x, whereToDraw.y);
	for(int i = 0; i < num; i++){
		//int i = int(0.1 * ofGetFrameNum())%num; //debug
		ofRectangle & texInput = inputs[i];
		ofRectangle & texOutput = outputs[i];
		t.drawSubsection(whereToDraw.width * texOutput.x, whereToDraw.height * texOutput.y, //x, y
						 outW, outH,	//w, h
						 texInput.x * t.getWidth(), texInput.y * t.getHeight(), //tex origin x, tex origin y
						 texInput.width * t.getWidth(), texInput.height * t.getHeight() //tex size x, tex size y
						 );
	}
	ofPopMatrix();
}


void ofxTextureMultiOutput::drawDebugInput(float x, float y, float w, float h){

	ofPushMatrix();
	ofTranslate(x, y);
	ofNoFill();
	map<int, ofRectangle>::iterator it = inputs.begin();
	while(it != inputs.end()){
		ofRectangle r = it->second;
		r.x = r.x * w;
		r.y = r.y * h;
		r.width = r.width * w;
		r.height = r.height * h;
		ofDrawRectangle(r);
		ofDrawBitmapString(ofToString(it->first), 10 + r.x, 10 + r.y);
		++it;
	}
	ofFill();
	ofPopMatrix();
}

void ofxTextureMultiOutput::drawDebugOutput(float x, float y, float w, float h){

	ofPushMatrix();
	ofTranslate(x, y);
	ofNoFill();

	map<int, ofRectangle>::iterator it = outputs.begin();
	while(it != outputs.end()){
		ofRectangle r = it->second;
		r.x = r.x * w;
		r.y = r.y * h;
		r.width = r.width * w;
		r.height = r.height * h;
		ofDrawRectangle(r);
		ofDrawBitmapString(ofToString(it->first), 10 + r.x, 10 + r.y);
		++it;
	}
	ofFill();
	ofPopMatrix();
}
