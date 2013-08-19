#include "testApp.h"


int curX  = 0;
int curY = 0;
int imgW;
int imgH;
int numImgsPerRow = 10;
int numImgsPerCol = 5;

//--------------------------------------------------------------
void testApp::setup() {
    ofBackground(0);
	quality = OF_IMAGE_QUALITY_WORST;
	maxSize = 2048;
	glitchStart = .05;
	reset();
    imgW=256;  //this should be calculated with aspect ratios from the source image and shit
    imgH=192;
    ofSetFrameRate(5);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(47,34);
    colorImg.allocate(47,34);
	currentGrayImage.allocate(47,34);
	previousGrayImage.allocate(47,34);
	differenceGrayImage.allocate(47,34);
	bLearnBakground = true;
	threshold = 80;
    soundMode = true;
    debugMode = false;
    fftLive.setMirrorData(false);
    fftLive.setup();
}

//--------------------------------------------------------------
void testApp::reset() {
	generation = 0;
	img.loadImage("buses.jpg");
	addX = ofRandom(0, 16);
	addY = ofRandom(0, 16);
	subX = ofRandom(0, addX);
	subY = ofRandom(0, addY);
}

//--------------------------------------------------------------
void testApp::update() {
	string curFilename = "compressed.jpg";
    bool bNewFrame = false;
    bool glitchMe = false;
    
    img.saveImage(curFilename, quality);
    fftLive.update();
    
    if(soundMode) {
        float soundLevel = fftLive.getAveragePeak();
        cout << soundLevel <<endl;
        
        if( soundLevel > 0.8) {
            glitchMe = true;
        }
    } else {
//        vidGrabber.grabFrame();
//
//        bNewFrame = vidGrabber.isFrameNew();
//        if (bNewFrame){
//            
//            colorImg.setFromPixels(vidGrabber.getPixels(), 47,34);
//            currentGrayImage = colorImg;
//            differenceGrayImage.absDiff(previousGrayImage, currentGrayImage);
//            differenceGrayImage.threshold(threshold);
//            previousGrayImage = currentGrayImage;
//            hotPix = differenceGrayImage.getPixels();
//            
//            for(int i=0; i<47; i++) {
//                for(int j=0; j<34; j++) {
//                    pix = hotPix[i*j];
//                    if(pix==255) {
//                        glitchMe=true;
//                        //break?
//                    }
//                }
//            }
//        }
    }
    
        if(glitchMe) {
            // this portion glitches the jpeg file
            // first loading the file (as binary)
            ofBuffer file = ofBufferFromFile(curFilename, true);
            int fileSize = file.size();
            char * buffer = file.getBinaryBuffer();

            // pick a byte offset that is somewhere near the end of the file
            int whichByte = (int) ofRandom(fileSize*glitchStart, fileSize);
            // and pick a bit in that byte to turn on
            int whichBit = ofRandom(8);
            char bitMask = 1 << whichBit;
            // using the OR operator |, if the bit isn't already on this will turn it on
            buffer[whichByte] |= bitMask;

            // write the file out like nothing happened
            ofBufferToFile(curFilename, file, true);
            img.loadImage(curFilename);
        } else {
            img.loadImage(curFilename);

            // this if switches every other frame
            // resizing up and down breaks the 8x8 JPEG blocks
            if(ofGetFrameNum() % 2 == 0) {
                // resize a little bigger
                img.resize(imgW + addX, imgW + addY);
            } else {
                // then resize a little smaller
                img.resize(imgW- subX, imgW - subY);
            }
        }

    Tile tile;
    tile.setup(img, curX, curY, imgW, imgH);
    imgs.push_back(tile);        

    if(curX > ofGetWidth() - imgW) {
        curX = 0;
        (curY > ofGetHeight() - imgH) ? curY=0 : curY+=imgH;
    } else {
        curX += imgW;
    }
}

//--------------------------------------------------------------
void testApp::draw() {

    for(int i=0; i<imgs.size(); i++) {
        imgs[i].draw();
    }
    
    if(debugMode) fftLive.draw(10, 30);
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

    if(key == 'd') {
        debugMode = !debugMode;
    }
    
    if(key == ' ') {
        soundMode = !soundMode;
    }
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	reset();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
