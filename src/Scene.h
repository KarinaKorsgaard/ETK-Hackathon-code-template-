#include "ofMain.h"
#include "common.h"

class Scene:public commonFunctions{

public:
   
    void setup(commonObjects*_co);
    void calculate();
    void draw();
    void reset();
    
    commonObjects * co;
    
    
    
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
