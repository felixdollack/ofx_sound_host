#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    loadSettingsAndWriteDefaultIfNeeded();
}

//--------------------------------------------------------------
void ofApp::update(){

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

void ofApp::loadSettingsAndWriteDefaultIfNeeded() {
    this->_settings = new ofxXmlSettings();
    if (this->_settings->loadFile(this->_settings_filename) == false) {
        writeDefaultSettings();
        this->_settings->loadFile(this->_settings_filename);
    }
    this->_settings->pushTag("settings");
    {
        // read number of files and make vector of sound files
        this->_settings->pushTag("filenames");
        int number_of_files = this->_settings->getValue("amount", 1);
        for (int kk=0; kk<number_of_files; kk++) {
            this->_settings->pushTag("file", kk);
            {
                int id = this->_settings->getValue("id", 1);
                string filename = this->_settings->getValue("name", "");
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
