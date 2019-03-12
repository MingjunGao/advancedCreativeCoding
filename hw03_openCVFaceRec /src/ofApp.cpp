//Assignment 03: openCV, webCam
//Due: March 12, 2019
//Mingjun Gao, Chaoyue Huang & Fangzhou Guo

#include "ofApp.h"

using namespace ofxCv;
using namespace cv;



//===================================================================
// Used to extract eye rectangles. from ProCamToolkit
GLdouble modelviewMatrix[16], projectionMatrix[16];
GLint viewport[4];
void updateProjectionState() {
	glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
}

glm::vec3 ofWorldToScreen(glm::vec3 world) {
	updateProjectionState();
    glm::vec3 screen = glm::project(glm::dvec3(world),
                                    glm::make_mat4(modelviewMatrix),
                                    glm::make_mat4(projectionMatrix),
                                    glm::make_vec4(viewport));
    screen.y = ofGetHeight() - screen.y;
	return screen;
}

ofMesh getProjectedMesh(const ofMesh& mesh) {
	ofMesh projected = mesh;
    for(std::size_t i = 0; i < mesh.getNumVertices(); i++) {
		glm::vec3 cur = ofWorldToScreen(mesh.getVerticesPointer()[i]);
		cur.z = 0;
		projected.setVertex(i, cur);
	}
	return projected;
}

template <class T>
void addTexCoords(ofMesh& to, const std::vector<T>& from) {
    for(std::size_t i = 0; i < from.size(); i++) {
        to.addTexCoord(glm::vec2(from[i].x, from[i].y));
	}
}


//===================================================================
using namespace ofxCv;

void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    cam.setVerbose(true);
    cam.setup(1280, 720);

	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    
    
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    
    //gui of setting threshold
    gui1.setup();
    gui1.add(threshold.set("Color Threshold", 30, 0, 255));
    threshold = 20;
    //import audio files
    crash.load("crash.mp3");
    bass.load("kick-bass.mp3");
    snare.load("snare.mp3");
    tom1.load("tom-1.mp3");
    tom2.load("tom-2.mp3");
    tom3.load("tom-3.mp3");
    tom4.load("tom-4.mp3");
    
    //blink
    snare1.load("yep.mp3");
    
   cam.initGrabber(1280, 720);
    //cam.setVerbose(true);
   // cam.setup(, 480);
	
	// Set up images we'll use for frame-differencing
	camImage.allocate(0, 0, OF_IMAGE_COLOR);
	eyeImageColor.allocate(128, 48);
	eyeImageGray.allocate(128,48);
	eyeImageGrayPrev.allocate(128,48);
	eyeImageGrayDif.allocate(128,48);
	eyeFbo.allocate(128, 48, GL_RGB);
	
	// Initialize our images to black.
	eyeImageColor.set(0);
	eyeImageGray.set(0);
	eyeImageGrayPrev.set(0);
	eyeImageGrayDif.set(0);

	// Set up other objects.
	tracker.setup();
	osc.setup("localhost", 8338);
	
	// This GUI slider adjusts the sensitivity of the blink detector.
	gui.setup();
	gui.add(percentileThreshold.setup("Blink Threshold", 0.92, 0.75, 1.0));
    
  
  
    
    
}

