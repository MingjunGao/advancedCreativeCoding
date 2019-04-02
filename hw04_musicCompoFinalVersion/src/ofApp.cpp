#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    for (int i = 0; i < 5; i++) {
        auto b = make_shared<Ball>();
        b->init();
        balls.push_back(b);
    }
    
    phase = 0;
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = 512;
    soundStream.setup(settings);

}

//--------------------------------------------------------------
void ofApp::update(){
    
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			if (i != j) balls[i]->update(balls[j]);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(122, 123, 124);

    for (int i = 0; i < 5; i++) balls[i]->draw();

}


void ofApp::audioOut(ofSoundBuffer &outBuffer){
    
    for(int i = 0; i < outBuffer.size(); i += 2) {
        float sample = sin(phase*TWO_PI) * (ofMap(balls[0]->vel.length(), 0, 10, 0, .8)+.2); // generating a sine wave sample
        float x = balls[0]->pos.x;
        float w = ofGetWidth();
        float rightOffset = ofMap(x - w/2.0, -w/2.0 , w/2.0, -1, 1);
        rightOffset = (-1 * abs(rightOffset)) + 1;
        float leftOffset = 1 - abs(rightOffset);
   
        outBuffer[i] = sample * rightOffset; // writing to the left channel
        outBuffer[i+1] = sample * leftOffset; // writing to the right channel
        //memorize this equation! phaseOffset = freq / sampleRate
        float phaseOffset = ((float)2000 / ofMap(balls[0]->preAcc.length(), 0, 80/balls[0]->r, 60, 2500));
        phase += phaseOffset;
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
