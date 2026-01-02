#include "../include/Report.hpp"
#include <iomanip>
//TODO: implement paragraph/sentence stats
//TODO: implement stack for pontuation.
//TODO: implement expressions on paragraphPartial
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
    Queue<Paragraph> pq = analyzer.getParagraphs();
    Queue<Sentence> sq = analyzer.getSentences();
    LinkedList<HashTable<Token>>::Iterator it = analyzer.getSentenceTokens().begin();
    Paragraph p;
    int paragraphNumber = 1;
    
    while(!pq.isEmpty()){
        pq.dequeue(p);
        printParagraphPartial(p, sq, it);
        paragraphNumber++;
    }
}
void Report::printParagraphPartial(Paragraph p, Queue<Sentence> &sq, LinkedList<HashTable<Token>>::Iterator &tokenIt){
    for(int s=0; s<p.getTotalSentences(); s++){
        Sentence sent;
        sq.dequeue(sent);

        HashTable<Token> &hash = *tokenIt;
        ++tokenIt;

        printLine('_',150);

        out<<left<<setw(25)<<"WORD"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<setw(15)<<"FREQUENCY"<<"POSITIONS\n";

        printLine('-',150);

        for(int i=0; i<hash.getTableSize(); i++){
            LinkedList<Token> &bucket = hash.getBucket(i);

            for(LinkedList<Token>::Iterator it=bucket.begin(); it!= bucket.end(); it++){
                Token &token = *it;

                out<<left<<setw(25)<<token.getText()<<setw(15)<<sent.getParagraphNumber()<<setw(15)<<sent.getSentenceNumber();

                bool first = true;
                LinkedList<Occurrence> &occList = token.getOccurrences();
                for(LinkedList<Occurrence>::Iterator occIt=occList.begin(); occIt!=occList.end(); occIt++){
                    Occurrence occ = *occIt;
                    if(!first){
                        out<<setw(25)<<" "<<setw(15)<<" "<<setw(15)<<" ";
                    }
                    out<<setw(15)<<occ.line<<setw(15)<<token.getFrequency()<<setw(15)<<occ.position<<endl;
                    
                    first = false;
                }
            }
        }
        printLine('_',150);

        out<<"=> Number of words with stop words: "<<sent.getAllWords()<<setw(60)<<"=> Number of words without stop words: "<<sent.getNormalWords()<<endl;

        printLine('-',150);
    }

    printLine('_',150);
    out<<"=> Beginning paragraph in line: "<<p.getStartingLine()<<" Number of sentences: "<<p.getTotalSentences()<<endl;
    printLine('_',150);
}
void Report::printFullResult(){
    HashTable<Token> &hash = analyzer.getTokens();
    int tableSize = hash.getTableSize();

    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<setw(15)<<"POSITIONS\n";

    printLine('-',150);

    for(int i=0; i<tableSize; i++){
        LinkedList<Token> &bucket = hash.getBucket(i);

        for(LinkedList<Token>::Iterator itTokens=bucket.begin(); itTokens!=bucket.end(); itTokens++){
            Token &token = *itTokens;

            out<<left<<setw(20)<<token.getText()<<setw(12)<<token.getFrequency();

            bool first = true;

            for(LinkedList<Occurrence>::Iterator itOcc=token.getOccurrences().begin(); itOcc!=token.getOccurrences().end(); itOcc++){
                Occurrence &occ = *itOcc;

                if(!first){
                    out<<setw(20)<<" "<<setw(12)<<" ";

                }

                out<<setw(15)<<occ.paragraph<<setw(15)<<occ.sentence<<setw(15)<<occ.line<<setw(15)<<occ.position<<endl;

                first = false;
            }

            printLine('-',150);
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