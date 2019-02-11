#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxSTL.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
   

    //ofMesh
    ofVboMesh mesh,jcl,jcr,backgrip,save;
    
    vector<ofVec3f> gripvertex;
    vector<ofVec3f> jcrvertex;
    vector<ofVec3f> jclvertex;
    vector<ofVec3f> bgripvertex;

    vector<int> gpointnumm;
    vector<int> gpointnump;
    vector<int> bgpointnumm;
    vector<int> bgpointnump;

    
    ofVec3f gripmove;
    
    string date;
    bool saved;
    
    // Camera
    ofEasyCam camera;
    
    // Gui
    ofxImGui::Gui gui;
    bool imGui();
    bool guiVisible;
    bool mouseOverGui;
    
    
    //parameters
    float camzoom;
    float fgsize;
   
    
    ofParameter<bool> wireframes{ "Wirefarmes", false };
    ofParameter<bool> faces{ "Faces", true };
    ofParameter<bool> vertices{ "Vertices", true };
    ofParameter<float> cdistance{ "(x) Zoom", 1, 1, 4};
    ofParameter<bool> jc{"JC", true};
    ofParameterGroup view{ "View", wireframes,faces, vertices , cdistance,jc};
    
    ofParameter<float> gsize{ "(mm) Size", 30, 18, 118};
    ofParameter<bool> bgrip{ "Back Grip", false };
    ofParameter<int> bgrippos{ "Position ", 200, 200, 400};
    ofParameterGroup model{ "Model",gsize,bgrip,bgrippos };
    
    vector<string> labels = { "None", "Grip01", "Grip02" };
    
    ofParameter<int> dummy{ "For Test", 289, 289, 322};
    ofParameterGroup gene{"Generator", dummy};
    
    
};
