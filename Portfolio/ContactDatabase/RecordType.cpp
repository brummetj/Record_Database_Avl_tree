//
//  DataType.cpp
//  Data Structures Final Project
//
//  Created by Joshua Brummet on 3/15/16.
//  Copyright © 2016 C++. All rights reserved.
//

#include "RecordType.h"
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::cin;


int RecordType::__idGen = 0;

//Constructor
RecordType::RecordType()
{
        ID = 0;
        firstName = "";
        middleName = "";
        lastName = "";
        company = "";
        address = "";
        city = "";
        state = "";
        country = "";
        email = "";
        HomePhone = "";
        OfficePhone = "";
        mobilePhone = "";
        ZipCode = "";
        a__first = "";
        a__last = "";
        a__email = "";
        a__mobile = "";
        __afffiliate.reserve(20); // Reserving atleast 20 elements spots for affiliates. Save time. 
    
}


//******************* SET FUNCTIONS *************************

void RecordType::setRecord(int __id, string __first, string __middle, string __last, string __comp, string __add, string iCity, string __State, string __Country, string __Email, string __HomePhone, string __Office, string __mobile, string __zip)
{
    
    ID = __id;
    firstName = __first;
    middleName = __middle;
    lastName = __last;
    company = __comp;
    address = __add;
    city = iCity;
    state = __State;
    country = __Country;
    HomePhone = __HomePhone;
    OfficePhone = __Office;
    mobilePhone = __mobile;
    email = __Email;
    ZipCode = __zip;
}

void RecordType::setField(unsigned int index, string entry) {
    
    switch (index)
    {
        case 0: firstName = entry;
            break;
        case 1: middleName = entry;
            break;
        case 2: lastName = entry;
            break;
        case 3: company = entry;
            break;
        case 4: HomePhone = entry;
            break;
        case 5: OfficePhone = entry;
            break;
        case 6: email = entry;
            break;
        case 7: mobilePhone = entry;
            break;
        case 8: address = entry;
            break;
        case 9: city = entry;
            break;
        case 10: state = entry;
            break;
        case 11: ZipCode = entry;
            break;
        case 12: country = entry;
            break;
        default: break;
    }
}


void RecordType::setAffiliate(string __first, string __last, string __mobile, string __email)
{
    a__first = __first;
    a__last = __last;
    a__mobile = __mobile;
    a__email = __email;
    __afffiliate.push_back(__first);
    __afffiliate.push_back(__last);
    __afffiliate.push_back(__mobile);
    __afffiliate.push_back(__email);
}

void RecordType::setVector(std::vector<std::string> v)
{
    
    __afffiliate = v;
}

std::vector<string> RecordType::returnAff()
{
    
    return __afffiliate;
    
    
}



bool RecordType::getAffiliates(string i) const
{
    std::vector<string> data;
    
    for (int k = 0; k < __afffiliate.size(); ++k)
    {
        
        if (i == __afffiliate[k])
        {
            return true;
            
        }
        
    }
    
    return false;
}

string RecordType::Affiliates(string i) const
{
    std::vector<string> data;
    std::string d;
    
    for (int k = 0; k < __afffiliate.size(); ++k)
    {
        
        if (i == __afffiliate[k])
        {
            d =  __afffiliate[k];
            
        }
        
    }
    
    return d;
}

//***********************************

//****** Functions for return Certain values of RecordBase ****

//****************************************

//Print Functions
const string &RecordType::getField(unsigned int index) const
{
    switch (index)
    {
        case 0: return  firstName;
        case 1: return  middleName;
        case 2: return  lastName;
        case 3: return  company;
        case 4: return  HomePhone;
        case 5: return  OfficePhone;
        case 6: return  email;
        case 7: return  mobilePhone;
        case 8: return  address;
        case 9: return  city;
        case 10: return state;
        case 11: return ZipCode;
        case 12: return country;
        default: return country;
    }
}

//Print Functions
void RecordType::printf()
{
    int i = 1;
    cout << "ID #: " << getID() << endl;
    cout << "First Name: " << getFirst() << endl;
    cout << "Middle Name: " << getMiddle() << endl;
    cout << "Last Name: " << getLast() << endl;
    cout << "Company: " << getCompany() << endl;
    cout << "Home Phone: " << getHomePhone() << endl;
    cout << "Office Phone: " << getOfficePhone() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Street Address: " << getAddress() << endl;
    cout << "City: " << getCity() << endl;
    cout << "State: " << getState() << endl;
    cout << "Zip Code: " << getZip() << endl;
    cout << "Country: " << getCountry() << endl;
    for (int index = 0; index < __afffiliate.size(); index += 4)
        {
            cout << "Affiliate " << i <<": ";
            cout << __afffiliate[index] << " " << __afffiliate[index+1];
            if (__afffiliate[index+2]=="")
            {
                cout << endl;
            }
            else if (__afffiliate[index+3]=="")
            {
                cout << endl;
            }
            else
            cout << ", " << __afffiliate[index+2] << ", " << __afffiliate[index+3] << endl;
            ++i;
        }

}

//***************************************

