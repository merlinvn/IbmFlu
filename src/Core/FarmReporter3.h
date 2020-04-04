/* 
 * File:   FarmReporter3.h
 * Author: merlin
 *
 * Created on July 1, 2012, 10:01 AM
 */

#ifndef FARMREPORTER3_H
#define	FARMREPORTER3_H

#include "Type.h"
#include "Reporter.h"

class FarmReporter3 : public Reporter {
    DISALLOW_COPY_AND_ASSIGN_(FarmReporter3);
    PROPERTY(DoubleVector, daily_case_fataolity);
    
public:
    FarmReporter3();    
    virtual ~FarmReporter3();
    
    virtual void DailyReport(Model* model);

    virtual void BeforeRunReport(Model* model);
    virtual void AfterRunReport(Model* model);
    
private:

};

#endif	/* FARMREPORTER3_H */

