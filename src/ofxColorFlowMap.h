#pragma once

#include "ofMain.h"

class ofxColorFlowMap {
    
public:
    ofParameterGroup settings;
    ofParameter<bool>       doDrawToMap;
    ofParameter<float>       mapDrawSize;
    ofParameter<float>       mapPressure;
    ofShader drawFlowShader;
    ofFbo fbo;
    ofImage map;
    ofImage clearMapImage;
    
    void setup() {
        fbo.allocate(1280, 720, GL_RGBA);
        map.load("map.png");
        updateMap();
        
        clearMapImage.load("clear.png");
        
        updateMap();
        
        settings.setName("map");
        settings.add(doDrawToMap.set("doDrawToMap", false));
        settings.add(mapDrawSize.set("mapDrawSize", 0.5f, 0.0f, 2.0));
        settings.add(mapPressure.set("mapPressure", 0.5f, -1.0f, 1.0));
    }
    
    void update() {
        if (ofGetMousePressed() && doDrawToMap) {
            ofSetColor(255);
            float nposX = 1.0 * ofGetMouseX() / ofGetWidth();
            float nposY = 1.0 * ofGetMouseY() / ofGetHeight();
            float pressure = mapPressure;
            if (ofGetMousePressed(2) == true) pressure = -mapPressure;
            
            fbo.begin();
            drawFlowShader.begin();
            drawFlowShader.setUniform1f("size", mapDrawSize);
            drawFlowShader.setUniform1f("pressure", pressure);
            drawFlowShader.setUniform2f("mouse", nposX * fbo.getWidth(), nposY * fbo.getHeight());
            fbo.draw(0, 0, fbo.getWidth(), fbo.getHeight());
            drawFlowShader.end();
            fbo.end();
            //ofDrawCircle(nposX * fbo.getWidth(), nposY * fbo.getHeight(), 40);
        }
    }
    
    void clearMap() {
        ofEnableAlphaBlending();
        ofLogVerbose("[ofApp] clearMap");
        fbo.begin();
        clearMapImage.draw(0, 0, fbo.getWidth(), fbo.getHeight());
        fbo.end();
    }
    
    
    void updateMap() {
        ofEnableAlphaBlending();
        ofLogVerbose("[ofApp] updateMap");
        fbo.begin();
        map.draw(0, 0, fbo.getWidth(), fbo.getHeight());
        fbo.end();
    }

    
    void loadShaders() {
        drawFlowShader.load("", "shaders/flow/DrawFlow.frag");
    }
};
