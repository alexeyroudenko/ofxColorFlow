#pragma once

#include "ofMain.h"
#include "ofxColorFlow.h"

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);
    
    ofImage image;
    ofxColorFlow            colorFlow;
    ofParameter<bool>       doDrawDebug;
    
};
