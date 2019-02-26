#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    mVidGrabber.setVerbose(true);
    mVidGrabber.setup(160,120);
    
    gui.setup();
    gui.add(endTime.set("End Time", 1000.0, 0.0, 6000.0));
    filterShow = false;
    timerEnd = false;
    startTime =ofGetElapsedTimeMillis();
    
    //image
    img.load ("color.jpg");
    
    img02.load ("blue2.png");
    img03.load ("bluet2.png");
    
    //videos
    vid.load ("vcar.mp4");
    carPlay = false;
    
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    mVidGrabber.update();

    if(mVidGrabber.isFrameNew()){
      
        //		ofLogNotice() << "frame new" << endl;
     //grab pixels
        ofPixels pixels = mVidGrabber.getPixels();
        
        for (int y = 0; y<pixels.getHeight();y++){
            for (int x = 0; x<pixels.getWidth(); x++){
                if (pixels.getColor (x,y).getBrightness()>128){
                    pixels.setColor(x,y,ofColor(255,255,255));
                }
                else {
                    pixels.setColor(x,y,ofColor(0,0,0));
                }
                
            }
            
            texture.loadData(pixels);
            }
    
    
    
     
    }
}

//--------------------------------------------------------------
void ofApp::draw(){


    ofSetHexColor(0xffffff);
    //	ofLogNotice() << ofGetFrameRate() << endl;
    
    int pattern_width=160;
    int pattern_height=120;
    if (filterShow ==false){
    for(int i = 0; i < ofGetScreenHeight(); i += pattern_height){
        for(int j = 0; j < ofGetScreenWidth(); j += pattern_width){
            mVidGrabber.draw(j, i, pattern_width, pattern_height);
        }
    }//for loop ends
        
    }
//webcam blackwhite filter
    if (filterShow==true){
        texture.draw(ofGetWidth()/2-100,ofGetHeight()/2-100);
        
    }
    
    //set up timer and change the time by clicking on timeBar on screen
    gui.draw();
    float barWidth = 600;
    float timer = ofGetElapsedTimeMillis()-startTime;
    
    if (timer >= endTime){
        timerEnd = true;
    }
    
    float timerBar = ofMap(timer, 0.0, endTime, 0.0,  1.0, true );
    
    if (timer >= 5000 ) {
      
        img.drawSubsection(300, 0, 100, 100, mouseX, mouseY, 50, 50);
    }
    
    if (timer >=5500){
         img.drawSubsection(600, 0, 100, 100, mouseX, mouseY, 50, 50);
    }
    if (timer >=6000){
         img.drawSubsection(900, 0, 100, 100, mouseX, mouseY, 50, 50);
    }
    if (timer >=6500){
        img.drawSubsection(900, 200, 100, 100, mouseX, mouseY, 50, 50);
    }
    if (timer >=7000){
        img.drawSubsection(600, 200, 100, 100, mouseX, mouseY, 50, 50);
    
    }
    if (timer >=7500){
        img.drawSubsection(300, 200, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (timer >=8000){
        img.drawSubsection(300, 400, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    if (timer >=8500){
        img.drawSubsection(600, 400, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (timer >=9000){
        img.drawSubsection(900, 400, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (timer >=9500){
        img.drawSubsection(900, 600, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (timer >=10000){
        img.drawSubsection(600, 600, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (timer >=10500){
        img.drawSubsection(300, 600, 100, 100, mouseX, mouseY, 50, 50);
        
    }
    
    if (carPlay == true){
    
    vid.play();
    vid.update();
    if (vid.isLoaded()){
       
        //aspect ratio is the proportional relationship between width and height
        float aspectRatio = vid.getWidth() / vid.getHeight();
        vid.draw(0.0f, 0.0f, ofGetWidth(), ofGetWidth() / aspectRatio);
        
    }
    }

   
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        timerEnd = false;
        startTime = ofGetElapsedTimeMillis();
    }
    if (key== 'q'){
        filterShow = true;
        
    }
    if (key=='w'){
        filterShow = false;
    }
    if (key=='a'){
        carPlay= true;
        
    }
    if (key=='s'){
        carPlay= false;
        
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
