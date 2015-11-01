//
//  Main.cpp
//  
//
//  Created by Fabian Kern on 01.11.15.
//
//

#include "Main.hpp"


using namespace std;

/*
 * Converts Illumina 1.8+ coded input-data by extracting quality values and transformation into Phred quality scores.
 * The first argument is the input file usually given as .fastq file.
 * The second argument is optional and defines the name and type of the output file.
 * If omitted out.txt will be used.
 * This source code ensures compatibility with the C++98 standard and above.
 * If the first or third line of the input-file does not fulfill the Illumina 1.8+ standard beginning characters the program quits with an useful error-report.
 * Every fourth line gets converted into Phred quality scores.
 */
int main(int argc, char* argv[]){
    ifstream fastq(argv[1]);
    const char* outfile = argv[2];
    
    if (fastq.is_open()){
        if(outfile == NULL){
            string def = "out.txt";
            outfile = def.c_str();
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