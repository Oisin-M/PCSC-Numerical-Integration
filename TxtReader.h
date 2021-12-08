//
// Created by morrison@INTRANET.EPFL.CH on 08.12.21.
//

#ifndef PROJECT5_TXTREADER_H
#define PROJECT5_TXTREADER_H

#include "DataStruct.h"
#include "AbstractReader.h"

class TxtReader : public AbstractReader {
public:
    TxtReader(std::string filename);
    Data OutputData();
};

#endif //PROJECT5_TXTREADER_H
