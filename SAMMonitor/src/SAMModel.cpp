#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <string>
#include <SAMModel.h>
#include <logger.h>

using namespace std;

string JSON_PATH = "/usr/SAM/Model/";

Json::Value model;

void readJson(string path, int pid){
    string complete_path = path + to_string(pid) + ".json";
    ifstream ifs(complete_path);
    if(!ifs.is_open()){
        cout << "error oppening json file:" + complete_path << endl;
        writelog("error oppening json file:" + complete_path);
    }
    else{
        writelog("json file oppened: " + complete_path);
    }
    
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

int getPID(){
    return getInt("pid");
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

void startJson(int pid){
    readJson(JSON_PATH, pid);
}





























