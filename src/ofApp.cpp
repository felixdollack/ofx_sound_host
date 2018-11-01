#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    loadSettingsAndWriteDefaultIfNeeded();
    connectToHost();
}

//--------------------------------------------------------------
void ofApp::update(){
    react();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::connectToHost() {
    this->_udpConnection.Create();
    this->_udpConnection.Bind(this->_port);
    this->_udpConnection.SetNonBlocking(true);
}
void ofApp::react() {
    memset(this->_udpMessage, 0, _maxMessageLen);
    this->_udpConnection.Receive(this->_udpMessage, _maxMessageLen);

    string message = this->_udpMessage;
    if (message != "") {
        int i = ofToInt(message);
        if (i <= this->_sounds.size()) {
            if (this->_sounds[i]->isLoaded() == true) {
                this->_sounds[i]->play();
            }
        }
        if (i == 9999) {
            if (this->_beep.isLoaded() == true) {
                this->_beep.play();
            }
        }
    }
}

void ofApp::loadSettingsAndWriteDefaultIfNeeded() {
    ofSoundPlayer *sound = NULL;
    string filename;
    int id;
    this->_settings = new ofxXmlSettings();
    if (this->_settings->loadFile(this->_settings_filename) == false) {
        writeDefaultSettings();
        this->_settings->loadFile(this->_settings_filename);
    }
    this->_settings->pushTag("settings");
    {
        // read file for beep
        filename = this->_settings->getValue("beep", "");
        cout << "beep:" << filename << endl;
        if (filename != "") {
            this->_beep.load(filename);
        }
        // read number of files and make vector of sound files
        this->_settings->pushTag("filenames");
        int number_of_files = this->_settings->getValue("amount", 1);
        for (int kk=0; kk<number_of_files; kk++) {
            this->_settings->pushTag("file", kk);
            {
                id = this->_settings->getValue("id", 1);
                filename = this->_settings->getValue("name", "");
                cout << "file " << id << ":" << filename << endl;
                if (filename != "") {
                    sound = new ofSoundPlayer();
                    sound->load(filename);
                }
                _sounds.push_back(sound);
            }
            this->_settings->popTag();
        }
        this->_settings->popTag();

        // read network settings
        this->_settings->pushTag("network");
        {
            this->_port = this->_settings->getValue("port", 12345);
        }
        this->_settings->popTag();
    }
    this->_settings->popTag();
}

void ofApp::writeDefaultSettings() {
    this->_settings->addTag("settings");
    this->_settings->pushTag("settings");
    {
        this->_settings->addValue("beep", "beep_low.wav");
        this->_settings->addTag("filenames");
        this->_settings->pushTag("filenames");
        {
            this->_settings->addValue("amount", 1);
            this->_settings->addTag("file");
            this->_settings->pushTag("file", 0);
            {
                this->_settings->addValue("id", 0);
                this->_settings->addValue("name", "beep_mid.wav");
            }
            this->_settings->popTag();
        }
        this->_settings->popTag();
        this->_settings->addTag("network");
        this->_settings->pushTag("network");
        {
            this->_settings->addValue("port", 12345);
        }
        this->_settings->popTag();
    }
    this->_settings->popTag();
    this->_settings->saveFile();
}
