//
// Created by morrison@INTRANET.EPFL.CH on 30.11.21.
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

int main() {
    int sum = 0;
    int x;
    string line;
    ifstream inFile;
    string filename = "/home/majoor/myfiles/Programmation/Project-PCSC/project-5-numerical-integration/readfile.txt";
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string s = ReadNthLine(filename, 0);
    auto vec = extractIntegers(s);
    int domains_dim = vec(0);
    int outputs_dim = vec(1);

    auto test = extractIntegers(ReadNthLine(filename, 3));
    cout << "Vector : " << test << endl;
    cout << "Last element : " << test[test.size()-1] << endl;
    inFile.close();
    //while (inFile >> x) {
    //    sum = sum + x;
    //}

    //inFile.close();
    //cout << "Sum = " << sum << endl;
    return 0;
}

