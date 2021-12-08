//
// Created by majoor@INTRANET.EPFL.CH on 08.12.21.
//

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <array>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#include "AbstractReader.h"
#include "offreadfile.h"

string ReadNthLine(const string& filename, int N)
{
    std::ifstream in(filename.c_str());

    std::string s;
    //for performance
    s.reserve(200);

    //skip N lines
    for(int i = 0; i < N; ++i)
        std::getline(in, s);

    std::getline(in,s);
    return s;
}

int countIntegers(string str)
{
    stringstream ss;
    int count_ints = 0;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            count_ints += 1;

        /* To save from space at the end of string */
        temp = "";
    }
    return count_ints;
}


Eigen::VectorXd extractIntegers(string str)
{
    int n_ints = countIntegers(str);
    Eigen::VectorXd vec (n_ints);
    stringstream ss;
    int fill_counter = 0;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            // cout << found << " ";
            vec(fill_counter) = found;
            fill_counter += 1;

        /* To save from space at the end of string */
        temp = "";
    }
    return vec;
}

int returnDimensionDomain (const string& filename){
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s = ReadNthLine(filename, 0);
    auto vec = extractIntegers(s);
    int domains_dim = vec(0);
    return domains_dim;
}

int returnDimensionOutput (const string& filename){
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s = ReadNthLine(filename, 0);
    auto vec = extractIntegers(s);
    int outputs_dim = vec(1);
    return outputs_dim;
}

Eigen::Vector2d returnDimensions (const string& filename){
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s = ReadNthLine(filename, 0);
    auto vec = extractIntegers(s);
    int domains_dim = vec(0);
    int outputs_dim = vec(1);
    Eigen::Vector2d dimensions (domains_dim, outputs_dim);
    return dimensions;
}

Eigen::MatrixXd returnBoundsX (const string& filename){

    int domains_dim = returnDimensionDomain(filename);
    Eigen::MatrixXd boundsX (domains_dim, 2);

    for (int i = 1; i < domains_dim + 1; i++) {
        auto bounds = extractIntegers(ReadNthLine(filename, i));
        boundsX(i - 1, 0) = bounds(0);
        boundsX(i - 1, 1) = bounds(1);

    return boundsX;
}

Eigen::MatrixXd returnBoundsY (const string& filename){

    int domains_dim = returnDimensionsDomain(filename);
    Eigen::MatrixXd boundsY (domains_dim, 2);

    for (int i = 1; i < domains_dim + 1; i++) {
        auto bounds = extractIntegers(ReadNthLine(filename, i));
        boundsY(i - 1, 0) = bounds(2);
        boundsY(i - 1, 1) = bounds(3);

    return boundsY;
}

Eigen::MatrixXd returnSteps (const string& filename){

    int domains_dim = returnDimensionsDomain(filename);
    Eigen::MatrixXd numberSteps (domains_dim, 2);

    for (int i = 1; i < domains_dim + 1; i++) {
        auto bounds = extractIntegers(ReadNthLine(filename, i));
        numberSteps(i - 1, 0) = bounds(4);
        numberSteps(i - 1, 1) = bounds(5);

    return numberSteps;
}

Eigen::VectorXcd function (double x, double y){
    Eigen::VectorXd XandY (max_rank / 2);
    XandY(0) = 1;
    for (i = 0; i < max_rank / 2 - 1; i++){
        power = ceil((i + 0.5) / 2); // gives 1, 1, 2, 2, 3, 3, ...
        if (i % 2 == 0){
            XandY(i + 1) = pow(x, power);
        }
        else {
            XandY(i + 1) = pow(y, power);
        }
    }
    Eigen::VectorXcd output (outputs_dim);
    output = output_functions * XandY;
    return output;
}

ReadTxt::ReadTxt(const string& fname) : AbstractReader(fname) {}








// old





int main() {
    ifstream inFile;
    string filename = "../readfile.txt";
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s = ReadNthLine(filename, 0);
    auto vec = extractIntegers(s);
    int domains_dim = vec(0);
    int outputs_dim = vec(1);

    Eigen::MatrixXd boundsX (domains_dim, 2);
    Eigen::MatrixXd boundsY (domains_dim, 2);
    Eigen::MatrixXd step_number (domains_dim, 2);


    for (int i = 1; i < domains_dim + 1; i++) {
        auto bounds = extractIntegers(ReadNthLine(filename, i));
        boundsX(i - 1, 0) = bounds(0);
        boundsX(i - 1, 1) = bounds(1);
        boundsY(i - 1, 0) = bounds(2);
        boundsY(i - 1, 1) = bounds(3);
        step_number(i - 1, 0) = bounds(4);
        step_number(i - 1, 1) = bounds(5);
    }
    int max_rank = 0;
    for (int i = domains_dim + 1; i < 1 + domains_dim + outputs_dim; i++) {
        int rank = extractIntegers(ReadNthLine(filename, i)).size();
        if (rank > max_rank) {
            max_rank = rank;
        }
    }
    cout << "Max rank : " << max_rank << endl;

    Eigen::MatrixXcd output_functions (outputs_dim, max_rank / 2);

    for (int i = domains_dim + 1; i < 1 + domains_dim + outputs_dim; i++) {
        auto coeffs = extractIntegers(ReadNthLine(filename, i));
        int rank = coeffs.size();
        for (int j = 0; j < rank / 2; j++){
            output_functions(i - domains_dim - 1, j) = complex<double>(coeffs(2*j), coeffs(2*j+1));

        }
    }
    cout << output_functions << endl;

    Eigen::VectorXd XandY (double x, double y);

    XandY (1) 
    

    // auto test = extractIntegers(ReadNthLine(filename, 3));
    // cout << "Vector : " << test << endl;
    // cout << "Last element : " << test[test.size()-1] << endl;
    // cout << "boundsX" << boundsX << endl;
    inFile.close();

    return 0;
}