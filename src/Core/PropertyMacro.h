/* 
 * File:   PropertyMacro.h
 * Author: merlin
 *
 * Created on May 4, 2012, 10:44 AM
 */

#ifndef PROPERTYMACRO_H
#define	PROPERTYMACRO_H

#include <iostream>

#define PROPERTY(property_type, property_name)\
    private:\
        property_type property_name##_;\
    public:\
        property_type property_name() const{ return property_name##_; }\
        void set_##property_name(const property_type& value){ property_name##_ = value;}

#define POINTER_PROPERTY(property_type, property_name)\
    private:\
        property_type* property_name##_;\
    public:\
        property_type* property_name() const{ return property_name##_; }\
        void set_##property_name(property_type* value){ property_name##_ = value;}

#define READ_ONLY_PROPERTY(property_type, property_name)\
    private:\
        property_type property_name##_;\
    public:\
        property_type property_name() const{ return property_name##_; }

#define WRITE_ONLY_PROPERTY(property_type, property_name)\
    private:\
        property_type property_name##_;\
    public:\
        void set_##property_name(const property_type& value){ property_name##_ = value;}

#define READ_ONLY_POINTER_PROPERTY(property_type, property_name)\
    private:\
        property_type* property_name##_;\
    public:\
        property_type* property_name() const{ return property_name##_; }
        
#define DISALLOW_ASSIGN_(type)\
    private:\
        void operator=(type const &);

#define DISALLOW_COPY_(type)\
    private:\
        type(type const &);\

#define DISALLOW_COPY_AND_ASSIGN_(type)\
    private:\
        DISALLOW_COPY_(type)\
        DISALLOW_ASSIGN_(type)\
        

#define PROPERTY_HEADER(property_type, property_name)\
    private:\
        property_type property_name##_;\
    public:\
        property_type property_name() const;\
        void set_##property_name(property_type value);\
        

#define POINTER_PROPERTY_HEADER(property_type, property_name)\
    private:\
        property_type* property_name##_;\
    public:\
        property_type* property_name() const;\
        void set_##property_name(property_type* value);\
        

#define VIRTUAL_PROPERTY(property_type, property_name)\
    private:\
        property_type property_name##_;\
    public:\
        virtual property_type property_name() const{ return property_name##_; }\
        virtual void set_##property_name(const property_type& value){ property_name##_ = value;}
        
#endif	/* PROPERTYMACRO_H */

