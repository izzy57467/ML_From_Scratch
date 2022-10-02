#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std::chrono;
using namespace std;

double accuracy(int tp, int fn, int tn, int fp){
    double result = (tp+tn)/(tp+tn+fp+fn);
    return result;
}

double sensitivity(int tp, int fn, int tn, int fp){
    double result = tp/(tp+fn);
    return result;
}

double specificity(int tp, int fn, int tn, int fp){
    double result = tn/(tn+fp);
    return result;
}

bool custom_sort(double a, double b)
{
    double  a1=abs(a-0);
    double  b1=abs(b-0);
    return a1<b1;
}

int main(int argc, char** argv){
    
    ifstream inFS; //Input file stream
    string line;
    string age_in,survived_in, sex_in, pclass_in;

    // Setting length of divide
    const int TRAIN_LEN = 800;
    const int TEST_LEN = 250;

    // Training data frame
    vector<int> train_survived(TRAIN_LEN);
    vector<int> train_sex(TRAIN_LEN);
    
    // Testing data frame
    vector<int> test_survived(TEST_LEN);
    vector<int> test_sex(TEST_LEN);

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

    int numObservations = 0;
    while (inFS.good() && numObservations < 800) {
        getline(inFS, pclass_in, ',');
       // cout << heading_in << endl;
        getline(inFS, survived_in, ',');
       // cout << pclass_in << endl;
        getline(inFS, sex_in, ',');
       // cout << survived_in << endl;
        getline(inFS, age_in);
       // cout << sex_in << endl;

        train_survived.at(numObservations) = stof(survived_in);
        train_sex.at(numObservations) = stof(sex_in);

        numObservations++;
    }

    numObservations = 0;
    while (inFS.good() && numObservations < 250) {
        getline(inFS, pclass_in, ',');
       // cout << heading_in << endl;
        getline(inFS, survived_in, ',');
       // cout << pclass_in << endl;
        getline(inFS, sex_in, ',');
       // cout << survived_in << endl;
        getline(inFS, age_in);
       // cout << sex_in << endl;

        test_survived.at(numObservations) = stof(survived_in);
        test_sex.at(numObservations) = stof(sex_in);

        numObservations++;
    }
    
    ofstream myfile;
    myfile.open("results.txt");
    

    vector<double>error; // for storing the error values
    vector<double>output;
    double err;    // for calculating error on each stage
    double b0 = 0; // intializing b0
    double b1 = 0; // initializing b1
    double alpha = 0.01; // initializing our learning rate

    // STARTING CLOCK
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    /*Training Phase*/
    for (int i = 0; i < 800; i ++) { //Since there are 800 values in our dataset and we want to run for 4 epochs so total for loop run 3200 times
    int idx = i % 800;   //for accessing index after every epoch
    double p = -(b0 + b1 * train_sex.at(idx)); //making the prediction
    double pred  = 1/(1+ exp(p)); //calculating final prediction applying sigmoid
    err = train_survived.at(idx)-pred;  //calculating the error
    b0 = b0 - alpha * err*pred *(1-pred)* 1.0;   //updating b0
    b1 = b1 + alpha * err * pred*(1-pred) *train_sex.at(idx);//updating b1
    output.push_back(b1);
    myfile<<"B0="<<b0<<" "<<"B1="<<b1<<" "<<" error="<<err<<endl;// printing values after every step
    error.push_back(err);
    }

    // ENDING CLOCK
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  
    std::cout << "Elapsed time during training: " << elapsed_seconds.count() << "s\n";
    

    sort(error.begin(),error.end(),custom_sort);// sorting to get the minimum value
    cout<<"Final Coefficients are: "<<"B0 = "<<b0<<" "<<"B1 = "<<b1<<" "<<"error = "<<error[0] << endl;

    /*Testing Phase*/
    double test1; //enter test x1 and x2
    cout<<"Enter a test x value: " << endl;
    cin>>test1;
    double pred=b0+b1*test1; //make prediction
    cout<<"The value predicted by the model= "<<pred<<endl;
    if(pred>0.5)
    pred=1;
    else
    pred=0;
    cout<<"The class predicted by the model= "<< pred << endl;

    int TP, FN, TN, FP;

    cout << "output size: " << output.size() << endl;

    for(int x = 0;x<output.size();x++){
        if(output.at(x) > 0 && train_survived.at(x) > 0){
            TP++;
        }
        if(output.at(x) > 0 && train_survived.at(x) < 0){
            FN++;
        }
        if(output.at(x) < 0 && train_survived.at(x) < 0){
            TN++;
        }
        else
            FP++;
    }

    cout << "TP: " << TP << endl;
    cout << "FN: " << FN << endl;
    cout << "TN: " << TN << endl;
    cout << "FP: " << FP << endl;

    cout << "Accuracy: " << accuracy(TP, FN, TN, FP) << endl;
    cout << "Sensitivity: " << sensitivity(TP, FN, TN, FP) << endl;
    cout << "Specificity: " << specificity(TP, FN, TN, FP) << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close(); // Done with file, so close it
    myfile.close(); // Done writing to file, so close it
}