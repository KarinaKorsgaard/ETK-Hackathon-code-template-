#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "common.h"

#include "Scene.h"
#include "Scene01.h"

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
    commonObjects co;
    commonFunctions cc;
    
    string getAdress(int firstOrSecond, int _table, int _button);
    
    map< int , Button > buttons;
	ofxTrueTypeFontUC font_x_small;
    ofxTrueTypeFontUC font_small;
    ofxTrueTypeFontUC font_medium;
    ofxTrueTypeFontUC font_large;
    
    bool debug = false;
    ofxOscReceiver receiver;
    int sceneNumber=0;
    
    
    //scenes
    Scene scene;
    Scene01 scene01;

};


