//
// Created by majoor@INTRANET.EPFL.CH on 08.12.21.
//

#ifndef OFFREADFILE_H
#define OFFREADFILE_H

#include "AbstractReader.h"

class ReadTxt : public AbstractReader {
public:
    ReadTxt(const string& fname);
    Data readTxt();
};

#endif //OFFREADFILE_H