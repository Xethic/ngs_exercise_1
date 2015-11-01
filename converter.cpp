//
//  converter.cpp
//  
//
//  Created by Fabian Kern on 01.11.15.
//
//

#include "converter.hpp"

using namespace std;

string convertFromSangerToPhred(string input){
    if(input == ""){
        cout << "Read empty-line. Please check your input file.\n";
        return "";
    }
    stringstream output;
    for(int i = 0; i < input.length(); i++){
        int curr = input[i];
        curr -= 33;
        output << curr;
        output << " ";
    }
    return output.str()+"\n";
}