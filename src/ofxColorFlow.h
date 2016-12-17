#pragma once

#include "ofMain.h"
#include "ofxColorFlowMap.h"

class ofxColorFlow {
    
public:
    ofParameterGroup settings;
    ofParameter<bool>       doShader;
    ofParameter<bool>       drawMap;
    ofParameter<float>       flowSpeed;
    ofParameter<float>       cycleTime;
    ofParameter<float>       drawSmallSize;
    ofParameter<float>       drawSize;

    ofxColorFlowMap flowMap;
    ofShader generateNormalMapShader;
    
    ofShader flowMapFrag;
    ofShader flowMapDirectionFrag;
    ofShader flowMapTimeCycleFrag;
    
    void setup();
    void update();
    void draw(ofImage *image);
    void loadShaders();
    void keyPressed(int key);
};
