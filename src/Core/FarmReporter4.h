/* 
 * File:   FarmReporter4.h
 * Author: merlin
 *
 * Created on August 17, 2012, 10:31 AM
 */

#ifndef FARMREPORTER4_H
#define	FARMREPORTER4_H

#include "Type.h"
#include "Reporter.h"

class FarmReporter4 : public Reporter {
    DISALLOW_COPY_AND_ASSIGN_(FarmReporter4);
    PROPERTY(DoubleVector, daily_case_fataolity);
public:
    FarmReporter4();    
    virtual ~FarmReporter4();

    virtual void DailyReport(Model* model);

    virtual void BeforeRunReport(Model* model);
    virtual void AfterRunReport(Model* model);

private:

};

#endif	/* FARMREPORTER4_H */

