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
    int bufferSize        = 512;
    volume                = 0.6f;
    pan =0.5f;
    
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    
    lAudio.assign(bufferSize, 0.0);
    rAudio.assign(bufferSize, 0.0);
    
  
    
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
	ofBackground(34, 34, 34);

    ofSetColor(225);
    ofDrawBitmapString("press 's' to unpause the audio\npress 'e' to pause the audio", 31, 92);
    
        ofNoFill();
    // draw the left channel:
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 150, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Left Channel", 4, 18);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, 450, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(1.5);
    
    ofBeginShape();
    for (unsigned int i = 0; i < lAudio.size(); i++){
        float l =  ofMap(i, 0, lAudio.size(), 0, 450, true);
        ofVertex(l, 100 -lAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    // draw the right channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(500, 150, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Right Channel", 4, 18);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, 450, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(1.5);
    
    ofBeginShape();
    for (unsigned int i = 0; i < rAudio.size(); i++){
        float l =  ofMap(i, 0, rAudio.size(), 0, 450, true);
        ofVertex(l, 100 -rAudio[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    for (int i = 0; i < 5; i++) balls[i]->draw();
}




void ofApp::audioOut(ofSoundBuffer &outBuffer){
    float leftScale = 1 - pan;
    float rightScale = pan;
   
    while (phase > TWO_PI){
        phase -= TWO_PI;
    }
    
    for(int i = 0; i < outBuffer.size(); i += 2) {
        auto cooin = generateSample(phase, balls[0]);
        float sample = cooin * (ofMap(balls[0]->vel.length(), 0, 10, 0, .8)+.2); // generating a sine wave sample
        
        float x = balls[0]->pos.x;
        float w = ofGetWidth();
        float rightOffset = ofMap(x - w/2.0, -w/2.0 , w/2.0, -1, 1);
        rightOffset = (-1 * abs(rightOffset)) + 1;
        float leftOffset = 1 - abs(rightOffset);
        
        rAudio[i]= sample * volume*leftOffset;
        lAudio[i]= sample * volume*rightOffset;
        outBuffer[i] = sample * volume*rightOffset; // writing/drawing to the left channel
        outBuffer[i+1] = sample * volume*leftOffset; // writing/drawing to the right channel
        //memorize this equation! phaseOffset = freq / sampleRate
        float phaseOffset = ((float)2000 / ofMap(balls[0]->preAcc.length(), 0, 80/balls[0]->r, 60, 2500));
        phase += phaseOffset;
      
       
       }
    
}

float ofApp::generateSample(float phase, shared_ptr<Ball> ball){
    auto waveType = waveTypeGenerator(ball->pos);
    switch (waveType) {
        case 1://sine
            return sin(phase*TWO_PI);
            break;
        case 2://square
            return sin(phase*TWO_PI) > 0 ? .5 : -.5;
        case 3://sawtooth
            return fmod(phase,TWO_PI);
        case 4://triangle
            return abs(sin(phase*TWO_PI));
        default:
            break;
    }
}

int ofApp::waveTypeGenerator(ofVec2f ballPos){
    if (ballPos.x >= 0 && ballPos.x < ofGetWidth()/2){
        if (ballPos.y >= 0 && ballPos.y < ofGetHeight()/2){
            return 1;
        } else {
            return 2;
        }
    } else {
        if (ballPos.y >= 0 && ballPos.y < ofGetHeight()/2){
            return 3;
        } else {
            return 4;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 's' ){
        soundStream.start();
    }
    
    if( key == 'e' ){
        soundStream.stop();
    }

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
