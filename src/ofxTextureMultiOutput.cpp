//
//  ofxTextureMultiOutput.cpp
//  BaseApp
//
//  Created by Oriol Ferrer Mesià on 11/03/15.
//
//

#include "ofxTextureMultiOutput.h"


void ofxTextureMultiOutput::setup(int inX_, int inY_, int outX_, int outY_, Rotation rot){
	rotation = rot;
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
			rotations[c] = rot;
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


void setScreenRotationForIndex(ofxTextureMultiOutput::Rotation r, int screenIndex){

}

void ofxTextureMultiOutput::draw(ofTexture& t, ofRectangle whereToDraw){

	//per unit sizes
	float outW = whereToDraw.width / outX;
	float outH = whereToDraw.height / outY;

	ofPushMatrix();
	ofTranslate(whereToDraw.x, whereToDraw.y);

	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	//make space for all the vertex and tex coords we will provide
	mesh.getVertices().resize(6 * num);
	mesh.getTexCoords().resize(6 * num);
	mesh.enableTextures();


	for(int i = 0; i < num; i++){

		ofRectangle & texInput = inputs[i];
		ofRectangle & texOutput = outputs[i];
		Rotation rot = rotations[i];

		float x = whereToDraw.width * texOutput.x;
		float y = whereToDraw.height * texOutput.y;
/*
v0       v1
   *----*
   |t\ t|
   |2 \1|
   *----*
v3       v2
*/

		ofVec2f v0 = ofVec2f(x, y);
		ofVec2f v1 = ofVec2f(x + outW, y);
		ofVec2f v2 = ofVec2f(x + outW, y + outH);
		ofVec2f v3 = ofVec2f(x, y + outH);

//		t.drawSubsection(whereToDraw.width * texOutput.x, whereToDraw.height * texOutput.y, //x, y
//						 outW, outH,	//w, h
//						 texInput.x * t.getWidth(), texInput.y * t.getHeight(), //tex origin x, tex origin y
//						 texInput.width * t.getWidth(), texInput.height * t.getHeight() //tex size x, tex size y
//						 );

		//vertex for triangle 1 (v0, v1, v2)
		mesh.getVertices()[i * 6 + 0].set(v0);
		mesh.getVertices()[i * 6 + 1].set(v1);
		mesh.getVertices()[i * 6 + 2].set(v2);

		//vertex for triangle 2 (v0, v2, v3)
		mesh.getVertices()[i * 6 + 3].set(v0);
		mesh.getVertices()[i * 6 + 4].set(v2);
		mesh.getVertices()[i * 6 + 5].set(v3);


		//now lets do the tex coords
		float tx = texInput.x * t.getWidth();
		float ty = texInput.y * t.getHeight();
		float tw = texInput.width * t.getWidth();
		float th = texInput.height * t.getHeight();

		vector<ofVec2f> texC;
		texC.resize(4);
		texC[0] = ofVec2f(tx, ty);
		texC[1] = ofVec2f(tx + tw , ty);
		texC[2] = ofVec2f(tx + tw, ty + th);
		texC[3] = ofVec2f(tx, ty + th);

		for(int i = 0; i < (int)rot; i++){ //shift around all tex coord as many times as we need to rotate 90
			ofVec2f temp = texC[3];
			texC.erase(texC.end() - 1);
			texC.insert(texC.begin(), temp);
		}

		//tex coord for triangle 1 (v0, v1, v2)
		mesh.getTexCoords()[i * 6 + 0].set(texC[0]);
		mesh.getTexCoords()[i * 6 + 1].set(texC[1]);
		mesh.getTexCoords()[i * 6 + 2].set(texC[2]);

		//tex coord for triangle 2 (v0, v2, v3)
		mesh.getTexCoords()[i * 6 + 3].set(texC[0]);
		mesh.getTexCoords()[i * 6 + 4].set(texC[2]);
		mesh.getTexCoords()[i * 6 + 5].set(texC[3]);

	}

	t.bind();
	mesh.draw();
	t.unbind();

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
		ofDrawBitmapString(ofToString(it->first), 10 + r.x, 20 + r.y);
		++it;
	}
	ofFill();
	ofPopMatrix();
}

void ofxTextureMultiOutput::drawDebugOutput(float x, float y, float w, float h){

	ofPushMatrix();
	ofTranslate(x, y);
	ofNoFill();
	ofDrawBitmapMode m = ofGetStyle().drawBitmapMode;
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

	int c = 0;
	map<int, ofRectangle>::iterator it = outputs.begin();
	while(it != outputs.end()){
		ofRectangle r = it->second;
		r.x = r.x * w;
		r.y = r.y * h;
		r.width = r.width * w;
		r.height = r.height * h;
		ofDrawRectangle(r);
		ofPushMatrix();
		ofTranslate(10 + r.x, 20 + r.y);
		Rotation rot = rotations[c];
		ofRotate(90 * (int)rot, 0, 0, 1);
		ofDrawBitmapString(ofToString(it->first), 0, 0 );
		ofPopMatrix();
		++it;
		c++;
	}
	ofFill();
	ofPopMatrix();
}
