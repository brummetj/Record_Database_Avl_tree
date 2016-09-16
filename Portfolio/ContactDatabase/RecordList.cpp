//
//  ContactList.cpp
//  Data Structures Final Project
//
//  Created by Joshua Brummet on 4/24/16.
//  Copyright © 2016 C++. All rights reserved.
//



#include <iostream>
#include <fstream>
#include <vector>
#include "RecordList.h"
#include "RecordType.h"
#include "AVLtree.h"
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <iterator>

using std::cout;
using std::string;
using std::endl;
using std::cin;

class AVlTree;


RecordList::RecordList()
    {
        __tree = new AVLTree;
    }
    
    RecordList::~RecordList()
    {
        delete __tree;
    }

void RecordList::Mainmenu()
{

    /* Main Menu
     1. Load previous records
     2. add a record
     3. search records
     4. sort records by key
     5. modify a certain record
     6. save records
     7. exit records
     */
    int choice = 0;
    bool found = true;
    
    do
    {
        cout << "--------------" << endl;
        cout << "|  Main Menu  |" << endl;
        cout << "--------------" << endl;
        cout << "1. Load Records from file"<< endl;
        cout << "2. Add a Record to file" << endl;
        cout << "3. Print current Records" << endl;
        cout << "4. Search & modify Recods" << endl;
        cout << "5. Sort Records & Save sorted records to file" << endl;
        cout << "6. Save current records to file" << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        cout << "Please Note, Program is Case Sensitive." << endl << endl;
    
        
        cout << "Please enter your menu choice" << endl;
        cin >> choice;
        if (cin.fail())  {
                cout << "Invalid menu choice" << endl << endl;
            }
        cin.clear();
        cin.ignore(100, '\n');

        switch (choice)
        {
            case 1:
                MenuLoad(); found = true;
                break;
            case 2:
                MenuInsert(); found = true;
                break;
            case 3:
                MenuDisplay(); found = true;
                break;
            case 4:
                Menusearch(); found = true;
                break;
            case 5:
                MenuSort(); found = true;
                break;
            case 6:
                MenuSave(); found = true;
            case 7:
                found = true;
                return;
            default:
    
                break;
                
        }
        if (choice > 7 && choice != 0 )
        {
    
            cout << "Invalid choice returning back to main menu." << endl;
          
        }
      
        
    }
    while (found != false);
    

   
}
void RecordList::MenuLoad()
{
    
    string name;
    cout << "Please Enter the file name to load to database" << endl;
    
    std::cin >> name;
    
    std::ifstream open(name);
    loadContactsfromFile(name);

    
}


void RecordList::MenuDisplay()
{

    if (__tree->size() == 0)
    {
        cout << "Empty Database Please add new Records from Main Menu" << endl;
        return;
    }
    
    std::vector<RecordType> records;
    
    __tree->addtoVector(records);
    
    
    for (int i = 0; i <records.size(); ++i)
    {
        records[i].printf();
        cout << "|" << endl;
        
    }
    
}

void RecordList::MenuInsert()
{
    string choice;
    RecordType Record;
    RecordType Val;
    do
    {
        cout << "Please enter the following information for your new record. " << endl;
        Val = Record.CreateRecord();
        __tree->insert(Val);
        
        cout << endl;
        cout << endl;
        cout << "Would you like to add another record?" << endl;
        cin >> choice;
    }
    while (choice != "N" && choice != "No" && choice != "no" && choice != "n");
    
}

void RecordList::Menusearch()
{
    std::vector<RecordType> data, data1;
    
    int choice = 0;
    bool found = false;
    
    do
    {
        cout << "----- Search Menu ----" << endl;
        cout << "1. Search and Display" << endl;
        cout << "2. Search and Display (Contains) " << endl;
        cout << "3. Search and Modify" << endl;
        cout << "4. Search and Delete" << endl;
        cout << "5. Exit to main menu" << endl;
        
    
        cout << "Please enter your menu choice" << endl;
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid menu choice" << endl << endl;
            cin.clear();
            cin.ignore(100, '\n');
            return;
            }
        
        switch (choice)
        {
            case 1:
                GeneralSearch(); found = true;
                break;
            case 2:
                Contains_Search(); found = true;
                break;
            case 3:
                Modify_Search(); found = true;
                break;
            case 4:
                Delete_Search(); found = true;
                break;
            case 5:
                found = true;
                return;
                break;
                
        }
        
        if  (choice >5 && choice != 0)
        {
            cout << "Invalid choice returning back to main menu." << endl << endl;
            return;
            
        }
        
        
        
    }while (found != false);

}


void RecordList::MenuSort()
{
    
    int choice;
    std::vector<RecordType> rec;
    bool found = false;
    
    do
    {
    cout << "----- Sort Menu ----" << endl;
    cout << "1. Sort and Display" << endl;
        
    cout << "2. Sort Records by Type and Save" << endl;
    cout << "3. Exit to main menu" << endl;
    cout << endl;
        
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid menu choice" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            return;
            
        }
        
        switch (choice)
        {
            case 1:
                sort_and_Display(); found = true;
                break;
            case 2:
                Sort_and_Save(); found = true;
                break;
            case 3:return;
                break;

        }
        if  (choice >3 && choice != 0)
        {
            cout << "Invalid choice returning back to main menu." << endl << endl;
            return;
            
        }

    }while (found != false);
    
    
}

    
void RecordList::loadContactsfromFile(std::string fname)
    {
        std::vector<RecordType> rec;
        
        std::fstream file;
        file.open(fname);
        
        if(file.fail()) {
            
            cout << "error opening file" << endl;
            return;
        }
   
        std::string temp;
        
        while(!file.eof())
            {
                RecordType R;
                if(file >> R)
                __tree->insert(R);
                
            }
            file.close();
        
        cout << "Your Records Have been Loaded, type 3, to print your records from the file" << endl;
        
    }
    
std::ostream &operator<<(std::ostream &os, const RecordList &rl)
    {
        std::vector<RecordType> vec;
        
        rl.__tree->addtoVector(vec);
        
        for (auto &e : vec) {
            os << e << "|" << std::endl;
        }
        
        return os;
    }
    
std::istream &operator>>(std::istream &is, RecordList &rl)
    {
        while (!is.eof())
        {
            RecordType c;
            is >> c;
            if (c.getFirst() != "NULL")
                rl.__tree->insert(c);
        }
        
        return is;
    }

void RecordList::MenuSave()
{
    std::vector<RecordType> rec;
    
    __tree->addtoVector(rec);
    
    std::string yes;
    cout << "Do you wish to save your newly sorted records ? yes/no " << endl;
    cin >> yes;
    if (yes == "yes" || yes == "YES" || yes =="Yes")
    {
        
        std::ofstream data;
        std::string input;
        cout << "Please enter the name of the file you wish to save to! :-) " << endl;
        cin >> input;
        
        data.open(input.c_str());
        
        for (int i = 0; i < rec.size(); i++)
        {
            
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


