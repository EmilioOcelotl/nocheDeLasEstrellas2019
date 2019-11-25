#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

typedef enum {
	      STATE_1, // Entrada
	      STATE_2, // Big Bang 
	      STATE_3, // Gas Partículas
	      STATE_4, // formación estrellas (jets) 
	      STATE_5, // hawc
	      STATE_6, // simulaciones
	      STATE_7, // salida
	      STATE_8 // vacio 
} State;

class ofApp : public ofBaseApp{
public:
  void setup();
  void update();
  void draw();
  
  void bigBang();
  void gasParticulas();
  void formacionEstrellas();
  void hawc();
  void simulaciones();
  void entrada();
  void salida(); 
		
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

  int state;
  ofTexture texture;
  ofEasyCam camera;

  vector <ofVec3f> points;
  vector <ofVec3f> sizes;

  ofVbo vbo;
  ofTrueTypeFont font;
  string typing; 
  ofShader shader;
  ofxOscReceiver reciever;

  float camDistance;
  int numStars;
  string post; 
  
};