void ofApp::update() {
     cam.update();
	if(cam.isFrameNew()) {
		camImage.setFromPixels(cam.getPixels());
        
        contourFinder.setTargetColor(targetColor, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB); //find target color
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
        
        
        
		tracker.update(toCv(cam));
		position = tracker.getPosition();
		scale = tracker.getScale();
		rotationMatrix = tracker.getRotationMatrix();
        
        
        
		if(tracker.getFound()) {
			glm::vec2
			leftOuter = tracker.getImagePoint(36),
			leftInner = tracker.getImagePoint(39),
			rightInner = tracker.getImagePoint(42),
			rightOuter = tracker.getImagePoint(45);

			ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
			ofPolyline rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);

            glm::vec2 leftCenter = leftEye.getBoundingBox().getCenter();
            glm::vec2 rightCenter = rightEye.getBoundingBox().getCenter();

            float leftRadius = (glm::distance(leftCenter, leftInner) + glm::distance(leftCenter, leftOuter)) / 2;
            float rightRadius = (glm::distance(rightCenter, rightInner) + glm::distance(rightCenter, rightOuter)) / 2;

			glm::vec3
			leftOuterObj = tracker.getObjectPoint(36),
			leftInnerObj = tracker.getObjectPoint(39),
			rightInnerObj = tracker.getObjectPoint(42),
			rightOuterObj = tracker.getObjectPoint(45);

			glm::vec3 upperBorder(0, -3.5, 0), lowerBorder(0, 2.5, 0);
			glm::vec3 leftDirection(-1, 0, 0), rightDirection(+1, 0, 0);
			float innerBorder = 1.5, outerBorder = 2.5;

			ofMesh leftRect, rightRect;
			leftRect.setMode(OF_PRIMITIVE_LINE_LOOP);
			leftRect.addVertex(leftOuterObj + upperBorder + leftDirection * outerBorder);
			leftRect.addVertex(leftInnerObj + upperBorder + rightDirection * innerBorder);
			leftRect.addVertex(leftInnerObj + lowerBorder + rightDirection * innerBorder);
			leftRect.addVertex(leftOuterObj + lowerBorder + leftDirection * outerBorder);
			rightRect.setMode(OF_PRIMITIVE_LINE_LOOP);
			rightRect.addVertex(rightInnerObj+ upperBorder + leftDirection * innerBorder);
			rightRect.addVertex(rightOuterObj + upperBorder + rightDirection * outerBorder);
			rightRect.addVertex(rightOuterObj + lowerBorder + rightDirection * outerBorder);
			rightRect.addVertex(rightInnerObj + lowerBorder + leftDirection * innerBorder);

			ofPushMatrix();
			ofSetupScreenOrtho(640, 480, -1000, 1000);
			ofScale(1, 1, -1);
			ofTranslate(position);
			applyMatrix(rotationMatrix);
			ofScale(scale, scale, scale);
			leftRectImg = getProjectedMesh(leftRect);
			rightRectImg = getProjectedMesh(rightRect);
			ofPopMatrix();

			// more effective than using object space points would be to use image space
			// but translate to the center of the eye and orient the rectangle in the
			// direction the face is facing.
			/*
			 ofPushMatrix();
			 ofTranslate(tracker.getImageFeature(ofxFaceTracker::LEFT_EYE).getCentroid2D());
			 applyMatrix(rotationMatrix);
			 ofRect(-50, -40, 2*50, 2*40);
			 ofPopMatrix();

			 ofPushMatrix();
			 ofTranslate(tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE).getCentroid2D());
			 applyMatrix(rotationMatrix);
			 ofRect(-50, -40, 2*50, 2*40);
			 ofPopMatrix();
			 */

			ofMesh normRect, normLeft, normRight;
			normRect.addVertex(glm::vec3(0, 0, 0));
			normRect.addVertex(glm::vec3(64, 0, 0));
			normRect.addVertex(glm::vec3(64, 48, 0));
			normRect.addVertex(glm::vec3(0, 48, 0));
			normLeft.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			normRight.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			normLeft.addVertices(normRect.getVertices());
			normRight.addVertices(normRect.getVertices());
			addTexCoords(normLeft, leftRectImg.getVertices());
			addTexCoords(normRight, rightRectImg.getVertices());

			// Copy the extracted quadrilaterals into the eyeFbo
			eyeFbo.begin();
			ofSetColor(255);
			ofFill();
			cam.getTexture().bind();
			normLeft.draw();
			ofTranslate(64, 0);
			normRight.draw();
			cam.getTexture().unbind();
			eyeFbo.end();
			eyeFbo.readToPixels(eyePixels);
			
			// Convert the combined eye-image to grayscale,
			// and put its data into a frame-differencer.
			eyeImageColor.setFromPixels(eyePixels);
			eyeImageGrayPrev.setFromPixels(eyeImageGray.getPixels());
			eyeImageGray.setFromColorImage(eyeImageColor);
			eyeImageGray.contrastStretch();
			eyeImageGrayDif.absDiff(eyeImageGrayPrev, eyeImageGray);
			
			// Compute the average brightness of the difference image.
			unsigned char* difPixels = eyeImageGrayDif.getPixels().getData();
			int nPixels = 128*48;
			float sum = 0;
			for (int i=0; i<nPixels; i++){
				if (difPixels[i] > 4){ // don't consider diffs less than 4 gray levels;
					sum += difPixels[i]; // reduces noise
				}
			}
			// Store the current average in the row graph
			float avg = sum / (float) nPixels;
			rowGraph.addSample(avg, percentileThreshold);

			// Send out an OSC message,
			// With the value 1 if the current average is above threshold
			ofxOscMessage msg;
			msg.setAddress("/gesture/blink");
			int oscMsgInt = (rowGraph.getState() ? 1 : 0);
            //event blick occurs
			msg.addIntArg(oscMsgInt);
			osc.sendMessage(msg);
			
            
            
            
            
			// Print out a message to the console if there was a blink.
            //make a sound when was a blink
			if (oscMsgInt > 0){
            
                
                
                
                
                
                
				printf("Blink happened at frame #:	%d\n", (int)ofGetFrameNum());
                
                snare1.play();
               
                
                
			}
		
		}
	}
}

