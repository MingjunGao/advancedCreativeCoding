#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int posY = 0;
    int posX = 0;
    for (int i = 0; i < mImages.size(); i++){
        posX = i*400;
        
        mImages[i].draw(posX,posY);
        
        if  (i*400  > ofGetWidth()){
            
            posY+=200;
            posX=0;
        }//if
       
    }//for

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='a'){
        mStrings.push_back(ofToString(key));
        
        ofImage image;
        if (image.load("http://lorempixel.com/400/200/sports/1/")){
            mImages.push_back(image);
        }//?
        ofLogNotice()<<mStrings.back()<< endl;
        
        
    }
    
    //esle if (key == 'd'){}
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mFloatingNums.push_back(ofRandom(100.0));
    ofLogNotice()<<"mFloatingNums has"<<
    mFloatingNums.size() <<endl;
    ofLogNotice() << mFloatingNums.back()<< endl;

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
