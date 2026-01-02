#include "../include/Report.hpp"
#include <iomanip>
//TODO: implement paragraph/sentence stats
//TODO: implement stack for pontuation.
Report::Report(Analyzer &a, ostream &output): analyzer(a), out(output) {}

void Report::printLine(char c, int n){
    for(int i=0; i<n; i++)
        out<<c;
    out<<'\n';
}
void Report::printTitle(const string &title){
    const int width = 150;
    printLine('=',width);
    int titleLen = title.size(); //"=> "
    int leftPadding = (width - titleLen) / 2;
    out<<"=>"<<string(leftPadding, ' ')<<title<<endl<<endl;
    printLine('=',width);
}

void Report::printPartialResult(){
    Queue<Paragraph> pq = analyzer.getParagraphs();
    Queue<Sentence> sq = analyzer.getSentences();
    LinkedList<HashTable<Token>>::Iterator tokensIt = analyzer.getSentenceTokens().begin();
    LinkedList<HashTable<Expression>>::Iterator expIt = analyzer.getParagraphExpressions().begin();
    Paragraph p;
    
    while(!pq.isEmpty()){
        pq.dequeue(p);
        printParagraphPartial(p, sq, tokensIt, expIt);
    }
}
void Report::printParagraphPartial(Paragraph p, Queue<Sentence> &sq, LinkedList<HashTable<Token>>::Iterator &tokenIt, LinkedList<HashTable<Expression>>::Iterator &expIt){
    for(int s=0; s<p.getTotalSentences(); s++){
        Sentence sent;
        sq.dequeue(sent);

        HashTable<Token> &hash = *tokenIt;
        ++tokenIt;

        printLine('_',150);

        out<<left<<setw(25)<<"WORD"<<setw(15)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<"POSITIONS\n";

        printLine('-',150);

        for(int i=0; i<hash.getTableSize(); i++){
            LinkedList<Token> &bucket = hash.getBucket(i);

            for(LinkedList<Token>::Iterator it=bucket.begin(); it!= bucket.end(); it++){
                Token &token = *it;

                out<<left<<setw(25)<<token.getText()<<setw(15)<<token.getFrequency()<<setw(15)<<sent.getParagraphNumber()<<setw(15)<<sent.getSentenceNumber();

                string lines;
                string positions;

                for(LinkedList<Occurrence>::Iterator occIt=token.getOccurrences().begin(); occIt!=token.getOccurrences().end(); occIt++){
                    Occurrence occ = *occIt;
                    lines += to_string(occ.line)+" ";
                    positions += to_string(occ.position)+" ";
                }
                out<<setw(15)<<lines<<positions<<endl;
            }
        }
        printLine('_',150);

        out<<"=> Number of words with stop words: "<<setw(60)<<sent.getAllWords()<<"=> Number of words without stop words: "<<sent.getNormalWords()<<endl;

        printLine('-',150);
    }

    HashTable<Expression> &expHash = *expIt;
    ++expIt;
    if(expHash.countObjects()>0){
        printExpressionTable(expHash);
    }


    printLine('_',150);
    out<<"=> Beginning paragraph in line: "<<p.getStartingLine()<<"  Number of sentences: "<<p.getTotalSentences()<<endl;
    printLine('_',150);
    out<<endl;
}
void Report::printFullResult(){
    HashTable<Token> &hash = analyzer.getTokens();
    int tableSize = hash.getTableSize();

    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<"POSITIONS\n";

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

    HashTable<Expression> &expHash = analyzer.getAllExpressions();
    if(expHash.countObjects()>0){
        printExpressionTable(expHash);
    }
}

void Report::printExpressionTable(HashTable<Expression> &hash){
    printLine('_',150);
    out<<left<<setw(40)<<"EXPRESSION"<<setw(15)<<"FREQUENCY"<<setw(20)<<"LINE"<<endl;
    
    printLine('-',150);

    for(int i=0; i<hash.getTableSize(); i++){
        LinkedList<Expression> &bucket = hash.getBucket(i);

        for(LinkedList<Expression>::Iterator itExp=bucket.begin(); itExp!=bucket.end(); itExp++){
            Expression &exp = *itExp;

            out<<left<<setw(40)<<exp.getText()<<setw(15)<<exp.getFrequency();

            bool first = true;
            for(LinkedList<int>::Iterator it=exp.getLines().begin(); it!=exp.getLines().end(); it++){
                if(!first)
                    out<<" ";
                out<<*it;
                first = false;
            }
            out<<endl;
        }
    }
    printLine('-',150);
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