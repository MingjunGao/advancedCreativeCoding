#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //x y coordinates separate
    int midX = ofGetWidth()/2;
    int midY = ofGetHeight()/2;

    ofDrawEllipse (midX, midY, 100, 100);
    
    //glm:ivec2 date type
    glm::ivec2(midX,midY);
       ofDrawEllipse (midX-100, midY, 100, 100);
    
    //glm::midpoint =glm::ivec2(midX,midY)=
    auto midpoint = glm::ivec2(midX,midY);
    ofDrawEllipse (midpoint.x+100,midpoint.y,100,100);
    
    float();
    int ();
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
