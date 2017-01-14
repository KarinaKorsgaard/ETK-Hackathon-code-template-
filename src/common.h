//
//  common.h
//  ETK_2017
//
//  Created by Karina Jensen on 14/01/17.
//
//

#ifndef common_h
#define common_h

#include "Poco/TextConverter.h"
#include "Poco/TextEncoding.h"
#include "Poco/Unicode.h"
#include "Poco/UTF8String.h"
#include "Poco/String.h"

class commonFunctions{
public:
    bool lock;
    
    float ease(float t, float b, float c, float d) {
        c -=b;
        t /= d;
        return c*t*t + b;
    }
    
    string timeToString(double time){ // should write 1:30 for 1 min. not 90.
        if(time<0)time = 0;
        return ofToString(time,0);
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
    
    void setLockButtons(bool is){
        lock = is;
    }
    
    string encode(string input, const string& inputEncoding, const string& outputEncoding) {
        Poco::TextEncoding::Ptr ie = Poco::TextEncoding::find(inputEncoding);
        Poco::TextEncoding::Ptr oe = Poco::TextEncoding::find(outputEncoding);
        Poco::TextConverter converter(*ie, *oe);
        string output;
        converter.convert(input, output);
        return output;
    }
};


#endif /* common_h */
