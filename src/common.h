//
//  common.h
//  ETK_2017
//
//  Created by Karina Jensen on 14/01/17.
//
//

#ifndef common_h
#define common_h

#define PORT 5000
#define NUM_TABLES 12
#define BUTTONS_PR_TABLE 6

#include "Poco/TextConverter.h"
#include "Poco/TextEncoding.h"
#include "Poco/Unicode.h"
#include "Poco/UTF8String.h"
#include "Poco/String.h"

# include "ofxTrueTypeFontUC.h"
# include "Button.h"

struct commonObjects{
    bool lock;
    bool start;
    
    map<int,Button> *buttons;
    ofxTrueTypeFontUC * font_small;
    ofxTrueTypeFontUC * font_medium;
    ofxTrueTypeFontUC * font_large;
};

class commonFunctions{
public:
    float ease(float t, float b, float c, float d) {
        c -=b;
        t /= d;
        return c*t*t + b;
    }
    string timeToString(double time){
        time = floorf(time);
        if(time<0)time = 0;
        
        string timeString = "";
        int min = time / 60 ;
        int sec = time - min*60;
        
        timeString = ofToString(min,2,'0')+":";
        timeString.append(ofToString(sec,2,'0'));
        
        return timeString;
    }
    
    void drawCollumn(string str, int x, int y, int w, ofxTrueTypeFontUC * font ){
        ofPushMatrix();
        ofTranslate(x,y);
        string appending="";
        for(int i = 0; i<str.length();i++){
            string c = str.substr(i, 1);
            if (c == "\303") {
                c = str.substr(i, 2);
                i++;
            }
            appending.append(c);
            if(font->getStringBoundingBox(appending, 0, 0).width > w && ( c == " " || c == "-") ){
                font->drawString(appending, 0, 0);
                ofTranslate(0, font->getLineHeight());
                appending.clear();
            }
        }
        font->drawString(appending, 0, 0);
        ofPopMatrix();
    }
    
    
    string encode(string input, const string& inputEncoding, const string& outputEncoding) {
        Poco::TextEncoding::Ptr ie = Poco::TextEncoding::find(inputEncoding);
        Poco::TextEncoding::Ptr oe = Poco::TextEncoding::find(outputEncoding);
        Poco::TextConverter converter(*ie, *oe);
        string output;
        converter.convert(input, output);
        return output;
    }
    
    void drawGridLetters(int t, int b, ofxTrueTypeFontUC * f){
        for(int i = 0 ; i<t; i++){
            //return ofPoint(table * 70 + int(table/4)*20 + (1920 -( 70*12+20*3 + 70) ), row * 70 + 70);
            ofPushMatrix();
            ofTranslate(i * 70 + int(i/4)*20 + (1920 -( 70*12+20*3 + 70) ) - f->getStringBoundingBox(ofToString(i+1), 0, 0).width/2 , f->getLineHeight() + 30);
            f->drawString(ofToString(i+1),0,0);
            ofPopMatrix();
            
        }
        vector<string>letters = {"A","B","C","D","E","F"};
        for(int i = 0 ; i<b; i++){
            //return ofPoint(table * 70 + int(table/4)*20 + (1920 -( 70*12+20*3 + 70) ), row * 70 + 70);
            ofPushMatrix();
            ofTranslate((1920 -( 70*12+20*3 + 70) ) - 90 , i * 70 + 140  + (70-f->getLineHeight())/2 );
            f->drawString(letters[i],0,0);
            ofPopMatrix();  
        }
    }
    
    void drawGrid(int t, int b, map<int,Button>*buttons){
        ofPushStyle();
        ofSetLineWidth(4);
        ofSetColor(255);
        ofNoFill();
        for(auto b: *buttons){
            ofPushMatrix();
            ofTranslate(b.second.getGridPos());
            ofDrawRectangle(-35,-35,70,70);
            
            ofPopMatrix();
        }
        ofPopStyle();
    }

};


#endif /* common_h */
