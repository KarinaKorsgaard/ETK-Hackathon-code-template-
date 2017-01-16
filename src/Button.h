//
//  Button.h
//  ETK_2017
//
//  Created by Karina Jensen on 10/01/17.
//
//

#ifndef Button_h
#define Button_h


#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"


class Button{
public:
    void setup(int _row, int _table, string _address, string _secondAdress){
        row = _row;
        table = _table;
        address = _address;
        secondAdress = _secondAdress;
    }
    
    void drawDebug(){

        ofPushMatrix();
        ofTranslate(x * 1920, y * 1080);
        ofRotateZ(ofRadToDeg(r));
        if(on)ofSetColor(ofColor::royalBlue , 150);
        else ofSetColor(ofColor::orangeRed , 150);
        ofDrawCircle(0, 0, 25);
        ofSetColor(ofColor::white);
        ofDrawLine(0, 0, 25, 0);
        ofDrawBitmapString(ofToString(table)+","+ofToString(row), 10, 10);
        ofPopMatrix();
    }

    void set(float _x, float _y, float _r){
        x=_x;
        y=_y;
        r=_r;
    }
    ofPoint getGridPos(){
        return ofPoint(table * 70 + int(table/4)*20 + (1920 -( 70*12+20*3 + 70) ), row * 70 + 140);
    }
    ofPoint getPos(){
        return ofPoint(x*1920.0f, y*1080.0f);
    }

    float r;
    float x;
    float y;
    
    int row;
    int table;
    int ID;
    
    string address;
    string secondAdress;
    
    bool on = false;
};

#endif /* Button_h */
