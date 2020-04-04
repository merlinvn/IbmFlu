/* 
 * File:   ConsoleDailyReporter.h
 * Author: merlin
 *
 * Created on May 20, 2012, 1:56 PM
 */

#ifndef CONSOLEDAILYREPORTER_H
#define	CONSOLEDAILYREPORTER_H

#include "PropertyMacro.h"
#include "Reporter.h"

class ConsoleReporter : public Reporter {
    DISALLOW_COPY_AND_ASSIGN_(ConsoleReporter);
public:
    ConsoleReporter();
    virtual ~ConsoleReporter();

    virtual void DailyReport(Model* model);    
    
    virtual void BeforeRunReport(Model* model);
    virtual void AfterRunReport(Model* model);
private:

};

#endif	/* CONSOLEDAILYREPORTER_H */

