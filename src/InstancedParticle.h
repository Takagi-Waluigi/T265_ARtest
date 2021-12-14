#pragma once
#include "ofMain.h"

#define OBJECT_NUM 50000 

class InstancedParticle
{
public:
	void setup();
	void draw();

	ofParameter<ofFloatColor> lightColor;
	ofParameter<ofFloatColor> ambientColor;
	ofParameter<ofVec3f> lightPosition;

	ofShader shader;
	ofEasyCam cam;

	std::array<ofVec3f, OBJECT_NUM> positions;
	std::array<ofFloatColor, OBJECT_NUM> colors;


	ofVbo vao;
	ofBufferObject bufferObject;
	int amt;
};

