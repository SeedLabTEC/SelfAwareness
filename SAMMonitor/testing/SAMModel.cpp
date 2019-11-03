#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>

#define JSON_PATH "/usr/SAM/Model/SAMModel.json"

using namespace std;

Json::Value model;

void readJson(string path){
    ifstream ifs(path);
    Json::Reader reader;
    reader.parse(ifs, model); // reader can also read strings
}

void saveJson(string path){
    Json::StyledStreamWriter writer;
    std::ofstream output(path);
    writer.write(output,model);
}


//gets
static int getInt(string key){
    return model[key].asInt(); 
}

static double getDouble(string key){
    return model[key].asDouble(); 
}

static string getString(string key){
    return model[key].asString(); 
}

static Json::Value getList(string key){
    const Json::Value& temp = model[key];
    return temp;
}

double getPowerUpperLimit(){
    return getDouble("upperPower");
}

double getPowerLowerLimit(){
    return getDouble("lowerPower");
}

double getFreqUpperLimit(){
    return getDouble("upperFreq");
}

double getFreqLowerLimit(){
    return getDouble("lowerFreq");
}

double getCoresUpperLimit(){
    return getDouble("upperCores");
}

double getCoresLowerLimit(){
    return getDouble("lowerCores");
}

double getCPUUpperLimit(){
    return getDouble("upperCPU");
}

double getCPULowerLimit(){
    return getDouble("lowerCPU");
}

double getMemUpperLimit(){
    return getDouble("upperMem");
}

double getMemLowerLimit(){
    return getDouble("lowerMem");
}

//sets
void setPowerUpperLimit(double val){
    model["upperPower"] = val;
    saveJson(JSON_PATH);
}

void setPowerLowerLimit(double val){
    model["lowerPower"] = val;
    saveJson(JSON_PATH);
}

void setFreqUpperLimit(double val){
    model["upperFreq"] = val;
    saveJson(JSON_PATH);
}

void setFreqLowerLimit(double val){
    model["lowerFreq"] = val;
    saveJson(JSON_PATH);
}

void setCoresUpperLimit(double val){
    model["upperCores"] = val;
    saveJson(JSON_PATH);
}

void setCoresLowerLimit(double val){
    model["lowerCores"] = val;
    saveJson(JSON_PATH);
}

void setCPUUpperLimit(double val){
    model["upperCPU"] = val;
    saveJson(JSON_PATH);
}

void setCPULowerLimit(double val){
    model["lowerCPU"] = val;
    saveJson(JSON_PATH);
}

void setMemUpperLimit(double val){
    model["upperMem"] = val;
    saveJson(JSON_PATH);
}

void setMemLowerLimit(double val){
    model["lowerMem"] = val;
    saveJson(JSON_PATH);
}


int main() {
    readJson(JSON_PATH);
    cout << "upper power limit: " << getPowerUpperLimit() << endl;
    cout << "lower power limit: " << getPowerLowerLimit() << endl;
    cout << "upper frequency limit: " << getFreqUpperLimit() << endl;
    cout << "lower frequency limit: " << getFreqLowerLimit() << endl;
    cout << "upper cores limit: " << getCoresUpperLimit() << endl;
    cout << "lower cores limit: " << getCoresLowerLimit() << endl;
    cout << "upper cpu limit: " << getCPUUpperLimit() << endl;
    cout << "lower cpu limit: " << getCPULowerLimit() << endl;
    cout << "upper mem limit: " << getMemUpperLimit() << endl;
    cout << "lower mem limit: " << getMemLowerLimit() << endl;

    setPowerLowerLimit(0.0);
    setPowerUpperLimit(0.0);
    setFreqUpperLimit(0.0); 
    setFreqLowerLimit(0.0); 
    setCoresUpperLimit(0.0);
    setCoresLowerLimit(0.0);
    setCPUUpperLimit(0.0);
    setCPULowerLimit(0.0);
    setMemUpperLimit(0.0);
    setMemLowerLimit(0.0);

    cout << "upper power limit: " << getPowerUpperLimit() << endl;
    cout << "lower power limit: " << getPowerLowerLimit() << endl;
    cout << "upper frequency limit: " << getFreqUpperLimit() << endl;
    cout << "lower frequency limit: " << getFreqLowerLimit() << endl;
    cout << "upper cores limit: " << getCoresUpperLimit() << endl;
    cout << "lower cores limit: " << getCoresLowerLimit() << endl;
    cout << "upper cpu limit: " << getCPUUpperLimit() << endl;
    cout << "lower cpu limit: " << getCPULowerLimit() << endl;
    cout << "upper mem limit: " << getMemUpperLimit() << endl;
    cout << "lower mem limit: " << getMemLowerLimit() << endl;
    
    
    // const Json::Value& characters = getList("characters");
    // for (int i = 0; i < characters.size(); i++){
        // cout << "    name: " << characters[i]["name"].asString();
        // cout << " chapter: " << characters[i]["chapter"].asUInt();
        // cout << endl;
    // }
}





























