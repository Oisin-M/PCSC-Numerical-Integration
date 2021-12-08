//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#include "TxtReader.h"
#include "DataStruct.h"

std::string TxtReader::ReadNthLine(const std::string& filename, int N)
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

int TxtReader::countIntegers(std::string str)
{
    std::stringstream ss;
    int count_ints = 0;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    std::string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found)
            count_ints += 1;

        /* To save from space at the end of string */
        temp = "";
    }
    return count_ints;
}

Eigen::VectorXd TxtReader::extractIntegers(std::string str)
{
    int n_ints = countIntegers(str);
    Eigen::VectorXd vec (n_ints);
    std::stringstream ss;
    int fill_counter = 0;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    std::string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (std::stringstream(temp) >> found)
            // cout << found << " ";
            vec(fill_counter) = found;
            fill_counter += 1;

        /* To save from space at the end of string */
        temp = "";
    }
    return vec;
}


Data TxtReader::OutputData() {
    std::ifstream inFile;
    inFile.open(fname);
    if (!inFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    std::string s = ReadNthLine(fname, 0);
    auto vec = extractIntegers(s);
    int domains_dim = vec(0);
    int outputs_dim = vec(1);

    Eigen::MatrixXd boundsX (domains_dim, 2);
    Eigen::MatrixXd boundsY (domains_dim, 2);
    Eigen::MatrixXd noSteps (domains_dim, 2);


    for (int i = 1; i < domains_dim + 1; i++) {
        auto bounds = extractIntegers(ReadNthLine(fname, i));
        boundsX(i - 1, 0) = bounds(0);
        boundsX(i - 1, 1) = bounds(1);
        boundsY(i - 1, 0) = bounds(2);
        boundsY(i - 1, 1) = bounds(3);
        noSteps(i - 1, 0) = bounds(4);
        noSteps(i - 1, 1) = bounds(5);
    }

    int max_rank = 0;
    for (int i = domains_dim + 1; i < 1 + domains_dim + outputs_dim; i++) {
        int rank = extractIntegers(ReadNthLine(fname, i)).size();
        if (rank > max_rank) {
            max_rank = rank;
        }
    }
    std::cout << "Max rank : " << max_rank << std::endl;

    Eigen::MatrixXcd coefficients (outputs_dim, max_rank / 2);

    for (int i = domains_dim + 1; i < 1 + domains_dim + outputs_dim; i++) {
        auto coeffs = extractIntegers(ReadNthLine(fname, i));
        int rank = coeffs.size();
        for (int j = 0; j < rank / 2; j++){
            coefficients(i - domains_dim - 1, j) = std::complex<double>(coeffs(2*j), coeffs(2*j+1));

        }
    }
    Data data = { .boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficients, .D=domains_dim, .m=outputs_dim};
    return data;


// Data TxtReader::OutputData() {
//     Eigen::MatrixX2d boundsX(2,2); //X rows, 2 columns and doubles
//     Eigen::MatrixX2d boundsY(2,2); //X rows, 2 columns and doubles
//     Eigen::MatrixX2i noSteps(2,2); //X rows, 2 columns and ints
//     Eigen::MatrixXd coefficents(2,2); //X rows, 2 columns and ints


//     for (int i=0; i<2; i++) {
//         boundsX(0,i)=i+1;
//         boundsY(0,i)=i+1;
//         noSteps(0,i)=i+1;
//         coefficents(0,i)=i+1;
//     }
//     for (int i=0; i<2; i++) {
//         boundsX(1,i)=i+1;
//         boundsY(1,i)=i+1;
//         noSteps(1,i)=i+1;
//         coefficents(1,i)=i+1;
//     }
//     int D=2;
//     int m=2;

//     Data data = { .boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficents, .D=D, .m=m};
//     return data;
// }

TxtReader::TxtReader(std::string filename) : AbstractReader(filename) {}