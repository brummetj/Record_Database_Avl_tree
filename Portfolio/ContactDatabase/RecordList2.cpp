//
//  ContactList2.cpp
//  Data Structures Final Project
//
//  Created by Joshua Brummet on 5/2/16.
//  Copyright © 2016 C++. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <vector>
#include "RecordList.h"
#include "RecordType.h"
#include "AVLtree.h"
#include "AVLnode.h"
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <stack>

using std::cout;
using std::string;
using std::endl;
using std::cin;

class AVlTree;


/******************************************
 *
 *          SEARCHING FUNCTIONS
 ******************************************/


void RecordList::Modify_Search() {
    
    if (__tree->size() == 0) {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    
    //adding data to vectors
    std::vector<RecordType> rec, data, data1;
    std::vector<std::string> stringData;

    __tree->addtoVector(data);
    cout << endl;
    //user input
    std::string name;
    cout << "____Search and Modify___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << "Affiliates ->    13" << endl;
    cout << endl;
    cout << "Enter the index number to search by." << endl;
    int index;
    cin >> index;
    cout << "Enter the Name/Number of the contact you are looking for to modify." << endl;
    cin >> name;

        //If found, insert that record into a seperate vector for futher use.
        for (int i =0; i < data.size(); ++i)  {
            
            if (index==13) {
                if (data[i].getAffiliates(name))
                    rec.push_back(data[i]);
            }
            
            else if (name == data[i].getField(index))
                rec.push_back(data[i]);
            }
    //Validate if its found or not.
        if (rec.empty())  {
            std::string choice;
            cout << "Your search was not found. Do you wish to try again? Yes/No." << endl;
            cin >> choice;
            if (choice == "NO" || choice == "no" || choice == "No")
                return;
            else
                Modify_Search();
        }
    //Printing results of search.. if any
        for(int i =0; i < rec.size(); ++i)  {
            rec[i].printf();
            cout << "|" << endl;
        }
    if (rec.size() > 0 ) {
        std::string results,again;
        //Can only Modify one record, needs to refine search, since output can be big.
        cout << "Is the record you're looking for? Please enter 'yes', else enter 'no' and refine your search to one record." << endl;
        cin >> results;
        int index1;
        
        while (results != "Yes" && results != "yes" && results != "YES") {
            //reentering more information to refine search.
            cout << "____Search and Modify___" << endl << endl;
            cout << "First Name ->    0" << endl;
            cout << "Middle Name ->   1" << endl;
            cout << "Last Name ->     2" << endl;
            cout << "Company ->       3" << endl;
            cout << "Home Phone ->    4" << endl;
            cout << "Office Phone ->  5" << endl;
            cout << "Email ->         6" << endl;
            cout << "Mobile Phone ->  7" << endl;
            cout << "Street Address-> 8" << endl;
            cout << "City ->          9" << endl;
            cout << "State ->         10" << endl;
            cout << "ZipCode ->       11" << endl;
            cout << "Country ->       12" << endl;
            cout << "Affiliates ->    13" << endl;
            cout << endl;
            cout << "Enter the index number to search by." << endl;
            cin >> index1;
            cout << "Enter the Name/Number of the contact you are looking for to modify." << endl;
            cin >> again;

            for (int i = 0; i < rec.size(); ++i)
            {
        
                if (index1 == 13) {
                    if (rec[i].getAffiliates(again))
                        data1.push_back(rec[i]);
                }
                
                else if (again == rec[i].getField(index1))
                    data1.push_back(rec[i]);
                
            }
            
            if (data1.empty())  {
                std::string s;
                cout << "Couldn't find the record do you want to try again? yes/no" << endl << endl;
                cin >> s;
                if (s == "Yes" || s == "YES" || s == "yes")
                    break;
                else
                    return;
                
            }
            for (int i= 0; i < data1.size(); ++i)  {
                data1[i].printf();
                cout << "|" << endl;
            }
            if (data1.size() >0)  {
                cout << "Is this the Record you want to modify? yes/no" << endl;
                cin >> results;
                if (results == "No" || results == "NO" || results == "no")
                {
                    std::string again;
                    cout << "Would you like to search again?" << endl;
                    cin.ignore();
                    cin >> again;
                    if (again == "YES" || again == "Yes" || again == "yes")
                        Modify_Search();
                    else
                        return;
                }
            }
        }
        RecordType R, S;
        std::string m;
        //Modify one more Fields, by entry, allowing a user to fully change the Record. 
      do {
        cout << endl;
        std::string modify;
        cout << "____Modify by field___" << endl << endl;
        cout << "First Name ->    0" << endl;
        cout << "Middle Name ->   1" << endl;
        cout << "Last Name ->     2" << endl;
        cout << "Company ->       3" << endl;
        cout << "Home Phone ->    4" << endl;
        cout << "Office Phone ->  5" << endl;
        cout << "Email ->         6" << endl;
        cout << "Mobile Phone ->  7" << endl;
        cout << "Street Address-> 8" << endl;
        cout << "City ->          9" << endl;
        cout << "State ->         10" << endl;
        cout << "ZipCode ->       11" << endl;
        cout << "Country ->       12" << endl;
        cout << "Affiliates ->    13" << endl;
        cout << endl;
        cout << "Enter the index number to modify" << endl;
        int index2;
        cin >> index2;
        if (index2 == 13)  {
            std::string aff, a;
            cout << "Do you wish to delete/add a # of Affiliates or modify a current one?" << endl;
            cin >> aff;
            
            if (aff == "Delete" || aff == "delete")  {
                do {
                    std::stack<string> temp; std::string del;
                    
                    cout << "Enter the first name of the Affiliate to delete" << endl;
                    cin >> del;
                    
                if (data1[0].getAffiliates(del)) {  //if contact name contains
                    data1[0].DeleteAffiliate(del);
                    cout << "Affiliate delete, Delete another? yes/no " << endl;
                    cout << "Please enter your answer twice. " << endl;
             
                    cin >> a; //user needs to enter Yes/No twice inside the program. Not sure how to get around it, i have tried multiple methods to try and get around this problem and did not succeed. Please enter the answer twice.
                }
                else{
                    cout << "Cant find the first name of the affiliate to delete try again? yes/no" << endl;
                    cout << "Please enter your answer twice. " << endl;
                    cin >> a;
                    break;
                }
                    
                    
                }while (a != "NO" && a != "no" && a != "No");
                                        
            }
            if (aff == "Modify" || aff == "modify" ) {
                std::string m,n,a;
                do {
                    cout << "Enter the name of affiliates information that you wish to modify" << endl << endl;
                    cout << "First Name || Last Name || Phone Number || Email" << endl;
                    cin >> m;
                    cout << "What do you wish to change it to?" << endl;
                    cin >> n;
                    data1[0].ModifyAff(m,n);
                    
                    
                    cout << "Do you want to change more? yes/no " << endl;
                    cout << "Please enter your answer twice. " << endl;
                    cin >> a;
                    cin.ignore();
                }while(a != "NO" && a != "no" && a != "No");
                
            }
            if (aff == "Add" || aff == "add") {
                std::string a_f,a_l,a_p,a_e , b;
                do {
                cout << "Please enter your contacts new affiliates information, if you wish to skip a line please hit enter." << endl << endl;
                cout << "First Name || Last Name || Phone Number || Email" << endl;
                    cin.ignore();
                    getline(cin,a_f);
                    getline(cin,a_l);
                    getline(cin,a_p);
                    getline(cin,a_e);
                data1[0].setAffiliate(a_f, a_l, a_p, a_e);
                
                cout << "Do you want to add more? yes/no " << endl;
                cout << "Please enter your answer twice. " << endl;
                cin >> b;
                }while(b != "NO" && b != "no" &&  b != "No");
            }
            
        }
        else
          cout << "Enter the new information for the contact." << endl;
          cin >> modify;
        
        //First element of the vector, should be the record to modify, (can only modify one record).
        R = data1[0];
        data1[0].setField(index2,modify);
        
        __tree->remove(R);
        
        __tree->insert(data1[0]);
        
        cout << "This is youre new Contact" << endl;
        data1[0].printf();
        cout << "Do you wish to edit more fields of the contact? yes/no." << endl;
        cin >> m;
          
      }
        while( m != "No" && m != "NO" && m != "no");
    }
}
/****************************************************/


void RecordList::Contains_Search()
{
    
    if (__tree->size() == 0)  {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    //Vectors for Searching (contains)
    std::vector<RecordType> rec, data, data1;
    
    //Adding to vector contents of the AVL TREE.
    __tree->addtoVector(rec);
    cout << endl;
    std::string name;
    
    //Getting User Input
    cout << "____Search and Diplay (contains)___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << endl;
    cout << "Enter the index number to search by." << endl;
    int index;
    cin >> index;
    cout << "Enter the letters/numbers of which your contact contains" << endl;
    cin >> name;
    
    std::string str;
    
    for (int i = 0; i < rec.size(); i++) {
        
        if (index == 13)
        {
            
            if (rec[i].ContainsAff(name) == true)
                data.push_back(rec[i]);
            
        }
        else if (index != 13)
        {
            
        std::size_t found = rec[i].getField(index).find(name); // using string .Find() to intialize size_t found to string size of name.
        
                if(found != std::string::npos )
                    data.push_back(rec[i]); //returns the finding string in datatype adding it to the data vector
        
        }
    }
    //printing data
    for (int i =0; i < data.size(); ++i) {
        data[i].printf();
        cout << "|" << endl;
        }
    
    
    //If SEARCH (contains) didn't contain the letters or words you were looking for.
    if (data.empty()) {
        std::string choice;
        cout << "Your search was not found. Do you wish to try again? Yes/No." << endl;
        cin >> choice;
        if (choice == "NO" || choice == "no" || choice == "No")
            return;
        else
            Contains_Search();
    }
    cout << endl << endl;
    
    //If SEARCH (contains) did find the words/letters you were looking for
    if (data.size() >0) {
    std::string more;
        cout << "Do you wish to search more within these records? yes/no" << endl;
    cin >> more;
        
        
    // SUB SEARCH
    if (more == "Yes" || more == "YES" || more == "yes"){
    
        cout << endl;
        std::string name1;
        cout << "____Search and Diplay (contains)___" << endl << endl;
        cout << "First Name ->    0" << endl;
        cout << "Middle Name ->   1" << endl;
        cout << "Last Name ->     2" << endl;
        cout << "Company ->       3" << endl;
        cout << "Home Phone ->    4" << endl;
        cout << "Office Phone ->  5" << endl;
        cout << "Email ->         6" << endl;
        cout << "Mobile Phone ->  7" << endl;
        cout << "Street Address-> 8" << endl;
        cout << "City ->          9" << endl;
        cout << "State ->         10" << endl;
        cout << "ZipCode ->       11" << endl;
        cout << "Country ->       12" << endl;
        cout << endl;
        cout << "Enter the index number to search by." << endl;
        int index1;
        cin >> index1;
        cout << "Enter the letters/numbers of which your contact contains" << endl;
        cin >> name1;
        
        std::string str;
        
        for (int i = 0; i < data.size(); i++) {

            if (index1 == 13)
            {
                
                if (data[i].ContainsAff(name1) == true)
                    data1.push_back(data[i]);
                
            }
            else if (index1 != 13)
            {
                
                std::size_t found = data[i].getField(index1).find(name1); // using string .Find() to intialize size_t found to string size of name.
                
                if(found != std::string::npos )
                    data1.push_back(data[i]); //returns the finding string in datatype adding it to the data vector
                
            } //returns the finding string in datatype adding it to the data vector
        }
        
        if (data1.empty()) {
            std::string p;
            cout << "Couldn't Find any contacts that contain what you're looking for within the previous search. Do you wish to try again? yes/no " << endl;
            cin >> p;
            if (p == "Yes" || p == "YES" || p == "yes")
                Contains_Search();
            else
                return;
            
        }
        
        //Printing records
        for (int i =0; i < data1.size(); ++i) {
            
            data1[i].printf();
            cout << "|" << endl;
        }
        
        std::string m;
        cout << "Do you wish to Search again?" << endl;
        cin >> m;
        
        if (m == "Yes" || m == "yes" || m == "YES")
            Contains_Search();
        else
            return;
        
    }
    else
        return;
    }
}
/****************************************************/

void RecordList::GeneralSearch() {
    
    if (__tree->size() == 0) {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    
    std::vector<RecordType> data, data1;
    
    std::string name;
    cout << "____Search and Diplay___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << "Affiliates ->    13" << endl;
    cout << endl;
    cout << "Enter the index number to search by." << endl;
    int index;
    cin >> index;
    cout << "Enter the Name/Number of the contact you are looking for." << endl;
    cin >> name;
    
    __tree->addtoVector(data);
    
    std::vector<RecordType> rec;
    for (int i =0; i < data.size(); ++i) {
        if (index==13) {
            if (data[i].getAffiliates(name))
                rec.push_back(data[i]);
        }
        
        else if (name == data[i].getField(index)) {
            rec.push_back(data[i]);
        }
    }
    if (rec.empty()) {
        std::string choice;
        cout << "Your search was not found. Do you wish to try again? Yes/No." << endl;
        cin >> choice;
        if (choice == "NO" || choice == "no" || choice == "No")
            return;
        else
            GeneralSearch();
    }
    else
        
        //Printing results of search.. if any
        for(int i =0; i < rec.size(); ++i) {
            rec[i].printf();
            cout << "|" << endl;
        }
    
    //********************************************************
    //             Search again? :-)
    
    std::string results,again;
    
    cout << "Do you wish to continue searching within you're previous results? Yes/No." << endl;
    cin >> results;
    if(results == "No" || results == "no")
        return;
    else
        cout << "____Search and Diplay___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << "Affiliates ->    13" << endl;
    cout << endl;
        cout << "Enter the index number to search by." << endl;
    cin >> index;
    cout << "Enter the Name/Number of the contact you are looking for." << endl;
    cin >> again;
    for (int i = 0; i <rec.size(); ++i) {
        
        if (index==13) {
            if (data[i].getAffiliates(name))
                rec.push_back(data[i]);
        }
        
        if( again == rec[i].getField(index))
            data1.push_back(rec[i]);
        
    }
    for (int i= 0; i < data1.size(); ++i) {
        data1[i].printf();
        cout << "|" << endl;
        
    }
    
    
}

/****************************************************/

void RecordList::Delete_Search()
{
    if (__tree->size() == 0) {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    
    std::vector<RecordType> rec, data, data1;
    
    __tree->addtoVector(data);
    cout << endl;
    std::string name;
    cout << "____Search and Delete___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << "Affiliates ->    13" << endl;
    cout << endl;
    cout << "Enter the index number to search by." << endl;
    int index;
    cin >> index;
    cout << "Enter the Name/Number of the contact you are looking for to delete." << endl;
    cin >> name;
    
    for (int i =0; i < data.size(); ++i) {
        
        if (index==13) {
            if (data[i].getAffiliates(name))
                rec.push_back(data[i]);
        }
        
        else if (name == data[i].getField(index))
        {
            rec.push_back(data[i]);
        }
    }
    if (rec.empty()) {
        std::string choice;
        cout << "Your search was not found. Do you wish to try again? Yes/No." << endl;
        cin >> choice;
        if (choice == "NO" || choice == "no" || choice == "No")
            return;
        else
            Delete_Search();
    }
    
    //Printing results of search.. if any
    for(int i =0; i < rec.size(); ++i)
    {
        rec[i].printf();
        cout << "|" << endl;
    }
    
    
    if (rec.size() > 0 ) {
        std::string results,again;
        //Can only Delete one record, needs to refine search, since output can be big.
        cout << "Is the record you're looking for? Please enter 'yes', else enter 'no' and refine your search to one record." << endl;
        cin >> results;
        
        while (results != "Yes" && results != "yes" && results != "YES") {
            std::string name;
            cout << "____Search and Modify___" << endl << endl;
            cout << "First Name ->    0" << endl;
            cout << "Middle Name ->   1" << endl;
            cout << "Last Name ->     2" << endl;
            cout << "Company ->       3" << endl;
            cout << "Home Phone ->    4" << endl;
            cout << "Office Phone ->  5" << endl;
            cout << "Email ->         6" << endl;
            cout << "Mobile Phone ->  7" << endl;
            cout << "Street Address-> 8" << endl;
            cout << "City ->          9" << endl;
            cout << "State ->         10" << endl;
            cout << "ZipCode ->       11" << endl;
            cout << "Country ->       12" << endl;
            cout << "Affiliates ->    13" << endl;
            cout << endl;
            cout << "Enter the index number to search by." << endl;
            int index1;
            cin >> index1;
            cout << "Enter the Name/Number of the contact you are looking for to modify." << endl;
            cin >> name;
           
            for (int i =0; i < rec.size(); ++i)  {
                
                if (index1==13) {
                    if (rec[i].getAffiliates(name))
                        data1.push_back(rec[i]);
                }
                
                else if (name ==rec[i].getField(index1))
                    data1.push_back(rec[i]);
            }
            
            if (data1.empty()) {
                std::string s;
                cout << "Couldn't find the record do you want to try again? yes/no" << endl << endl;
                cin >> s;
                if (s == "Yes" || s == "YES" || s == "yes")
                    break;
                else
                    return;
                
            }
            
            for (int i= 0; i < data1.size(); ++i) {
                data1[i].printf();
                cout << "|" << endl;
                
            }
            if (data1.size() >0) {
                cout << "Is this the Record you want to Delete? yes/no" << endl;
                cin >> results;
            }
            
        }
        std::string choose;
        cout << "Are you sure you want to delete the following record? " << endl;
        data1[0].printf();
        cout << endl;
        cout << "The records information will be erased. yes/no" << endl;
        cin >> choose;
        if (choose == "Yes" || choose == "yes" || choose == "YES") {
            __tree->remove(data1[0]);
            
        cout << "The record has been deleted" << endl;
        
        }
        else
            return;
        
        
    }
}

/******************************************
 *
 *          SORTING FUNCTIONS
 ******************************************/
    
void RecordList::sort_and_Display() {
    
    if (__tree->size() == 0) {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
        
        std::vector<RecordType> rec;
        
        __tree->addtoVector(rec);
        cout << endl;
        cout << "____Sort and Diplay___" << endl << endl;
        cout << "First Name ->    0" << endl;
        cout << "Middle Name ->   1" << endl;
        cout << "Last Name ->     2" << endl;
        cout << "Company ->       3" << endl;
        cout << "Home Phone ->    4" << endl;
        cout << "Office Phone ->  5" << endl;
        cout << "Email ->         6" << endl;
        cout << "Mobile Phone ->  7" << endl;
        cout << "Street Address-> 8" << endl;
        cout << "City ->          9" << endl;
        cout << "State ->         10" << endl;
        cout << "ZipCode ->       11" << endl;
        cout << "Country ->       12" << endl;
        cout << endl;
        cout << "Enter the index number to sort your contacts by and display them" << endl;
        int index;
        cin >> index;
        if (index >13 || index < 0)
        {
            cout << "The index you entered doesn't match with a field, please try agian" << endl;
            cin >> index;
        }
        
        sortContact s(index);
        
        sort(rec.begin(),rec.end(),s);
        
        for (auto &e : rec)
        {
            e.printf();
            cout << "|" << endl;
        }
        
        
    }

void RecordList::Sort_and_Save() const {
    
    if (__tree->size() == 0) {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    
    std::vector<RecordType> rec, data;
    
    __tree->addtoVector(rec);
    __tree->addtoVector(data);
    
    cout << endl;
    cout << "____Sort and Save___" << endl << endl;
    cout << "First Name ->    0" << endl;
    cout << "Middle Name ->   1" << endl;
    cout << "Last Name ->     2" << endl;
    cout << "Company ->       3" << endl;
    cout << "Home Phone ->    4" << endl;
    cout << "Office Phone ->  5" << endl;
    cout << "Email ->         6" << endl;
    cout << "Mobile Phone ->  7" << endl;
    cout << "Street Address-> 8" << endl;
    cout << "City ->          9" << endl;
    cout << "State ->         10" << endl;
    cout << "ZipCode ->       11" << endl;
    cout << "Country ->       12" << endl;
    cout << endl;
    cout << "Enter the index number to sort your contacts by and display them" << endl;
    int index;
    cin >> index;
    if (index >13 || index < 0) {
        cout << "The index you entered doesn't match with a field, please try agian" << endl;
        cin >> index;
    }
    
    sortContact s(index);
    
    sort(rec.begin(),rec.end(),s);
    
    std::string yes;
    cout << "Your records have been sorted by the following field." << endl;
    cout << "Do you wish to save your newly sorted records ? yes/no " << endl;
    cin >> yes;
    if (yes == "yes" || yes == "YES" || yes =="Yes") {
        
        std::ofstream data;
        std::string input;
        cout << "Please enter the name of the file you wish to save to! :-) " << endl;
        cin >> input;
        
        data.open(input.c_str());
        
        for (int i = 0; i < rec.size(); i++) {
            data << rec[i];
            data << "|" << endl;
            
        }
        std::string you;
        cout << "Your File has now been saved. Do you want to return to the main menu? or exit program? Please enter 'main' if you wish to continue" << endl;
        cin >> you;
        if (you == "Main" || you == "main" || you == "MAIN")
            return;
        else
            exit(1);
        
    }
    else
        return;
   
}





