#include "Scene01.h"

void Scene01::setup(commonObjects*_co){
    co = _co;
    reset();
}

void Scene01::calculate(){
    p.x+=vx*2;
    p.y+=vy*2;
    if(p.x>ofGetWidth() + 400|| p.x<0)vx*=-1;
    if(p.y>ofGetHeight() + 200|| p.y<0)vy*=-1;
}


void Scene01::draw(){
    drawCollumn("this is a new scene", p.x, p.y, 400, co->font_medium);
    
    drawGrid(NUM_TABLES, BUTTONS_PR_TABLE, co->buttons);
    drawGridLetters(NUM_TABLES, BUTTONS_PR_TABLE, co->font_small);
}

void Scene01::reset(){
    vx=1;
    vy=1;
    p.x=0;
    p.y=0;
}

