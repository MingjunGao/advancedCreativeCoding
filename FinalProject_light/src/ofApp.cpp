#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowTitle("openFrameworks");
    
    ofBackground(39);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
    auto radius_span = 50;
    auto deg_span = 5;
    for (auto radius = 50; radius < 350; radius += radius_span) {
        
        ofRotate(ofGetFrameNum());
        
        for (auto deg = 0; deg < 360; deg += deg_span) {
            
            ofColor color;
            color.setHsb(ofMap(deg, 0, 360, 0, 255), 255, 255);
            ofSetColor(color);
            
            ofBeginShape();
            ofVertex(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
            ofVertex(glm::vec2(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD)));
            ofVertex(glm::vec2((radius + radius_span) * cos((deg + deg_span) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span) * DEG_TO_RAD)));
            ofVertex(glm::vec2((radius + radius_span) * cos((deg)* DEG_TO_RAD), (radius + radius_span) * sin((deg)* DEG_TO_RAD)));
            ofEndShape();
        }
    }

}
//--------------------------------------------------------------
int main() {
    
    ofSetupOpenGL(720, 720, OF_WINDOW);
    ofRunApp(new ofApp());
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
