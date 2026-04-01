#ifndef IMACHINE_H
#define IMACHINE_H

#include "IPrinter.h"
#include "IScanner.h"

class IMachine : public IPrinter , public IScanner {

public:
    virtual ~IMachine() = default;
};
#endif // IMACHINE_H
