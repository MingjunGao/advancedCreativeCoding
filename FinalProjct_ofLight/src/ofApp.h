

#pragma once

//video streaming
#include "ofMain.h"
#include "IPVideoGrabber.h"

#include "ofxXmlPoco.h"
// Leap Motion
#include "ofxLeapMotion2.h"



class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
//standard name
    std::vector<std::shared_ptr<ofx::Video::IPVideoGrabber>> grabbers;

    void reloadCameras();
    ofx::Video::IpVideoGrabberSettings& getNextCamera();
    std::vector<ofx::Video::IpVideoGrabberSettings> ipcams; // a list of IPCameras
    std::size_t nextCamera = 0;

    // This message occurs when the incoming video stream image size changes. 
    // This can happen if the IPCamera has a single broadcast state (some cheaper IPCams do this)
    // and that broadcast size is changed by another user. 
    void videoResized(const void* sender, ofResizeEventArgs& arg);

    std::size_t numCameras = 1;
    std::size_t numCameraRows = 1;
    std::size_t numCameraColumns = 1;
    
    //donut
    glm::vec3 make_point(float R, float r, float u, float v);
      vector<glm::vec3> locations;
    
    // Leap Motion
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    vector <int> fingersFound;
    
    //cam
    ofEasyCam cam;
    
  
    //sound
    ofSoundPlayer ocean;
    ofSoundPlayer haixx;
    
};