//outstream to file.
std::ostream &operator<<(std::ostream &os, const RecordType &contact)
{
    int i = 1;
    os << contact.getID() << endl;
    os << contact.getFirst() << endl;
    os << contact.getMiddle() << endl;
    os << contact.getLast() << endl;
    os << contact.getCompany() << endl;
    os << contact.getHomePhone() << endl;
    os << contact.getOfficePhone() << endl;
    os << contact.getEmail() << endl;
    os << contact.getMobilePhone() << endl;
    os << contact.getAddress() << endl;
    os << contact.getCity() << endl;
    os << contact.getState() << endl;
    os << contact.getZip() << endl;
    os << contact.getCountry() << endl;
    for (int index = 0; index < contact.__afffiliate.size(); index += 4)
    {
        os << "Affiliate " << i <<": ";
        os << contact.__afffiliate[index] << " " << contact.__afffiliate[index+1];
        os << ", " << contact.__afffiliate[index+2] << ", " << contact.__afffiliate[index+3] <<endl;
        ++i;
    }
    
    return os;
    
}


//overloaded istream for streaming into a record file. 
std::istream &operator>>(std::istream &is, RecordType& contact)
{
   
    string  a_first, a_last, a_phone, a_email;
    string line;
    
is >> contact.ID;
  if(!is)
      return is;
    
  else
   getline(is,line);
   while(!is.eof() && line != "|" && !is.fail())
   {
    
       for (int i = 0; i < RecordType::NUM_FIELD; ++i)
       {
           getline(is,line);
           std::istringstream ss(line);
           contact.setField(i,line);
       }
       getline(is,line);
       while(line != "|")
       {
         std::istringstream iss(line);
           iss >> a_first;
           getline(iss,a_last, ',');
           getline(iss,a_phone, ',');
           getline(iss,a_email);
       
        contact.setAffiliate(a_first, a_last, a_phone, a_email);
        getline(is,line);
       }
       
   }
    
    return is;
}


//***************Create a Record From user**********
RecordType RecordType::CreateRecord()
{
    RecordType Record;
    string firstName, middleName, lastName, company, address,
    city, state, country, email, affiliates, HomePhone, OfficePhone,mobilePhone, ZipCode,
    //Strings for affiliates.
    a_f = "", a_l ="", a_e = "", a_p = "";
    
    //Num iterator
    int num;
    
    cin.ignore();
    cout << "Enter First Name " << endl;
    getline(cin,firstName);
    cout << "Enter Middle Name " << endl;
    getline(cin,middleName);
    cout << "Enter Last Name " << endl;
    getline(cin,lastName);
    cout << "Enter Company " << endl;
    getline(cin,company);
    cout << "Enter Home number " << endl;
    getline(cin,HomePhone);
    cout << "Enter Office Phone Number " << endl;
    getline(cin,OfficePhone);
    cout << "Enter Mobile Phone Number " << endl;
    getline(cin,mobilePhone);
    cout << "Enter city of which the person lives in " << endl;
    getline(cin,city);
    cout << "Enter state " << endl;
    getline(cin,state);
    cout << "Enter country" << endl;
    getline(cin,country);
    cout << "Enter Email" << endl;
    cin.ignore();
    getline(cin,email);
    cout << "Street Address" << endl;
    getline(cin,address);
    cout << "Enter ZipCode" << endl;
    cin >> ZipCode;
    cout << "Enter number of Affiliates for person";
    cin >> num;

    for (int i = 0; i < num; ++i)
    {
    cout << "Enter Affiliate #" <<  i +1 << ":" << endl;
    cout << "First Name " << endl;
    cin >> a_f;
    cout << "Last Name " << endl;
    cin >> a_l;
    cout << "Phone Number " << endl;
    cin >> a_p;
    cout << "Email " << endl;
    cin >> a_e;

    Record.setAffiliate(a_f, a_l, a_p, a_e);
    }
    int ID;
    cout << "ID Number for Contact to store" << endl;
    cin >> ID;

    Record.setRecord(ID,firstName, middleName, lastName, company, address, city, state, country, email, HomePhone, OfficePhone, mobilePhone, ZipCode);

    return Record;
}
void RecordType::DeleteAffiliate(std::string a)
{
    
    for (auto it = __afffiliate.begin(); it != __afffiliate.end(); it++)
    {
        
        if (*it == a)
        {
            __afffiliate.erase(it);
            __afffiliate.erase(it);
            
            __afffiliate.erase(it); // __affiliates stores " " for Email, and Phone if not there. Deletes anyway.
            __afffiliate.erase(it);
                    break;
        }
        
    }
    
}
void RecordType::ModifyAff(std::string a, string b)
{
    string temp;
    int i = 0;
    for (auto it = __afffiliate.begin(); it != __afffiliate.end(); it++)
    {
        if (*it == a)
        {
            __afffiliate.erase(it);
            __afffiliate.insert(__afffiliate.begin()+i,b);
        }
        ++i;
    }

}

bool RecordType::ContainsAff(std::string a)
{
   
    for (int i =0; i < __afffiliate.size(); i++)
    {
        std::size_t found = __afffiliate[i].find(a);
        if (found != std::string::npos)
            return true;
        
    }

    return false;
    
}


