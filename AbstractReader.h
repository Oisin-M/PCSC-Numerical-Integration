//
// Created by morrison@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PROJECT5_ABSTRACTREADER_H
#define PROJECT5_ABSTRACTREADER_H

#include "DataStruct.h"

/**
* Takes as input a filename and outputs a Data struct
* \brief Abstract class for implementation of file reading
*/
class AbstractReader {
public:
/** \brief Initialiser setting filename
*/
    AbstractReader(std::string filename);
/** \brief Method to compute data as Data struct  from file
*/
/*!
\return A Data object read from the the file
*/
    virtual Data OutputData()=0;

protected:
    std::string fname;
};
#endif //PROJECT5_ABSTRACTREADER_H