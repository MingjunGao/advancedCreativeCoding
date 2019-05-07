//Mingjun Gao Final Project updated: 05/02/19

//References:
//1.Video Grabber, 2009 Christopher Baker <https://christopherbaker.net>



#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    //leapmotion
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setOrientation(ofPoint(-20, 0, 0));
    ipcams = ofx::Video::IpVideoGrabberSettings::fromFile("streams.json");
    leap.open();
    
    ocean.load("ocean.mp3");
    ocean.play();
    haixx.load ("海がきこえるファーストインプレッションピアノアレンジ.mp3");
    haixx.play();

    //this->threshold = 0.5;
    
    // keep app receiving data from leap motion even when it's in the background
    leap.setReceiveBackgroundFrames(true);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    //bool lightOn = false;//lights on: true/false
    
    ofLogNotice("ofApp::setup()") << "Loaded " << ipcams.size() << " locations.";
    
    reloadCameras();
}


ofx::Video::IpVideoGrabberSettings& ofApp::getNextCamera()
{
  
     nextCamera = (nextCamera + 1) % ipcams.size();
    return ipcams[nextCamera];
}


//--------------------------------------------------------------
void ofApp::reloadCameras()
{
    // Clear the grabbers.
    grabbers.clear();

    // Initialize new grabbers.
    for (std::size_t i = 0; i < numCameras; ++i)
    {
        auto c = std::make_shared<ofx::Video::IPVideoGrabber>();
        auto& settings = getNextCamera();
        c->setUsername(settings.getUsername());
        c->setPassword(settings.getPassword());
        c->setURI(settings.getURL());
        c->connect();

        grabbers.push_back(c);;
    }
}

//--------------------------------------------------------------

void ofApp::videoResized(const void* sender, ofResizeEventArgs& arg)
{
    // Find the camera that sent the resize event changed.
    for (std::size_t i = 0; i < numCameras; ++i)
    {
        if (sender == grabbers[i].get())
        {
            std::stringstream ss;
            ss << "videoResized: ";
            ss << "Camera connected to: " << grabbers[i]->getURI() + " ";
            ss << "New DIM = " << arg.width << "/" << arg.height;
            ofLogVerbose("ofApp") << ss.str();
        }
    }
}


//--------------------------------------------------------------
void ofApp::update()
{
    for (auto& grabber: grabbers)
    {
        grabber->update();
    }
    
       ofSoundUpdate();
    ocean.setLoop(true);
    haixx.setLoop(true);
    fingersFound.clear();
    
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                fingersFound.push_back(id);
                
                
                float volume =ofMap(mcp.y,0,ofGetHeight(),0,1 );
                haixx.setVolume(volume);
                 float volume2 =ofMap(mcp.x,0,ofGetWidth(),0,1 );
                 ocean.setVolume(volume2);
                //"bri": null, // brightness: 0-255
                //"hue": null, // hue: 0-255
                //"sat": 255   // always set to 255 for full color
                //b s h
                
            }
        }
    }
    
 
    leap.markFrameAsOld();//tell the frame is not new
    
    ofSeedRandom(39);
    this->locations.clear();
    while (this->locations.size() < 500) {
        
        float R = 300;
        float r = 50;
        float u = ofRandom(0, 360) + ofGetFrameNum() * ofRandom(0.5, 2);
        float v = ofRandom(0, 360);
        
        this->locations.push_back(this->make_point(R, r, u, v));
    }
}


