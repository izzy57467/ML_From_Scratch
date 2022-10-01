#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char** argv){
    
    ifstream inFS; //Input file stream
    string line;
    string heading_in,survived_in, sex_in, pclass_in;
    const int MAX_LEN = 1050;
    vector<int> heading(MAX_LEN);
    vector<int> pclass(MAX_LEN);
    vector<int> survived(MAX_LEN);
    vector<int> sex(MAX_LEN);

    //Try to open file
    cout << "Opening file tiatanic_project.csv." << endl;

    inFS.open("titanic_project.csv");
    if(!inFS.is_open()){
        cout << "Could not open file titanic_project.csv." << endl;
        return 1; //1 indicates error
    }

        //Can now use inFS stream like cin stream
    //Boston.csv should contain two doubles

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    //echo heading
    cout << "heading: " << line << endl;

        //echo heading
    cout << "heading: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, heading_in, ',');
        getline(inFS, pclass_in, ',');
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');

        pclass.at(numObservations) = stof(pclass_in);
        survived.at(numObservations) = stof(survived_in);
        sex.at(numObservations) = stof(sex_in);

        numObservations++;
    }
    
    pclass.resize(numObservations);
    survived.resize(numObservations);
    sex.resize(numObservations);

    
    cout << "new length " << survived.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close(); //Done with file, so close it

    cout << "Number of records: " << numObservations << endl;
}