


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
//--------------------------------------------------------------


int main()
{
    //ofSetupOpenGL(320*3 , 240*3 ,OF_WINDOW);
	ofSetupOpenGL(320*3 , 240*3 , OF_FULLSCREEN);
    return ofRunApp(std::make_shared<ofApp>());
}
