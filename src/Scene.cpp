#include "Scene.h"

void Scene::setup(){
    values.resize(buttons->size());
    b_on.resize(buttons->size());
    reset();
}

void Scene::calculate(){

    timer-=ofGetLastFrameTime();
    
    if(timer < 3 && !done) textopactity = cc->ease( (3 - timer) , 255 , 0 , 3 );
    if(timer < 0 ) {
        done = true;
        if(textopactity < 255)
            textopactity = cc->ease(-timer, 0 , 255 , 1 );
        cc->setLockButtons(true);
    }
    
    if(!done){
        int a(0),b(0);
        for(int i=0; i<buttons->size(); i++){
            
            values[i] = int(floorf( ofMap(buttons->find(i)->second.r, 0, 2*PI, 0, 2)));
            
            if(values[i]==0)a++;
            else if(values[i]==1)b++;
            
            
        }
        int max = MAX(a,b);
        int p_majority = majority;
        majority = max == a ? 0 : 1;
        if(p_majority!=majority){
            rectOpacityTimer=ofGetElapsedTimef();
            rectOpacity = 0;
        }
        if(rectOpacity<255)rectOpacity = cc->ease(ofGetElapsedTimef()-rectOpacityTimer, 0, 255, 1);
    }
}


void Scene::draw(){
    
    for(int i=0; i<buttons->size(); i++){
        Button b = buttons->find(i)->second;
        if(b.on){
            ofSetLineWidth(4);
            ofFill();
            
            ofPushMatrix();
            //ofTranslate(b.getPos());
            ofTranslate( b.getGridPos()) ;
            
            if(values[i]==0)
                ofSetColor(ofColor::royalBlue);
            else ofSetColor(ofColor::orangeRed);
            ofDrawRectangle(-35,-35,70,70);

            ofNoFill();
            ofSetColor(255);
            ofDrawRectangle(-35,-35,70,70);
            ofFill();
            
            if(values[i]==majority){
                ofRotateZ(ofRadToDeg(b.r));
                
                if(values[i]==0)ofSetColor(ofColor::aquamarine , rectOpacity);
                else ofSetColor(ofColor::blanchedAlmond, rectOpacity);
                
                ofDrawRectangle(-20, -20, 40, 40);
            
            }
            ofPopMatrix();
        }
    }
    
    
    ofSetColor(255);
    int line_y = font_large->getLineHeight() ;
    font_large->drawString(cc->timeToString(timer) , 70, line_y);
    line_y += font_medium->getLineHeight() ;
    
    ofSetColor(255 , textopactity);
    if(!done)
        cc->drawCollumn("Double squares have the majority and you can write õ ö ä and all the other weird letters you estonians have :)", 70, line_y, 400, font_small);
    else {
        string winner = majority==0 ? "blues" : "reds";
        cc->drawCollumn("The "+ winner +" have won!", 70, line_y + 60 , 400, font_medium);
    }
    
}

void Scene::reset(){
    timer = 10;
    done = false;
    textopactity=255;
    cc->setLockButtons(false);
}

