#pragma once

#include "ofMain.h"
#include "Tile.h"
#include "ofxOpenCv.h"
#include "ofxFFTLive.h"

class testApp : public ofBaseApp {
	public:
		void reset();
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofImage img;
		int maxSize;
		int generation;
		ofImageQualityType quality;
		int addX, addY, subX, subY;
		float glitchStart;
    
        vector<Tile> imgs;
    
        ofVideoGrabber 		vidGrabber;

        ofxCvColorImage			colorImg;
        ofxCvGrayscaleImage 	currentGrayImage;
        ofxCvGrayscaleImage 	previousGrayImage;
        ofxCvGrayscaleImage 	differenceGrayImage;
        ofxCvGrayscaleImage     scaledDifference;
        ofxCvContourFinder 	contourFinder;
        int 				threshold;
        bool				bLearnBakground;
        ofPixels grayPixels;
        unsigned char *hotPix;
        int pix;
        bool soundMode;
        bool debugMode;
        ofxFFTLive fftLive;
};
