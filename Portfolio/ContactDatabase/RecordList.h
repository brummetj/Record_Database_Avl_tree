//
//  ContactList.hpp
//  Data Structures Final Project
//
//  Created by Joshua Brummet on 4/24/16.
//  Copyright © 2016 C++. All rights reserved.
//

#ifndef ContactList_h
#define ContactList_h

#include <stdio.h>
#include <iostream>
#include <string>

#include "RecordType.h"
#include "AVLTree.h"
#include "AVLnode.h"


    class RecordList
    {
    public:
        RecordList();
        RecordList(std::string fname);
        ~RecordList();
        
        void loadContactsfromFile(std::string fname);
        
        friend std::ostream &operator<<(std::ostream &os, const RecordList &rl);
        friend std::istream &operator>>(std::istream &is, RecordList &rl);
        
        
        //Menu functions for Algorithms and Data Manipulation.
        void Mainmenu();
        
        void MenuDisplay(); // diplay contents of AVL tree
        
        void MenuLoad(); // load from file
        
        void Menusearch(); // display sub menu for searching
        
        void GeneralSearch(); // a general search
        
        void Contains_Search();// a search which outputs 
        
        void Modify_Search();
        
        void MenuSort();
        
        void Delete_Search();
        
        void MenuInsert();
        
        void MenuSave();
        
        void CreateRecord();
        
        void sort_and_Display();
        
        void Sort_and_Save() const;
        
        bool containsString(const std::string& s, char input[2]);
        

        class sortContact
        {
        public:
            sortContact() : field(0) {}
            sortContact(int index) { field = index; }
            
            bool operator()( const RecordType&lhs,const  RecordType&rhs ) {  return ( lhs.getField(field) < rhs.getField(field));}
        private:
            int field;
        };
        
    protected:
        AVLTree *__tree;
        
    };





#endif /* ContactList_h */
