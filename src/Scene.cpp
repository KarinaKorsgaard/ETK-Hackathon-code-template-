#include "Scene.h"

void Scene::setup(commonObjects*_co){
    co = _co;
    values.resize(co->buttons->size());
    b_on.resize(co->buttons->size());
    reset();
}

void Scene::calculate(){

    // example:
    if(co->start)timer-=ofGetLastFrameTime();
    
    if(timer < 3 && !done) textopactity = ease( (3 - timer) , 255 , 0 , 3 );
    if(timer < 0 ) {
        done = true;
        if(textopactity < 255)
            textopactity = ease(-timer, 0 , 255 , 1 );
        co->lock=true; // sets the common bool to lock button values.
    }
    
    if(!done){
        int a(0),b(0);
        for(int i=0; i<co->buttons->size(); i++){
            
            values[i] = int(floorf( ofMap(co->buttons->find(i)->second.r, 0, 2*PI, 0, 2)));
            
            if(values[i]==0)a++;
            else if(values[i]==1)b++;
            
            
        }
        int max = MAX(a,b);
        int p_majority = majority;
        majority = max == a ? 0 : 1;
        if(a==b)majority = -1;
        if(p_majority!=majority){
            rectOpacityTimer=ofGetElapsedTimef();
            rectOpacity = 0;
        }
        
    }
    if(rectOpacity<255)rectOpacity = ease(ofGetElapsedTimef()-rectOpacityTimer, 0, 255, 1);
    // - example
}


void Scene::draw(){
    

    // example
    for(int i=0; i<co->buttons->size(); i++){
        Button b = co->buttons->find(i)->second;
        if(b.on){
            ofFill();
            
            ofPushMatrix();
            //ofTranslate(b.getPos());
            ofTranslate( b.getGridPos()) ; // buttons are placed in a matrix [table x buttonID]
            
            if(values[i]==0)
                ofSetColor(ofColor::royalBlue);
            else ofSetColor(ofColor::orangeRed);
            ofDrawRectangle(-35,-35,70,70);

            
            if(values[i]==majority){
                ofRotateZ(ofRadToDeg(b.r));
                
                if(values[i]==0)ofSetColor(ofColor::aquamarine , rectOpacity);
                else ofSetColor(ofColor::blanchedAlmond, rectOpacity);
                
                ofDrawRectangle(-20, -20, 40, 40);
            
            }
            
            ofPopMatrix();
        }
    }
    
    // draw explaining texts
    ofSetColor(255);
    int line_y = co->font_large->getLineHeight() ;
    co->font_large->drawString(timeToString(timer) , 70, line_y);
    line_y += co->font_medium->getLineHeight() ;
    ofPushStyle();
    ofSetColor(255 , textopactity);
    if(!done)
        drawCollumn("Double squares have the majority and you can write õ ö ä and all the other weird letters you estonians have :)", 70, line_y, 400, co->font_small);
    else {
        string winner = majority==0 ? "The blues have won!" : "The reds have won!";
        if(majority==-1)winner="No one won";
        drawCollumn(winner, 70, line_y + 60 , 400, co->font_medium);
    }
    ofPopStyle();
    
    drawGrid(NUM_TABLES, BUTTONS_PR_TABLE, co->buttons);
    drawGridLetters(NUM_TABLES, BUTTONS_PR_TABLE, co->font_small);
    // -- example
}

void Scene::reset(){
    timer = 5;
    done = false;
    textopactity=255;
}

