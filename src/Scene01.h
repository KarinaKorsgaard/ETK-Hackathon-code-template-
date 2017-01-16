#include "ofMain.h"
#include "common.h"

class Scene01 : public commonFunctions{

public:
   
    void setup(commonObjects*_co);
    void calculate();
    void draw();
    void reset();
    
    commonObjects * co;
    ofPoint p;
    int vx = 1; int vy = 1;
    
};
