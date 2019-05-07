#include "ofMain.h"
#include "ofApp.h"
//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {
    
    
    
    u *= DEG_TO_RAD;
    v *= DEG_TO_RAD;
    
    float x = (R + r * cos(u)) * cos(v);
    float y = (R + r * cos(u)) * sin(v);
    float z = r * sin(u);
    
    return glm::vec3(x, y, z);
}

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
