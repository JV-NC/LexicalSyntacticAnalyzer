#include <iostream>
#include <fstream>

#include "../include/Report.hpp"
#include "../include/Analyzer.hpp"
#include "../include/TextReader.hpp"

int main(int argc, char* argv[]){
    if(argc<2){
        cerr<<"Usage: ./LSA <input_text_file>\n";
        return 1;
    }

    TextReader reader(argv[1]);

    if(!reader.isOpen()){
        cerr<<"Error while opening input file: "<<argv[1]<<endl;
        return 1;
    }

    Analyzer analyzer("data/stopwords.txt", "data/expressoes.txt");

    analyzer.analyze(reader);

    ofstream output("output/output.txt");
    if(!output.is_open()){
        cerr<<"Error while creating output.txt.\n";
        return 1;
    }

    Report report(analyzer, output);
    report.generate();

    output.close();

    cout<<"Finished processing. Check output/output.txt.\n";
    return 0;
}