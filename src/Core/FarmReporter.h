/* 
 * File:   FarmReporter.h
 * Author: merlin
 *
 * Created on May 21, 2012, 11:22 AM
 */

#ifndef FARMREPORTER_H
#define	FARMREPORTER_H

#include "Reporter.h"
#include "Type.h"

class FarmReporter : public Reporter {
    DISALLOW_COPY_AND_ASSIGN_(FarmReporter);
    PROPERTY(DoubleVector, daily_case_fataolity);
public:
    FarmReporter();

    virtual ~FarmReporter();

    virtual void DailyReport(Model* model);   
    
    virtual void BeforeRunReport(Model* model);
    virtual void AfterRunReport(Model* model);
private:

};

#endif	/* FARMREPORTER_H */

