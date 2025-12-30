#include <iostream>
#include <fstream>

#include "../include/Report.hpp"
#include "../include/Analyzer.hpp"
#include "../include/TextReader.hpp"

int main(){
    TextReader reader("data/DomCasmurro.txt");

    if(!reader.isOpen()){
        cerr<<"Error while opening input file.\n";
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

    cout<<"Finished processing. Check output.txt.\n";
    return 0;
}