#include "Button.h"
#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "common.h"

class Scene{

public:
   
    void setup();
    void calculate();
    void draw();
    void reset();
    
    // usefull things to have in a scene
    map<int,Button> *buttons;
    ofxTrueTypeFontUC * font_small;
    ofxTrueTypeFontUC * font_medium;
    ofxTrueTypeFontUC * font_large;
    commonFunctions * cc;
    
    
    // example
    vector<int>values; // for storing button answers according to rotation value
    vector<bool>b_on; // for storing on_off info when time runs out.
    int majority; // winning team
    bool done;
    double timer;
    float textopactity;
    float rectOpacity;
    float rectOpacityTimer;

    
};
