#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetVerticalSync(true);
  ofSetWindowPosition(0, 0);
  ofSetWindowShape(1920, 1080);
  ofSetFrameRate(60);

  ofDisableArbTex();
  ofLoadImage(texture, "img/dot.png");

  font.load("fonts/PrintChar21.ttf", 18, true, true, true);
  state = 0;
  typing = "";
  reciever.setup(5612);
  post = "holahola"; 

  // lectura, escritura, invención de valores

  numStars = 5500;
  camDistance = 1000;

  for(int i = 0; i<numStars; i++ ) {
    
    float theta1 = ofRandom(0, TWO_PI);
    //float theta1 = ofRandom(0, 5000); 
    float theta2 = ofRandom(0, TWO_PI);
    
    ofVec3f p;
    p.x = cos( theta1 ) * cos( theta2 );
    p.y = sin( theta1 );
    p.z = cos( theta1 ) * sin( theta2 );
    p *= ofRandom(0, 500);
    points.push_back(p);
    float size = ofRandom(5, 70); 
    sizes.push_back(ofVec3f(size));
    
  }

  shader.load("shaders/shader"); 
 
}

//--------------------------------------------------------------
void ofApp::update(){

  // fft?

  // OSC
  while (reciever.hasWaitingMessages()){	
    ofxOscMessage m;
    reciever.getNextMessage(&m);
    
    if (m.getAddress() == "/camDistance" && m.getNumArgs() == 1){
      camDistance = m.getArgAsFloat(0);
      camera.setDistance(camDistance); 
      post = ofToString(m.getArgAsFloat(0)); 
    }
  }

}

//--------------------------------------------------------------
void ofApp::draw(){

  ofBackground(0); 

  // Switch con las escenas.
  
  switch( state )  
    {
    case STATE_1:
      entrada(); 
      break;
    case STATE_2:
      bigBang();
      break;
    case STATE_3:
      gasParticulas();
      break;
    case STATE_4:
      formacionEstrellas();
      break;
    case STATE_5:
      hawc();
      break;
    case STATE_6:
      simulaciones();
      break;
    case STATE_7:
      salida();
      break;
    case STATE_8:
      // vacio 
      break;
    }

  /*

    Por aquí podría haber texto informativo sobre la escena en la que se encuentra.
    Activar / desactivar efectos para que se vea cool. Uno de los efectos podría ser la retroalimentación dentro de un objeto. Preguntarle A Mitzi qué objeto podría ser para no usar primitivos de OF

  */

  string blink = "";
  
  if(ofGetFrameNum() % 25 == 0){
    blink = "_";
  } else {
    blink = ""; 
  }

  font.drawString( "n.702_3774936_751> " + typing + blink, 100, 100);
  font.drawString(post, 100, 140);
  
}


//--------------------------------------------------------------

void ofApp::entrada(){

  // Texto inicial, introducciones, etc etc

  ofSetColor(255);
  font.drawString("Intro (este texto puede ser informativo)", 100, ofGetHeight() -100); 

}

//--------------------------------------------------------------

void ofApp::bigBang(){

  /*

    Expansión (según entiendo)
    Idealmente tendría que haber un gran momento explosivo?
    Propuesta: cámara 3d, imagenes transformadas a través de mesh con puntos para dar la sensación de conjuntos de puntos.
    Varias imágenes distribuidas y rotadas de forma tal que den la sensación de 3d
    En este sentido el gran momento explosivo podría ser la condensación de esos meshes en un mismo espacio


   for(int i = 0; i<num; i++ ) {
   }
  */

  int total = (int)points.size();
  vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
  vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW); 

  glDepthMask(GL_FALSE);
  
  ofSetColor(50, 10, 255);
  
  // this makes everything look glowy :)
  ofEnableBlendMode(OF_BLENDMODE_ADD);
  ofEnablePointSprites();

  shader.begin();
  camera.begin();

  camera.orbit(ofGetElapsedTimef()*2, ofGetElapsedTimef()*4, camera.getDistance()); 

  ofRotateZ(90); 
  texture.bind();
  vbo.draw(GL_POINTS, 0, (int)points.size());
  texture.unbind(); 
  
  camera.end();
  shader.end(); 
  ofDisablePointSprites();
  ofDisableBlendMode();

  ofSetColor(255);
  font.drawString("big bang", 100, ofGetHeight() -100); 
  
}

//--------------------------------------------------------------

void ofApp::gasParticulas(){

  /*

    Podrían ser los mismos objetos que lo anterior, solo que transformado en una lógica de manipulación de vértices. 
    Revisar ejemplos de partículas en OF
    flow 

  */

  ofSetColor(255);
  font.drawString("gas-particulas", 100, ofGetHeight() -100); 

}

//--------------------------------------------------------------

void ofApp::formacionEstrellas(){

  /*

    Sketch en Processing. 
  
  */

  ofSetColor(255);
  font.drawString("jets formación estrellas", 100, ofGetHeight() -100); 

  
}

//--------------------------------------------------------------

void ofApp::hawc(){

  /*

    ofhawc mejorado

  */

  ofSetColor(255);
  font.drawString("HAWC", 100, ofGetHeight() -100); 
  
}

//--------------------------------------------------------------

void ofApp::simulaciones(){

  ofSetColor(255);
  font.drawString("Simulaciones", 100, ofGetHeight() -100); 
  
}

//--------------------------------------------------------------

void ofApp::salida(){

  // créditos, agradecimientos etc.

  ofSetColor(255);
  font.drawString("Outro", 100, ofGetHeight() -100); 
  
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  if(key != OF_KEY_RETURN){
    if(key != OF_KEY_BACKSPACE){
      typing += key;
    }
    else{
      if(typing.size() > 0){
	typing.erase(typing.end() - 1);
      }
    }
  }
  
  else{
    std::vector < std::string > term = ofSplitString(typing, " ");

    if(term[0] == "state"){
      state = ofToInt(term[1]); 
    }

    typing = ""; 
    
  }
  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
