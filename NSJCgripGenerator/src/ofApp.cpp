#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableArbTex();
    ofSetVerticalSync(true);
    
    ofSetFrameRate(60);
    mesh.load("./3dmodel/grip.ply");
    jcl.load("./3dmodel/jcl.ply");
    jcr.load("./3dmodel/jcr.ply");
    backgrip.load("./3dmodel/backgrip1.ply");
    
    gui.setup();
    guiVisible = true;

    gripvertex   = mesh.getVertices();
    jcrvertex   = jcr.getVertices();
    jclvertex  = jcl.getVertices();
    bgripvertex = backgrip.getVertices();
    
    for(int i = 0; i < (int)gripvertex.size();i++){
        
        if(gripvertex[i].x < 0){
            gpointnumm.push_back(i);
        }
        if(gripvertex[i].x > 0){
            gpointnump.push_back(i);
        }
        
    }
    
    for(int i = 0; i < (int)bgripvertex.size();i++){
        
        if(bgripvertex[i].x < 0){
            bgpointnumm.push_back(i);
        }
        if(bgripvertex[i].x > 0){
            bgpointnump.push_back(i);
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fgsize = ofMap(gsize, 18, 118, 0, 50);
    gripmove.set(fgsize,0, 0);
    camzoom = ofMap(cdistance, 1, 4, 300, 100);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient((30,30,100), (0,0,0), OF_GRADIENT_CIRCULAR);

    //camera
    camera.begin();
    camera.setDistance(camzoom);
    
    ofEnableDepthTest();
    
    
    
    //3d View set

    if(wireframes){
        ofSetColor(ofColor::white);
        mesh.drawWireframe();
        if(jc){
             jcl.drawWireframe();
             jcr.drawWireframe();
            }
        if(bgrip){
            backgrip.drawWireframe();
        }
        }
    
    if(faces){
        ofSetColor(ofColor::gray);
        mesh.drawFaces();

            if(jc){
            
            jcl.drawFaces();
            jcr.drawFaces();
        }
        
        
        if(bgrip){
            backgrip.drawFaces();
        }
    }
   
    if(vertices){
        ofSetColor(ofColor::white);
        glPointSize(2);
        mesh.drawVertices();
        if(jc){
            jcl.drawVertices();
            jcr.drawVertices();
        }
        if(bgrip){
            backgrip.drawVertices();
        }
    }
    //end
    
    
    //model scale
    for (int i = 0; i < (int)jcrvertex.size(); i++) {
        jcr.setVertex(i, jcrvertex[i] + gripmove);
    }
    
    for (int i = 0; i < (int)jclvertex.size(); i++) {
        jcl.setVertex(i, jclvertex[i] - gripmove);
    }
    for(int i = 0; i < (int)gpointnump.size();i++){
        mesh.setVertex(gpointnump[i], gripvertex[gpointnump[i]] + gripmove);
    }
    
    for(int i = 0; i < (int)gpointnumm.size();i++){
        mesh.setVertex(gpointnumm[i], gripvertex[gpointnumm[i]] - gripmove);
    }
    for(int i = 0; i < (int)bgpointnump.size();i++){
        backgrip.setVertex(bgpointnump[i], bgripvertex[bgpointnump[i]] + gripmove);
    }
    
    for(int i = 0; i < (int)bgpointnumm.size();i++){
        backgrip.setVertex(bgpointnumm[i], bgripvertex[bgpointnumm[i]] - gripmove);
    }
   
    //end
    
    
    ofDisableDepthTest();
    camera.end();
    
  //GUI
    mouseOverGui = false;
    if (guiVisible)
    {
        mouseOverGui = imGui();
    }
    if (mouseOverGui)
    {
       camera.disableMouseInput();
    }
    else
    {
        camera.enableMouseInput();
    }
    
    //end
    
    
}


bool ofApp::imGui()
{
    
    auto mainSettings = ofxImGui::Settings();

    gui.begin();
    
    {
       
        
        if (ofxImGui::BeginWindow("NSJC-Grip Generator ver 0.1a", mainSettings, false))
        {
            
        
            if (ofxImGui::BeginTree(view, mainSettings))
            {
                ImGui::Text("3D View Option");
                ofxImGui::AddParameter(jc);
                ofxImGui::AddParameter(wireframes);
                ofxImGui::AddParameter(faces);
                ofxImGui::AddParameter(vertices);
                ofxImGui::AddParameter(cdistance);
                ofxImGui::EndTree(mainSettings);
                
            }
            
    
            
            if (ofxImGui::BeginTree(model, mainSettings))
            {
                
                ImGui::Text("Front Grip");
                ofxImGui::AddParameter(gsize);

                ImGui::Spacing();
                ImGui::Text("Back Grip");
                ofxImGui::AddParameter(bgrip);
                //ofxImGui::AddParameter(bgrippos);
                

                ofxImGui::EndTree(mainSettings);
            }
            
            if (ofxImGui::BeginTree(gene, mainSettings)){
               // ofxImGui::AddParameter(dummy);
                ImGui::Spacing();

                if (ImGui::Button("Save Model"))
                {
                    if(bgrip){
                        save.append(backgrip);
                        
                    }
                    save.append(mesh);
                    date = ofGetTimestampString();
                    save.save(date + ".ply");
                    saved = true;
                    save.clear();
                }

                
                
                ofxImGui::EndTree(mainSettings);
            }

           
            ImGui::Spacing();
            if(saved){
                ImGui::Text("Saved as %s.ply", date.c_str());
            }
            ImGui::Text("Frame (%.2f FPS)",  ImGui::GetIO().Framerate);
          
            
        }
    
        
    
    
    ofxImGui::EndWindow(mainSettings);
    
   
    }
    
    gui.end();
    return mainSettings.mouseOverGui;


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}



//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
