//
// Created by morrison@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PROJECT5_ABSTRACTREADER_H
#define PROJECT5_ABSTRACTREADER_H

#include "DataStruct.h"

class AbstractReader {
public:
    AbstractReader(std::string filename) {
        fname=filename;
    };
    Data OutputData(std::string fname);
private:
    std::string fname;
};
#endif //PROJECT5_ABSTRACTREADER_H