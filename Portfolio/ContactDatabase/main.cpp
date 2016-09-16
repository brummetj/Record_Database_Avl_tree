#include <iostream>
#include <string>
#include <fstream>
#include "RecordType.h"
#include "RecordList.h"

using namespace std;


int main() {
    
    fstream file;
    file.open("data.txt");
    RecordList cl;
    
    
    cl.Mainmenu();
    
    
    return 0;
}
