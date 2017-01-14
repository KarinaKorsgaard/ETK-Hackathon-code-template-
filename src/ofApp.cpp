#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    receiver.setup(PORT);
    
    // set up buttons
    int indx = 0;
    for(int i =0; i < NUM_TABLES; i++){
        for(int j = 0; j<BUTTONS_PR_TABLE;j++){
            
            Button b = *new Button;
            b.setup(j,i, getAdress(0, i, j), getAdress(1, i, j));
            b.set(ofRandom(1),ofRandom(1),ofRandom(2*PI));
            buttons[indx] = b;
            indx++;
            
        }
    }
    
    //setup scene
    
    font_x_small.load("fonts/GT.ttf", 20);
    font_small.load("fonts/GT.ttf", 30);
    font_medium.load("fonts/GT.ttf", 65);
    font_large.load("fonts/GT.ttf", 140);
    
    scene.buttons = &buttons;
    scene.font_small = &font_small;
    scene.font_medium = &font_medium;
    scene.font_large = &font_large;
    scene.cc = &cc;
    
    scene.setup();
    
    //allocate framebuffer
    fbo.allocate(1920, 1080, GL_RGBA);
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(debug)ofSetWindowTitle("framerate: "+ofToString(ofGetFrameRate(),1));

    // update from incoming osc
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        // set button values
        if(!cc.lock){
            for(int i = 0; i < NUM_TABLES*BUTTONS_PR_TABLE; i++){
                Button *b = &buttons.find(i)->second;
                if( m.getAddress()==b->address ){
                    b->set(m.getArgAsFloat(0)/127.0f, m.getArgAsFloat(1)/127.0f, m.getArgAsFloat(2));
                }
                if (m.getAddress()==b->secondAdress){
                    if(m.getArgAsInt32(0)==1)
                        b->on = true;
                    else b->on = false;
                }
            }
        }
    }
    
    //update scene values
    scene.calculate();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofClear(0);
    ofBackground(0);
    
    ofSetColor(ofColor::white);
    cc.drawCollumn("press d to draw all buttons at they positions", 70, 1000, 500, &font_x_small);
    if(debug)for (auto& b : buttons)b.second.drawDebug();

    scene.draw();
    fbo.end();
    
    fbo.draw(0,0, ofGetWidth(), 1080.0f * (ofGetWidth() / 1920.0f) );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'd') debug = !debug;
    if(key == 'r') scene.reset();
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
//--------------------------------------------------------------
string ofApp:: getAdress(int _firstSecond, int _tabel, int _button){
    ofFile file;
    file.open(ofToDataPath("oscAdresses.txt"));
    ofBuffer b = file.readToBuffer();
    string result = "";
    int indx = 0;
    
    
    for (auto line : b.getLines()) {
        string str = line;
#ifdef TARGET_WIN32
        str = cc.encode(str, "UTF-8", "Windows-1252");
#endif
        if(indx == _tabel){
            result = str;
            if(_firstSecond == 1)
                result.append("/switch");
        }
        if(indx == 12+_button && _firstSecond == 0)
            result.append(str);
        if(indx == 12+6+_button && _firstSecond == 1)
            result.append(str);
        indx++;
    }
    ofLog() << result <<endl;
    return result;
}
