#pragma once
#include "ofMain.h"
class Ball
{
public:
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;
	ofColor c;
    ofVec2f preAcc;
    
	float r;
	bool isColl;

	void init();
	void update(shared_ptr<Ball> other);
	void draw();

	void applyForce(ofVec2f force);
};

