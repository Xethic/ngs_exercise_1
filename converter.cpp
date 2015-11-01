//
//  converter.cpp
//  
//
//  Created by Fabian Kern on 01.11.15.
//
//

#include "converter.hpp"

using namespace std;

/*
 *  Converts a line of input quality values given as string into Phred quality scores.
 *  Because Illumina's quality values are defined as Phred+33, it substracts 33 on every parsed ascii value.
 *  If there's an empty line given an empty string will be returned.
 */
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