//--------------------------------------------------------------
void ofApp::draw()
{
    
     ofColor deepprl (100,17,217);//defualt purple color
    ofBackgroundGradient (ofColor::white, deepprl,OF_GRADIENT_CIRCULAR);
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
   // ofColor deepprl = ofColor ( 100 , 17 , 217 ) ;
    for(int i = 0; i < simpleHands.size(); i++){
        for (int f=0; f<5; f++) {
            int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;
            fingersFound.push_back(id);
            
            //ofColor rainbow =ofColor
        //second: hue
            deepprl.setHsb(ofMap((ofGetFrameNum() *3) % 360, 0, 360, 160,200), ofMap(mcp.z, 0,400, 100,205),255);
            ofBackgroundGradient (ofColor::white, deepprl,OF_GRADIENT_CIRCULAR);
            //leap
           
            //"bri": null, // brightness: 0-255
            //“hue"
            //"sat": 255   // always set to 255 for full color
        
            
        }
    }



    cam.begin();
    
    ofSetHexColor(0xffffff);
    
    std::size_t row = 0;
    std::size_t col = 0;
    
    float x = 0;
    float y = 0;
    //width and height of the video 
    float w = ofGetWidth() / numCameraColumns;
    float h = ofGetHeight() / numCameraRows;
    
    float totalKbps = 0;
    float totalFPS = 0;
    //for (
    ofPushMatrix();
    //center the video
    int x_pos = ofGetWidth() /2.0-w;
    int y_pos = ofGetHeight()/2.0-h;
    ofTranslate(x_pos, y_pos);
    for (std::size_t i = 0; i < grabbers.size(); ++i)
    {
        x = col * w;
        y = row * h;

        // draw my streaming camera
        row = (row + 1) % numCameraRows;

        if (row == 0)
        {
            col = (col + 1) % numCameraColumns;
        }
        
        ofPushMatrix();
        //center the camera dont change
        ofTranslate(x/2+320,y/2+152);
        ofSetColor(255,255,255,255);
        grabbers[i]->draw(0,0,w*0.62,h*0.72); // draw the camera
        
        ofEnableAlphaBlending();
        
        // draw the info box
        //ofSetColor(0,80);
        //ofDrawRectangle(5,5,w-10,h-10);
        
        float kbps = grabbers[i]->getBitRate() / 1000.0f; // kilobits / second, not kibibits / second
        totalKbps+=kbps;
        
        float fps = grabbers[i]->getFrameRate();
        totalFPS+=fps;
        
        std::stringstream ss;
     
        ofSetColor(255);
        ofDrawBitmapString(ss.str(), 10, 10+12);
        
        ofDisableAlphaBlending();
        
        ofPopMatrix();
        ofPopMatrix();
    }
    
    
    // keep track of some totals
    float avgFPS = totalFPS / numCameras;
    float avgKbps = totalKbps / numCameras;

    ofEnableAlphaBlending();
    ofSetColor(0,80);
    ofDrawRectangle(5,5, 150, 40);
    
    
    
    ofColor color01;
    //donut
    for (int v = 0; v < 360; v += 6) {
        
        
        // "lighton": false, // lights on: true/false
      /*
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
        
      
        //b h s
        //  color.setHsb(ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, 0, 255), 255, 230);
        color01.setHsb(ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, ble, ble+10), ofMap((ofGetFrameNum() * 5 + v) % 360, 0, 360, 200, 100), 250);
        auto noise_value = ofNoise(x * 0.0005, y * 0.0005,  ofGetFrameNum() * 0.005);
       // auto noise_value = ofNoise (v*0.0005, ofGetFrameNum()*0.005);
        
        //auto rotate = ofMap(noise_value, this->threshold, 1, 0, 360 * 3);
        int tmp_v = v;
        auto m=1;
        auto n=1;
        //change the donut size by reloacting vertex x/ypositions
        
        for (int u = -180; u <= 180; u += 6) {
            //ofRotateDeg(rotate);
            //2d shape runs to create a donut
            ofSetColor(color01);
            ofBeginShape();
            ofVertex(this->make_point(565*m, 125*n, u - 3, tmp_v - 3));
            ofVertex(this->make_point(565*m, 125*n, u - 9, tmp_v - 3));
            ofVertex(this->make_point(565*m, 125*n, u - 3, tmp_v + 3));
            ofVertex(this->make_point(565*m, 125*n, u + 3, tmp_v + 3));
            ofEndShape(true);
            
            tmp_v += 6;
        }
    }
    
    
    for (auto& location : this->locations) {
        
        ofSetColor(color01);
        ofDrawSphere(location, 3);
        for (auto& other : this->locations) {
            
            if (location == other) { continue; }
            float distance = glm::distance(location, other);
            if (distance < 50) {
                
                ofSetColor(ofMap(distance, 10, 50, 39, 239));
            }
        }
        
    }
   
    
    
    //hand draw shapes

    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft        = simpleHands[i].isLeft;
        ofPoint handPos    = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;
   
     
        ofColor color02;
         float yl = 85;
        color02.setHsb(ofMap((ofGetFrameNum() * 5 + i) % 360, 0, 360, yl-5, yl+10), ofMap((ofGetFrameNum() * 5 + i) % 360, 0, 360, 200, 100), 200);
        ofSetColor(color02);
        //palm
       // ofDrawBox(handPos.x, handPos.y, handPos.z, 60, 100,20);
        ofDrawSphere(handPos.x, handPos.y, handPos.z, 20);
        
        //ofDrawArrow(handPos, handPos + 100*handNormal);
        
        for (int f=0; f<5; f++) {
            
            ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp;  // metacarpal
            ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip;  // proximal
            ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip;  // distal
            ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip;  // fingertip
            
           // ofSetColor(0, 255, 0);
         ofDrawSphere(mcp.x, mcp.y, mcp.z, 12);
            ofDrawSphere(pip.x, pip.y, pip.z, 10);
            ofDrawSphere(dip.x, dip.y, dip.z, 10);
            ofDrawSphere(tip.x, tip.y, tip.z, 6);
            
            //ofSetColor(255, 0, 0);
            ofSetLineWidth(23);
            ofDrawLine(mcp.x, mcp.y, mcp.z, pip.x, pip.y, pip.z);
             ofSetLineWidth(18);
            ofDrawLine(pip.x, pip.y, pip.z, dip.x, dip.y, dip.z);
            ofSetLineWidth(18);
            ofDrawLine(dip.x, dip.y, dip.z, tip.x, tip.y, tip.z);
        }
    }
   
    
    cam.end();
    
    //words
    ofPushMatrix();
    ofSetColor (color01);
     ofDrawBitmapString("Architecture of Light", 31, 92);
    ofSetColor(0);
    ofDrawBitmapString ("Put your hand over the leapmotion to turn the effects on...", 30, ofGetHeight()-60);

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        reloadCameras();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}

