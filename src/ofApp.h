#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxXmlSettings.h"

#define _maxMessageLen 128

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);
		void gotMessage(ofMessage msg);

    // settings
    ofxXmlSettings *_settings;
    const string _settings_filename = "settings.xml";
    void loadSettingsAndWriteDefaultIfNeeded();
    void writeDefaultSettings();

    // network
    char _udpMessage[_maxMessageLen];
    ofxUDPManager _udpConnection;
    int _port = 12345;
    void connectToHost();
    void react();
};
