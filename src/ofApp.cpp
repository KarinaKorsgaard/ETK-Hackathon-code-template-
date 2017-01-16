#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    receiver.setup(PORT);
    
    // set up buttons
    int indx = 0;
    for(int i =0; i < NUM_TABLES; i++){
        for(int j = 0; j<BUTTONS_PR_TABLE;j++){
            
            Button b = * new Button;
            b.setup(j,i, getAdress(0, i, j), getAdress(1, i, j));
            b.set(ofRandom(1),ofRandom(1),ofRandom(2*PI));
            buttons[indx] = b;
            indx++;
            
        }
    }
    
    //load fonts
    font_x_small.load("fonts/GT.ttf", 20);
    font_small.load("fonts/GT.ttf", 30);
    font_medium.load("fonts/GT.ttf", 65);
    font_large.load("fonts/GT.ttf", 140);
    
    //set common objects to point at fonts and button map
    co.buttons = &buttons;
    co.font_small = &font_small;
    co.font_medium = &font_medium;
    co.font_large = &font_large;
    
    //setup scene
    scene.setup(&co);
    scene01.setup(&co);
    
    //allocate framebuffer
    fbo.allocate(1920, 1080, GL_RGBA);
    ofEnableAntiAliasing();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetWindowTitle("framerate: "+ofToString(ofGetFrameRate(),1));

    // update from incoming osc
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        // set button values
        if(!co.lock){
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
    if(sceneNumber==0)scene.calculate();
    if(sceneNumber==1)scene01.calculate();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofClear(0);
    ofBackground(0);
    


    if(sceneNumber==0)scene.draw();
    if(sceneNumber==1)scene01.draw();
    
    
    ofSetColor(ofColor::white);
    if(debug){
        for (auto& b : buttons)b.second.drawDebug();
        cc.drawCollumn("press 'd' to draw all buttons at they positions, 's' to start scene timer and 'r' to reset the scene. Press any number key to change scene- Current scene = "+ofToString(sceneNumber), 70, 950, 400, &font_x_small);
    }
    
    fbo.end();
    
    fbo.draw(0,0, ofGetWidth(), 1080.0f * (ofGetWidth() / 1920.0f) );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'd') debug = !debug;
    if(key == 'r') scene.reset();
    if(key == 's') co.start=true;
    
    if(key - '0' < 9) {
        co.start = false;
        co.lock = false;
        scene.reset();
        scene01.reset();
        sceneNumber = key - '0';
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
