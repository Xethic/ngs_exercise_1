//
//  Main.cpp
//  
//
//  Created by Fabian Kern on 01.11.15.
//
//

#include "Main.hpp"


using namespace std;

int main(int argc, char *argv[]){
    ifstream fastq(argv[1]);
    string outfile = argv[2];
    
    if (fastq.is_open()){
        if(outfile == ""){
            outfile = "out.txt";
        }
        ofstream output;
        output.open(outfile, ofstream::out);
        string line;
        int counter = 0;
        while ( getline (fastq,line) ){
            switch (counter) {
                case 0:
                    if(line[0] != '@'){
                        cout << "Read: \n";
                        cout << line.at(0);
                        cout << " should be @\n";
                        cout << "No correct Illumina 1.8+ coded file!\n";
                        fastq.close();
                        output.close();
                        return 1;
                    }
                    counter++;
                    break;
                case 1:
                    counter++;
                    break;
                case 2:
                    if(line[0] != '+'){
                        cout << "Read: \n";
                        cout << line.at(0);
                        cout << " should be +\n";
                        cout << "No correct Illumina 1.8+ coded file!\n";
                        fastq.close();
                        output.close();
                        return 1;
                    }
                    counter++;
                    break;
                case 3:
                    counter = 0;
                    output << convertFromSangerToPhred(line);
                    break;
                default:
                    counter = 0;
            }
        }
        fastq.close();
        output.close();
    }
    else {
        cout << "File not found\n";
        return 1;
    }
    cout << "Done!\n";
    return 0;
}