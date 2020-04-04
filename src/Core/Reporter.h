/* 
 * File:   Reporter.h
 * Author: merlin
 *
 * Created on May 20, 2012, 1:53 PM
 */

#ifndef REPORTER_H
#define	REPORTER_H

#include "PropertyMacro.h"


class Model;

class Reporter {
    DISALLOW_COPY_AND_ASSIGN_(Reporter);

public:
    Reporter();

    virtual ~Reporter();

    virtual void DailyReport(Model* model) = 0;
    
    virtual void BeforeRunReport(Model* model) = 0;
    virtual void AfterRunReport(Model* model) = 0;

private:

};

#endif	/* REPORTER_H */

