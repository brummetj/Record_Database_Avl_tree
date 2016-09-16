//
//  DataType.H
//  Data Structures Final Project
//
//  Created by Joshua Brummet on 3/14/16.
//  Copyright © 2016 C++. All rights reserved.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#ifndef DataType_h
#define DataType_h

using std::string;

class RecordType
{
    
//Constant static Variables
static const int NUM_FIELD = 13;

    
private:
    //Affiliate class for modification.    
    
    
    //Data member variables for RecordType
    
    int
    ID;
    static int
    __idGen;
    
    //A contacts Member Information Variables
    string
    firstName,
    middleName,
    lastName,
    company,
    address,
    mobilePhone,
    city,
    state,
    country,
    email,
    HomePhone,
    OfficePhone,
    ZipCode;
    
    //Affiliates
    string a__first,
    a__last,
    a__mobile,
    a__email;
    
    //Vector for holding affiliates
    std::vector<std::string> __afffiliate;
    
public:
    //Default constructor for empty RecordType.
    RecordType();
    
    //Functions for initializing a new record
    void setRecord(int __id,
                   string __first,
                   string __middle,
                   string __last,
                   string __comp,
                   string __add,
                   string iCity,
                   string __State,
                   string __Country,
                   string __Email,
                   string __HomePhone,
                   string __Office,
                   string __mobile,
                   string __zip);
    
    void setAffiliate(string __first,
                      string __last,
                      string __mobile,
                      string __email);

    

    
    //used to modify current record type
    void setField(unsigned int index, string entry);
    
    /*****Mutators*****/
    
    void setVector(std::vector<std::string> v);
    void setFirst( string first )
    {firstName = first;}
    void setMiddle( string middle )
    {middleName = middle;}
    void setLast( string Last )
    {lastName = Last;}
    void setCompany( string Comp )
    {company = Comp;}
    void setAddress( string addy )
    {address = addy;}
    void setCity( string iCity )
    {city = iCity;}
    void setState( string iState )
    {state = iState;}
    void setCountry( string iCountry )
    {country = iCountry;}
    void setEmail( string iEmail )
    {email = iEmail;}
    void setHomePhone( string iHome )
    {HomePhone = iHome;}
    void setmobilePhone( string imobile)
    {mobilePhone = imobile;}
    void setOffice(string iOffice )
    {OfficePhone = iOffice;}
    void setZip( string iZip)
    {ZipCode = iZip;}
    void setID(int iID)
    {ID =iID;}

    /*****Accessors*****/
    
   const string getFirst() const
    {return firstName;}
   const string getMiddle() const
    {return middleName;}
   const string getLast() const
    {return lastName;}
   const string getCompany() const
    {return company;}
   const string getAddress() const
    { return address;}
   const string getCity() const
    {return city;}
   const string getState() const
    {return state;}
   const string getCountry() const
    {return country;}
   const string getEmail() const
    {return email;}
   const string getHomePhone() const
    {return HomePhone;}
   const string getOfficePhone() const
    {return OfficePhone;}
   const string getMobilePhone() const
    {return mobilePhone;}
   bool getAffiliates(string i) const;
   const int getID() const
    {return ID;}
   const string getZip() const
    {return ZipCode;}
   const string &getField(unsigned int index) const;
    std::vector<string> returnAff();
    
    //overloaded operators.. Friend functions.

    friend bool operator<(const RecordType& lhs, const RecordType& rhs)
    { return (lhs.getID() < rhs.getID()); }
    
    friend bool operator>=(const RecordType& lhs, const RecordType& rhs)
    { return (lhs.getID() >= rhs.getID()); }
    
    friend bool operator>(const RecordType& lhs, const RecordType& rhs)
    { return (lhs.getID() > rhs.getID()); }
    
    friend bool operator<=(const RecordType& lhs, const RecordType& rhs)
    {return (lhs.getID() <= rhs.getID());  }
    
    friend bool operator==(const RecordType& lhs, const RecordType& rhs)
    { return (lhs.getID() == rhs.getID()); }
    
    friend bool operator!=(const RecordType& lhs, const RecordType& rhs)
    { return !(lhs == rhs); }
    
    string &operator[](unsigned int index);

    
    //Friend overloaded operator.
    friend std::ostream &operator<<(std::ostream &os, const RecordType &contact);
    friend std::istream &operator>>(std::istream &is, RecordType &contact);
    
    
    //Creating a new record.
    RecordType CreateRecord();
    
    //Return Value, Used for sorting data.
    void DeleteAffiliate(string a);
    void ModifyAff(string a,string b);
    string Affiliates(string i) const;
    
    string getWordN(string str);
    bool ContainsAff(std::string a);
    
    //printing field
    void printf();
    
};



#endif /* DataType_h */