void ofApp::draw() {
    

   
   //ofPushMatrix();
	camImage.draw(0, 0, 1280,720);
   // camImage.draw(camImage.getWidth(),0,-camImage.getWidth(),camImage.getHeight());
    //ofPopMatrix();
    
    ofSetLineWidth(3);
    
    //draw the first rect
    ofSetColor(220, 56, 51);
    ofDrawRectangle(800, 200, 200, 200);
    //draw the first black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 200, 200, 20);
    //draw the second rect
    ofSetColor(250, 222, 79);
    ofDrawRectangle(0, 220, 200, 200);
    //draw the second black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 420, 200, 20);
    //draw the third rect
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 440, 200, 280);
    //draw the third black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(200, 620, 20, 100);
    //draw the fourth rect
    ofSetColor(54, 70, 116);
    ofDrawRectangle(220, 620, 200, 100);
    //draw the fourth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(420, 620, 20, 100);
    //draw the fifth rect
    ofSetColor(255, 255, 255);
    ofDrawRectangle(440, 620, 220, 100);
    //draw the fifth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(640, 620, 20, 100);
    //draw the sixth rect
    ofSetColor(0, 0, 0);
    ofDrawRectangle(660, 620, 200, 100);
    //draw the sixth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(860, 620, 20, 100);
    //draw the seventh rect
    ofSetColor(250, 222, 79);
    ofDrawRectangle(880, 620, 200, 100);
    
     ofSetColor(255);
    tracker.draw();
    
    
   
    leftRectImg.draw();
    rightRectImg.draw();

	
	float y = 58;
    
    //ofPushMatrix();
   // ofTranslate(700, 0);
   // gui1.draw(); //draw gui
    //ofPopMatrix();
    
	gui.draw();
    
    
	eyeImageGray.draw(10, y);    y+=58;
	eyeImageGrayDif.draw(10, y); y+=58;
	rowGraph.draw(10, y, 48);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, ofGetHeight() - 20);
    
    
    int n = contourFinder.size();
    for(int i = 0; i < n; i++) {
        cv::RotatedRect ellipse = contourFinder.getFitEllipse(i);
        ofPushMatrix();
        ofVec2f ellipseCenter = toOf(ellipse.center);
        ofTranslate(ellipseCenter.x, ellipseCenter.y);
        ofSetColor(255, 255, 255);
        ofDrawEllipse(0, 0, 20, 20);
        ofPopMatrix();
        
        if ( ellipseCenter.x > 800 && ellipseCenter.x < 1000 &&  ellipseCenter.y > 200 &&  ellipseCenter.y < 400) {
            crash.play();
            ofSetColor(180, 56, 51);
            ofDrawRectangle(800, 200, 220, 220);
            
        }
        if ( ellipseCenter.x > 0 && ellipseCenter.x < 200 &&  ellipseCenter.y > 220 &&  ellipseCenter.y < 420) {
            bass.play();
            ofSetColor(210, 220, 59);
            ofDrawRectangle(0, 220, 220, 200);
            
        }
        if ( ellipseCenter.x > 0 && ellipseCenter.x < 200 &&  ellipseCenter.y > 440 &&  ellipseCenter.y < 640) {
            snare.play();
            ofSetColor(200, 200, 200);
            ofDrawRectangle(0, 440, 220, 280);
            
        }
        if ( ellipseCenter.x > 200 && ellipseCenter.x < 400 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom1.play();
            ofSetColor(34, 50, 96);
            ofDrawRectangle(220, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 420 && ellipseCenter.x < 640 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom2.play();
            ofSetColor(205, 205, 205);
            ofDrawRectangle(440, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 660 && ellipseCenter.x < 860 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom3.play();
            ofSetColor(20, 20, 20);
            ofDrawRectangle(660, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 880 && ellipseCenter.x < 1080 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom4.play();
            ofSetColor(210, 220, 59);
            ofDrawRectangle(880, 600, 200, 120);
            
        }
    }
    
    
    
}



void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    targetColor = cam.getPixels().getColor(x, y);
    //ofLogNotice() << targetColor << endl;
}

