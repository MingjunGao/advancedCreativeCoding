#include "ofApp.h"
//Assignment 05: Laser Cutting

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
	ofSetWindowShape(800,1200);
    ofBackground(239);
    
	angle = 0;
    noiseArg = 0;

    //boolean
	oneShot = false;
	pdfRendering = false;
    returnRate =true;
	ofSetVerticalSync(true);
	//load a custom font
	//the ttf file must be inside your bin/data directory
	font.load("frabk.ttf", 24, true, false, true);
    
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
	angle++;
    noiseArg += 0.05;
    
    if( (returnRate)&&ofGetFrameRate()<=12){
        ofSetFrameRate(60);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    //one pdf is true:
	if( oneShot ){
		ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
	}
    if( oneShot ){
        ofEndSaveScreenAsPDF();
        oneShot = false;
    }
    
    //mutiple pdf is true:
	if( pdfRendering ){
    //flip condition
		ofDrawBitmapString("press r to stop pdf multipage rendering", 32, 52);
	}else{
        //boolen pdfrendering is not true
		ofDrawBitmapString("press r to start pdf multipage rendering\npress s to save a single screenshot as pdf to disk", 32, 52);
	}
    
	
    
    
    //draw lake shape
    
    ofPushMatrix();
	//centered
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ofSetColor(39);
    ofNoFill();
    ofSetLineWidth(2);
    
  
    float noiseValue = ofNoise(noiseArg);
    //auto: auto-type
    auto radius_base = 250*ofMap(noiseValue,0.01, 1.0, 0.8, 1.5);//outer radius
    auto len = 125;//distance=outerR-innerR
    auto deg_span = 5; //5 degrees each span
    //degrees
    for (auto deg = 0; deg < 360; deg += deg_span) {
        //2dVector;
        auto noise_point = glm::vec2(radius_base * cos(deg * DEG_TO_RAD), radius_base * sin(deg * DEG_TO_RAD));
        auto noise_value = ofNoise(noise_point.x * 0.01, noise_point.y * 0.01, ofGetFrameNum() * 0.01);
      
        auto radius = radius_base;
        //push out
        if (noise_value > 0.7) { radius += ofMap(noise_value, 0.7, 1.0, 0, radius_base * 0.5); }
        //push in
        if (noise_value < 0.3) { radius -= ofMap(noise_value, 0.0, 0.3, radius_base * 0.5, 0); }
        
        
        ofBeginShape();
        //out
        ofVertex(glm::vec2(radius * cos((deg - deg_span * 0.5)  * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD)));
        ofVertex(glm::vec2(radius * cos((deg + deg_span * 0.5)  * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD)));
        //in
        ofVertex(glm::vec2((radius - len) * cos((deg + deg_span * 0.5)  * DEG_TO_RAD), (radius - len) * sin((deg + deg_span * 0.5) * DEG_TO_RAD)));
        ofVertex(glm::vec2((radius - len) * cos((deg - deg_span * 0.5)  * DEG_TO_RAD), (radius - len) * sin((deg - deg_span * 0.5) * DEG_TO_RAD)));
        ofEndShape(true);
        
    }//for deg ends
	ofPopMatrix();	
	

	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if( key=='r'){
		pdfRendering = !pdfRendering;	
		if( pdfRendering ){
			ofSetFrameRate(12);  // so it doesn't generate tons of pages
			ofBeginSaveScreenAsPDF("recording-"+ofGetTimestampString()+".pdf", true);
            returnRate=false;
            
		}else{
			ofSetFrameRate(60);
			ofEndSaveScreenAsPDF();
            returnRate=true;
		}
	}
	
	if( !pdfRendering && key == 's' ){
		oneShot = true;
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


