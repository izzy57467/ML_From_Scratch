#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

void split(vector<int> survived, vector<int> sex){
    // We know that the total data points are 1046. Do an 80/20 split based on this for train/test
    //need to randomize the vectors we read in.
    auto rng = default_random_engine{};
    shuffle(survived, sex, rng);
    //create new vectors for train and test.
    vector<int>::const_iterator trainSur = survived.begin() + 800;
    vector<int>::const_iterator testSur = survived.at(801) + survived.end();
    vector<int>::const_iterator trainSex = sex.begin() + 800;
    vector<int>::const_iterator testSex = sex.at(801) + sex.end();
}


int main(int argc, char** argv){
    ifstream inFS; //Input file stream
    string line;
    string survived_in, sex_in;
    const int MAX_LEN = 1050;
    vector<int> survived(MAX_LEN);
    vector<int> sex(MAX_LEN);

    //Try to open file
    cout << "Opening file tiatanicLogReg.csv." << endl;

    inFS.open("titanicLogReg.csv");
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

    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');

        survived.at(numObservations) = stof(survived_in);
        sex.at(numObservations) = stof(sex_in);

        numObservations++;
    }

    survived.resize(numObservations);
    sex.resize(numObservations);

    
    cout << "new length " << survived.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close(); //Done with file, so close it

    cout << "Number of records: " << numObservations << endl;
    
}