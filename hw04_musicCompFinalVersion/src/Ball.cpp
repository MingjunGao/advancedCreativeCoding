#include "Ball.h"

void Ball::init()
{
	this->pos = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	this->vel = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
	this->acc = ofVec2f(ofRandom(-.1, .1), ofRandom(-.1, .1));

	this->r = ofRandom(20, 50);
	this->isColl = false;
	this->c = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Ball::update(shared_ptr<Ball> other)
{
	if (this->isColl) this->isColl = false;


	if (this->pos.x <= this->r) {
		this->pos.x = this->r + 5;
		this->vel.x *= -.6;
	}
	else if (this->pos.y <= this->r) {
		this->pos.y = this->r + 5;
		this->vel.y *= -.6;
	}
	else if (this->pos.x >= ofGetWidth() - this->r) {
		this->pos.x = ofGetWidth() - 5 - this->r;
		this->vel.x *= -.6;
	}
	else if (this->pos.y >= ofGetHeight() - this->r) {
		this->pos.y = ofGetHeight() - 5 - this->r;
		this->vel.y *= -.6;
	}

	//collision

	auto dist = this->pos.distance(other->pos);
	
	if (dist <= this->r + other->r && !this->isColl && !other->isColl) {
		auto temp = (other->vel - this->vel) * .6;
		other->vel =-temp;
		this->vel = temp;

		isColl = true;
	}
	//attraction && repel

	auto dir = other->pos - this->pos;
	auto strength = dir.length() * 2000;
	strength /= pow(dist, 2);
	strength = ofClamp(strength, 5, 1000);
    auto arrow = dist >= 200 ? 1 :  -.6;
	this->applyForce(arrow*dir.normalize()*strength);
	

 
	this->vel += this->acc;
    this->vel = this->vel.getNormalized() * ofClamp(this->vel.length(), 1, 10);
	this->pos += this->vel;
    this->preAcc = this->acc;
	this->acc *= 0;
	
}

void Ball::draw()
{
	ofSetColor(this->c);
	ofFill();
	ofDrawCircle(this->pos, this->r);
}

void Ball::applyForce(ofVec2f force) 
{
	auto acc = force / this->r;
	this->acc += acc;
}
