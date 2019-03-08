#include "ofApp.h"
int r=255;
int g=255;
int b=255;
int a=0;
int a2=0;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0);
    video.load("fractal.mp4");
    video_two.load("fractal.mp4");
    video.setVolume(0.1);
    
    mVidGrabber.setVerbose(true);
    mVidGrabber.setup(160,120);
    mVidGrabber_two.setVerbose(true);
    mVidGrabber_two.setup(160,120);
    screenShot.load("screenShot.png");
    
    
    
    timerEnd = false;
    startTime =ofGetElapsedTimeMillis();
    img.load("color.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    video_two.update();
    mVidGrabber.update();
    mVidGrabber_two.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //set up timer and change the time by clicking on timeBar on screen
    
    ofPushMatrix();
    float barWidth = 600;
    float timer = ofGetElapsedTimeMillis()-startTime;
    ofSetFrameRate(8);
    ofSetColor(255,255,255,200);
    if (timer >= endTime){
        timerEnd = true;
    }
    for(int s=0; s < ofGetWindowWidth(); s+=100){
        for(int v=0; v < ofGetWindowHeight(); v+=100){
            
            if (timer >= 2000+s+v ) {
                
                img.drawSubsection(s, v, 100, 100, mouseX, mouseY, 50, 50);
            }
            
        }
    }
    
    ofPopMatrix();
    int pattern_width=160;
    int pattern_height=120;
    int width=160;
    int height=120;
    
    ofPushMatrix();
    ofSetColor(r,g,b,100);
    for(int c = 0; c < ofGetWindowWidth(); c += width/2){
        for(int b = 0; b < ofGetWindowHeight(); b += height/2)
        {
            mVidGrabber.draw(c,b,width/2,height/2);
        }
        
    }
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofSetColor(r,g,b,75);
    for(int j = 0; j < ofGetWindowWidth(); j += width) {
        for(int i = 0; i < ofGetWindowHeight(); i += height){
            video.draw(j, i, width, height);
        }
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofSetColor(255, 255, 0,75);
    for(int c = 0; c < ofGetWindowWidth(); c += width*2){
        for(int b = 0; b < ofGetWindowHeight(); b += height*2)
        {
            mVidGrabber_two.draw(c,b,width*2,height*2);
        }
        
    }
    ofPopMatrix();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'm'){
        timerEnd = false;
        startTime = ofGetElapsedTimeMillis();
    }
    
    switch (key) {
        case ' ':
            video.play();
            video_two.play();
            break;
        case OF_KEY_LEFT:
            video.previousFrame();
            video_two.previousFrame();
            break;
        case OF_KEY_RIGHT:
            video.nextFrame();
            video_two.previousFrame();
            break;
        case 's':
            video.stop();
            video_two.stop();
            break;
        case 'h':
            a=100;
            a2=100;
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key){
        case 'h':
            a=0;
            a2=0;
            break;
    }
    
    
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
    screenShot.grabScreen(0,0,ofGetWindowWidth(),ofGetWindowHeight());
    screenShot.save("screenShot.png");
    
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
