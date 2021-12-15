//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#ifndef PROJECT5_TXTREADER_H
#define PROJECT5_TXTREADER_H

#include "DataStruct.h"
#include "AbstractReader.h"

/**
* Takes as input a filename and returns a Data struct that can be passed to the integration methods
* \brief Class implementing reading data from TXT riles
*/
class TxtReader : public AbstractReader {
public:
    /** \brief Initialiser setting the filename
*/
    TxtReader(std::string filename);
    /** \brief Method to read data from file
  */
    /**
    * Takes as input a filename and implements a OuputData() method returning the data from file
    */
    /*!
    \return The Data struct read from the file
    */
    Data OutputData();
};

#endif //PROJECT5_TXTREADER_H
