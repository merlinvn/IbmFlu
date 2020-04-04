/* 
 * File:   FarmReporter2.h
 * Author: merlin
 *
 * Created on June 25, 2012, 1:23 PM
 */

#ifndef FARMREPORTER2_H
#define	FARMREPORTER2_H
#include "Reporter.h"
#include "Type.h"

class FarmReporter2 : public Reporter {
    DISALLOW_COPY_AND_ASSIGN_(FarmReporter2);
    PROPERTY(DoubleVector, daily_case_fataolity);
    
public:
    FarmReporter2();

    virtual ~FarmReporter2();

    virtual void DailyReport(Model* model);

    virtual void BeforeRunReport(Model* model);
    virtual void AfterRunReport(Model* model);
private:

};

#endif	/* FARMREPORTER2_H */

