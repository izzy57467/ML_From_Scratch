#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

bool custom_sort(double a, double b){
    double  a1=abs(a-0);
    double  b1=abs(b-0);
    return a1<b1;
}

/*
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
*/

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
    cout << "Opening file titanic_project.csv." << endl;
    inFS.open("titanic.csv");
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


    ///////////////////!!!!!!!!!!!

    /*Intialization Phase*/
    // Survived Vector
    // Sex Array
    vector<double>error;             // array to store all error values
    double err;
    double b0 = 0;                   //initializing b0
    double b1 = 0;                   //initializing b1
    double alpha = 0.01;             //intializing error rate

    /*Training Phase*/
    for (int i = 0; i < 800; i++) {   // since there are 5 values and we want 4 epochs so run for loop for 20 times
        int idx = i % 5;              //for accessing index after every epoch
        double p = b0 + b1 * survived.at(idx);  //calculating prediction
        err = p - sex.at(idx);              // calculating error
        b0 = b0 - alpha * err;         // updating b0
        b1 = b1 - alpha * err * survived.at(idx);// updating b1
        cout<<"B0="<<(int)b0<<" "<<"B1="<<(int)b1<<" "<<"error="<<(int)err<<endl;// printing values after every updation
        error.push_back(err);
    }
    sort(error.begin(),error.end(),custom_sort);//sorting based on error values
    cout<<"Final Values are: "<<"B0="<<(int)b0<<" "<<"B1="<<(int)b1<<" "<<"error="<<error[0]<<endl;

    /*Testing Phase*/
    cout<<"Enter a test x value \n";
    double test;

    cout << "Enter test: \n";
    cin >> test;
    double pred = b0+b1*test;
    cout<<endl;
    cout<<"The value predicted by the model = \n"<< (int)pred;


    error.clear(); // for storing the error values
    err = 0;    // for calculating error on each stage
    b0 = 0; // initializing b0
    b1 = 0; // initializing b1
    double b2 = 0; // initializing b2
    alpha = 0.01; // initializing our learning rate
    double  e = 2.71828;
    
    /*Training Phase*/
    for(int i = 801; i < survived.size(); i++){ //Since there are 10 values in our dataset and we want to run for 4 epochs so total for loop run 40 times
        int idx = i % 10;   //for accessing index after every epoch
        double p = -(b0 + b1 * survived.at(idx)+ b2* sex.at(idx)); //making the prediction
        pred  = 1/(1+ pow(e,p)); //calculating final prediction applying sigmoid
        err = sex.at(idx)-pred;  //calculating the error
        b0 = b0 - alpha * err * pred *(1-pred)* 1.0;   //updating b0
        b1 = b1 + alpha * err * pred*(1-pred) *survived.at(idx);//updating b1
        b2 = b2 + alpha * err * pred*(1-pred) * sex.at(idx);//updating b2
        cout<<"B0="<<b0<<" "<<"B1="<<b1<<" "<<"B2="<<b2<<" error="<<err<<endl;// printing values after every step
        cout << "help" << endl;
        error.push_back(err);
    }

    sort(error.begin(),error.end(),custom_sort);//custom sort based on absolute error difference
    cout<<"\nFinal Values are: "<<"B0="<<b0<<" "<<"B1="<<b1<<" "<<"B2="<<b2<<" error="<<error[0];
    
    /*Testing Phase*/
    double test1,test2; //enter test x1 and x2
    cout << "\nTest 1: \n";
    cin>> test1;
    cout << "Test 2 \n";
    cin >> test2;
    pred=b0+b1*test1+b2*test2; //make prediction
    cout<<"The value predicted by the model= "<<pred<<endl;
    if(pred>0.5)
    pred=1;
    else
    pred=0;
    cout<<"The class predicted by the model= "<<pred;
    
}