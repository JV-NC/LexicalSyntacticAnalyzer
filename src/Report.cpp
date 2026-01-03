#include "../include/Report.hpp"
#include <iomanip>
//TODO: implement paragraph/sentence stats
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
    Queue<Stack<char>> punctuationBalance = analyzer.getPunctuationBalance();
    Stack<char> punctStack;
    Paragraph p;
    
    while(!pq.isEmpty()){
        pq.dequeue(p);
        punctuationBalance.dequeue(punctStack);
        printParagraphPartial(p, sq, tokensIt, expIt, punctStack);
    }
}
void Report::printParagraphPartial(Paragraph p, Queue<Sentence> &sq, LinkedList<HashTable<Token>>::Iterator &tokenIt, LinkedList<HashTable<Expression>>::Iterator &expIt, Stack<char> ps){
    for(int s=0; s<p.getTotalSentences(); s++){
        Sentence sent;
        sq.dequeue(sent);

        HashTable<Token> &hash = *tokenIt;
        ++tokenIt;

        printLine('_',150);

        out<<left<<setw(25)<<"WORD"<<setw(15)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<"POSITIONS\n";

        printLine('-',150);

        printSortedTokenTable(hash,sent.getParagraphNumber(),sent.getSentenceNumber());
        printLine('_',150);

        out<<"=> Number of words with stop words: "<<setw(60)<<sent.getAllWords()<<"=> Number of words without stop words: "<<sent.getNormalWords()<<endl;

        printLine('-',150);
    }

    HashTable<Expression> &expHash = *expIt;
    ++expIt;
    if(expHash.countObjects()>0){
        printSortedExpressionTable(expHash);
    }

    //punctuation balance
    if(!ps.isEmpty()){
        printLine('_',150);
        out<<"=> Unbalanced symbols\n"<<"=> Unmatched symbols: ";
        char c;
        while(!ps.isEmpty()){
            ps.pop(c);
            out<<c<<" ";
        }
        out<<endl;
        printLine('-',150);
    }

    printLine('_',150);
    out<<"=> Beginning paragraph in line: "<<p.getStartingLine()<<"  Number of sentences: "<<p.getTotalSentences()<<endl;
    printLine('_',150);
    out<<endl;
}
void Report::printFullResult(){
    HashTable<Token> &hash = analyzer.getTokens();

    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"
       <<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"
       <<setw(15)<<"LINE"<<"POSITIONS\n";

    printLine('-',150);

    int size = 0;
    Token *arr = hash.toArray(size);

    if(!arr || size == 0)
        return;

    SortMetrics metrics;
    Sorter<Token>::quickSort(arr, size, tokenAlpha, metrics);

    for(int i = 0; i < size; i++){
        Token &token = arr[i];

        out<<left<<setw(20)<<token.getText()
           <<setw(12)<<token.getFrequency();

        bool first = true;
        for(auto it = token.getOccurrences().begin();
            it != token.getOccurrences().end(); it++){

            if(!first)
                out<<setw(20)<<" "<<setw(12)<<" ";

            out<<setw(15)<<(*it).paragraph
               <<setw(15)<<(*it).sentence
               <<setw(15)<<(*it).line
               <<setw(15)<<(*it).position
               <<endl;

            first = false;
        }

        printLine('-',150);
    }

    printLine('_',150);
    out<<"Metrics:\n"<<"Comparisons: "<<setw(20)<<metrics.comparisons<<"Swaps: "<<setw(20)<<metrics.swaps<<"Elapsed time: "<<setw(20)<<metrics.elapsedTime<<endl;
    printLine('-',150);

    delete[] arr;

    HashTable<Expression> &expHash = analyzer.getAllExpressions();
    if(expHash.countObjects()>0){
        printSortedExpressionTable(expHash);
    }
}
void Report::printSortedTokenTable(HashTable<Token> &hash, int paragraph, int sentence){
    int size = 0;
    Token *arr = hash.toArray(size);

    if(!arr || size==0)
        return;
    
    SortMetrics metrics;
    Sorter<Token>::quickSort(arr, size, tokenAlpha, metrics);

    for(int i=0;i<size;i++){
        Token &token = arr[i];

        out<<left<<setw(25)<<token.getText()
           <<setw(15)<<token.getFrequency()
           <<setw(15)<<paragraph
           <<setw(15)<<sentence;
        
        string lines, positions;

        for(LinkedList<Occurrence>::Iterator it=token.getOccurrences().begin(); it!=token.getOccurrences().end(); it++){
            lines += to_string((*it).line) + " ";
            positions += to_string((*it).position) + " ";
        }

        out<<setw(15)<<lines<<positions<<endl;
    }

    printLine('_',150);
    out<<"Metrics:\n"<<"Comparisons: "<<setw(20)<<metrics.comparisons<<"Swaps: "<<setw(20)<<metrics.swaps<<"Elapsed time: "<<setw(20)<<metrics.elapsedTime<<endl;
    printLine('-',150);

    delete[] arr;
}
void Report::printSortedExpressionTable(HashTable<Expression> &hash){
    int size = 0;
    Expression* arr = hash.toArray(size);

    if(!arr || size==0)
        return;
    
    SortMetrics metrics;
    Sorter<Expression>::quickSort(arr,size,expressionAlpha,metrics);
    
    printLine('_',150);
    out<<left<<setw(40)<<"EXPRESSION"<<setw(15)<<"FREQUENCY"<<setw(20)<<"LINE"<<endl;
    
    printLine('-',150);


    for(int i=0; i<size; i++){
        Expression &exp = arr[i];

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