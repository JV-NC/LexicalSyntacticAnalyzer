#include "../include/Report.hpp"
#include <iomanip>

Report::Report(Analyzer &a, ostream &output): analyzer(a), out(output) {}

void Report::printLine(char c, int n){
    for(int i=0; i<n; i++)
        out<<c;
    out<<'\n';
}
void Report::printTitle(const string &title){
    printLine('=',150);
    out<<"=>"<<setw(120)<<right<<title<<'\n';
    printLine('=',150);
}

void Report::printPartialResult(){

}
void Report::printParagraphPartial(int paragraphNumber){

}
void Report::printFullResult(){
    HashTable &hash = analyzer.getTokens();
    int tableSize = hash.getTableSize();

    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<setw(15)<<"POSITIONS\n";

    printLine('-',150);

    for(int i=0; i<tableSize; i++){
        LinkedList<Token> &bucket = hash.getBucket(i);
        Node<Token> *node = bucket.getHead();

        while(node){
            Token &token = node->data;

            out<<left<<setw(20)<<token.getText()<<setw(12)<<token.getFrequency();

            Node<Occurrence> *occNode = token.getOccurrences().getHead();

            bool first = true;

            while(occNode){
                Occurrence &occ = occNode->data;

                if(!first){
                    out<<setw(20)<<" "<<setw(12)<<" ";

                }

                out<<setw(15)<<occ.paragraph<<setw(15)<<occ.sentence<<setw(15)<<occ.line<<setw(15)<<occ.position<<endl;

                first = false;
                occNode = occNode->next;
            }

            printLine('-',150);
            node = node->next;
        }
    }
}

void Report::printSentenceStats(){

}
void Report::printParagraphStats(){

}

void Report::generate(){
    printTitle("### START PROCESS ###");

    printTitle("### PARTIAL RESULT ###");
    printPartialResult();

    printTitle("### FULL RESULT ###");
    printFullResult();

    printSentenceStats();
    printParagraphStats();

    printTitle("### END PROCESS ###");
}