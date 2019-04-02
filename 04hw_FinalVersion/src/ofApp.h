#pragma once

#include "ofMain.h"
#include "Ball.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		vector<shared_ptr<Ball>> balls;
    
        void audioOut( ofSoundBuffer &outBuffer );
        double phase;
        ofSoundStream soundStream;
    
        int sampleRate = 44100;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
		float     pan;
    vector <float> lAudio;
    vector <float> rAudio;
    
    float     volume;
    
    float generateSample(float phase, shared_ptr<Ball> ball);
    int waveTypeGenerator(ofVec2f ballPos);

};
