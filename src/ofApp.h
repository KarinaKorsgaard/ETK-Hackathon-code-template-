#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Button.h"
#include "Scene.h"
#include "ofxTrueTypeFontUC.h"
#include "common.h"

#define PORT 5000
#define NUM_TABLES 12
#define BUTTONS_PR_TABLE 6

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    

    ofFbo fbo;
    commonFunctions cc;
    map< int , Button > buttons;
    string getAdress(int firstOrSecond, int _table, int _button);
	ofxTrueTypeFontUC font_x_small;
    ofxTrueTypeFontUC font_small;
    ofxTrueTypeFontUC font_medium;
    ofxTrueTypeFontUC font_large;
    bool debug = false;
    ofxOscReceiver receiver;
    
    
    
    Scene scene;
};


