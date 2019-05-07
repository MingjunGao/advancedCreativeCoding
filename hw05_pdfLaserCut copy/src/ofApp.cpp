#include "ofApp.h"
//use this one 

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(24);
    //ofSetFrameRate(60);
    ofSetWindowTitle("Architecture of Light");
    
    
    ofEnableDepthTest();
    
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    }


//--------------------------------------------------------------
void ofApp::draw(){
    ofColor deepprl = ofColor ( 100 , 17 , 217 ) ;
    ofBackgroundGradient (ofColor::white, deepprl,OF_GRADIENT_CIRCULAR);
    
    ofDrawBitmapString("Architecture of Light", 31, 92);
    
    this->cam.begin();
    
    for (int v = 0; v < 360; v += 6) {
        
        ofColor color01;
        /*Approximate hues for some common colors:
         
         Red: 0 (wrapped round from 255)
         Orange: 25
         Yellow: 42
         Green: 85
         Blue: 170
         Purple: 205
         Red: 255 (wraps round to 0)
         */
        float red = 0;
        float ble = 170;
        float org = 25;
        float ylw = 42;
        float prp = 205;
        
        // string string[
        //b h s
        //  color.setHsb(ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, 0, 255), 255, 230);
        color01.setHsb(ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, ble, ble+10), ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, 200, 100), 250);
        
        
        int tmp_v = v;
        for (int u = -180; u <= 180; u += 6) {
            
            ofSetColor(color01);
            ofBeginShape();
            ofVertex(this->make_point(300, 80, u - 3, tmp_v - 3));
            ofVertex(this->make_point(300, 80, u - 9, tmp_v - 3));
            ofVertex(this->make_point(300, 80, u - 3, tmp_v + 3));
            ofVertex(this->make_point(300, 80, u + 3, tmp_v + 3));
            ofEndShape(true);
            
            tmp_v += 6;
        }
    }
    
    ofDrawBox(100, 100, 100, 50);
    //hand draw shapes
    
    
    //grab real time sky video + mask
    
    
    this->cam.end();
	
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


