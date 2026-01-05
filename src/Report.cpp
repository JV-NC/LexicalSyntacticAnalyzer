#include "../include/Report.hpp"
#include <iomanip>

Report::Report(Analyzer &a, ostream &output): analyzer(a), out(output) {}

void Report::printLine(char c, int n){
    for(int i=0; i<n; i++)
        out<<c;
    out<<endl;
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
    HashTable<Token> paragraphTokens;
    for(int s=0; s<p.getTotalSentences(); s++){
        Sentence sent;
        sq.dequeue(sent);

        HashTable<Token> &hash = *tokenIt;
        ++tokenIt;

        //get tokens for paragraph
        int size = 0;
        Token *arr = hash.toArray(size);

        if(arr && size > 0){
            for(int i=0; i<size;i++){
                Token &t = arr[i];
                for(LinkedList<Occurrence>::Iterator occ = t.getOccurrences().begin(); occ!=t.getOccurrences().end(); occ++){
                    paragraphTokens.insert(
                        t.getText(),
                        (*occ).paragraph,
                        (*occ).sentence,
                        (*occ).line,
                        (*occ).position
                    );
                }
            }
        }

        delete[] arr;

        printLine('_',150);

        out<<left<<setw(25)<<"WORD"<<setw(15)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<"POSITIONS\n";

        printLine('-',150);

        printSortedTokenTable(hash,sent.getParagraphNumber(),sent.getSentenceNumber());
        printLine('_',150);

        out<<"=> Number of words with stop words: "<<setw(60)<<sent.getAllWords()<<"=> Number of words without stop words: "<<sent.getNormalWords()<<endl;

        printLine('-',150);
    }

    //words used 3 or more times in the paragraph
    printFrequentlyUsedWords(paragraphTokens);

    //paragraph expressions
    HashTable<Expression> &expHash = *expIt;
    ++expIt;
    if(expHash.countObjects()>0){
        printSortedExpressionTable(expHash);
    }

    //punctuation balance
    printLine('_',150);
    if(ps.isEmpty()){
        out<<"=> Balanced symbols: YES\n";
    }else{
        out<<"=> Balanced symbols: NO\n"<<"=> Unmatched symbols: ";
        char c;
        while(!ps.isEmpty()){
            ps.pop(c);
            out<<c<<" ";
        }
        out<<endl;
    }
    printLine('-',150);

    printLine('_',150);
    out<<"=> Beginning paragraph in line: "<<p.getStartingLine()<<"  Number of sentences: "<<p.getTotalSentences()<<endl;
    printLine('_',150);
    out<<endl;
}
void Report::printFullResult(){
    HashTable<Token> &hash = analyzer.getTokens();

    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<setw(15)<<"PARAGRAPH"<<setw(15)<<"SENTENCE"<<setw(15)<<"LINE"<<"POSITIONS\n";

    printLine('-',150);

    int size = 0;
    Token *arr = hash.toArray(size);

    if(!arr || size == 0)
        return;

    SortMetrics metrics;
    Sorter<Token>::quickSort(arr, size, tokenAlpha, metrics);

    for(int i = 0; i < size; i++){
        Token &token = arr[i];

        out<<left<<setw(20)<<token.getText()<<setw(12)<<token.getFrequency();

        bool first = true;
        for(LinkedList<Occurrence>::Iterator it = token.getOccurrences().begin(); it!=token.getOccurrences().end(); it++){

            if(!first)
                out<<setw(20)<<" "<<setw(12)<<" ";

            out<<setw(15)<<(*it).paragraph<<setw(15)<<(*it).sentence<<setw(15)<<(*it).line<<setw(15)<<(*it).position<<endl;

            first = false;
        }

        printLine('-',150);
    }

    delete[] arr;

    //distinct vocabulary size
    int distinctVocabulary = hash.countObjects();
    printLine('_',150);
    out << "DISTINCT VOCABULARY SIZE: " << distinctVocabulary << " WORDS\n";
    printLine('-',150);

    // 10 of most and least frequent words
    printMostLeastFrequentWords(hash, 10);

    printSentenceStats();
    printParagraphStats();

    HashTable<Expression> &expHash = analyzer.getAllExpressions();
    if(expHash.countObjects()>0){
        printSortedExpressionTable(expHash);
    }

    printFullResultSortMetrics(hash);
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

        out<<left<<setw(25)<<token.getText()<<setw(15)<<token.getFrequency()<<setw(15)<<paragraph<<setw(15)<<sentence;
        
        string lines, positions;

        for(LinkedList<Occurrence>::Iterator it=token.getOccurrences().begin(); it!=token.getOccurrences().end(); it++){
            lines += to_string((*it).line) + " ";
            positions += to_string((*it).position) + " ";
        }

        out<<setw(15)<<lines<<positions<<endl;
    }

    delete[] arr;
}
void Report::printFrequentlyUsedWords(HashTable<Token> &hash){
    int size = 0;
    Token *arr = hash.toArray(size);

    if(!arr || size==0)
        return;
    
    SortMetrics metrics;
    Sorter<Token>::quickSort(arr, size, tokenFreq, metrics);

    if(arr[0].getFrequency()<3){
        return;
    }

    printLine('_',150);
    out<<left<<setw(30)<<"WORDS USED 3 OR MORE TIMES"<<"FREQUENCY"<<endl;
    printLine('-',150);
    for(int i=0;i<size;i++){
        if(arr[i].getFrequency()<3){
            break;
        }
        out<<left<<setw(30)<<arr[i].getText()<<arr[i].getFrequency()<<endl;
    }
    printLine('_',150);
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
void Report::printFullResultSortMetrics(HashTable<Token> &hash){
    int size = 0;
    Token *base = hash.toArray(size);

    if(!base || size==0)
        return;

    SortMetrics metrics[4];
    Token *arr;
    string alg[2] = {"MergeSort","QuickSort"};
    string order[2] = {"Alphabetical","Frequency"};

    //MergeSortAlpha
    arr = analyzer.cloneArray(base, size);
    Sorter<Token>::mergeSort(arr, size, tokenAlpha, metrics[0]);
    delete[] arr;

    //MergeSortFreq
    arr = analyzer.cloneArray(base, size);
    Sorter<Token>::mergeSort(arr, size, tokenFreq, metrics[1]);
    delete[] arr;

    //QuickSortAlpha
    arr = analyzer.cloneArray(base, size);
    Sorter<Token>::quickSort(arr, size, tokenAlpha, metrics[2]);
    delete[] arr;

    //QuickSortFreq
    arr = analyzer.cloneArray(base, size);
    Sorter<Token>::quickSort(arr, size, tokenFreq, metrics[3]);
    delete[] arr;

    delete[] base;

    printLine('=',150);
    out<<"SORT PERFORMANCE METRICS\n";
    printLine('-',150);

    out<<left<<setw(25)<<"Algorithm"<<setw(20)<<"Order"<<setw(20)<<"Comparisons"<<setw(20)<<"Swaps"<<setw(25)<<"Elapsed Time (s)"<<endl;

    printLine('-',150);

    for(int i=0; i<2; i++){
        for(int j=0; j<2;j++){
            out<<left<<setw(25)<<alg[i%2]<<setw(20)<<order[j%2]<<setw(20)<<metrics[i*2+j].comparisons<<setw(20)<<metrics[i*2+j].swaps<<setw(20)<<fixed<<setprecision(6)<<metrics[i*2+j].elapsedTime<<endl;
        }
    }

    printLine('=',150);
    out<<endl;
}
void Report::printMostLeastFrequentWords(HashTable<Token> &hash, int X){
    int size = 0;
    Token *arr = hash.toArray(size);
    SortMetrics metrics;

    if(!arr || size == 0)
        return;
    
    Sorter<Token>::quickSort(arr, size, tokenFreq, metrics);

    printLine('_',150);
    out<<"TOP "<<X<<" MOST FREQUENT WORDS\n";
    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<endl;
    printLine('-',150);
    for(int i=0; i<X && i<size; i++){
        out<<left<<setw(20)<<arr[i].getText()<<arr[i].getFrequency()<<endl;
    }
    printLine('_',150);

    printLine('_',150);
    out<<"TOP "<<X<<" LEAST FREQUENT WORDS\n";
    out<<left<<setw(20)<<"WORD"<<setw(12)<<"FREQUENCY"<<endl;
    printLine('-',150);
    for(int i=size-X; i<size; i++){
        if(i>=0)
            out<<left<<setw(20)<<arr[i].getText()<<arr[i].getFrequency()<<endl;
    }
    printLine('_',150);
}
void Report::printLengthDist(){
    printLine('_',50);
    out<<left<<"WORD LENGTH DISTRIBUTION\n"<<setw(15)<<"Length"<<"Frequency"<<endl;
    printLine('-',50);
    LinkedList<MapEntry> lengthDist = analyzer.getLengthDist();
    for(LinkedList<MapEntry>::Iterator it=lengthDist.begin(); it!=lengthDist.end(); it++){
        out<<left<<setw(15)<<(*it).key<<(*it).value<<endl;
    }

}
void Report::printSentenceStats(){
    Queue<Sentence> sq = analyzer.getSentences();
    int totalWords = 0, totalSentences = 0;

    if(sq.isEmpty()){
        out<<"Error in printSentenceStats;\n";
        return;
    }
    
    printLine('_',150);
    out<<setw(110)<<"NUMBER OF WORDS IN EACH SENTENCE WITH AND WITHOUT STOP WORDS"<<endl;
    printLine('-',150);

    Sentence s;
    while(!sq.isEmpty()){
        sq.dequeue(s);
        totalWords+=s.getNormalWords();
        totalSentences++;

        out<<"Paragraph: "<<setw(7)<<s.getParagraphNumber()<<"\tSentence: "<<setw(7)<<s.getSentenceNumber()<<"\tNumber of words with stop words: "<<setw(4)<<s.getAllWords()<<"\tNumber of words without stop words: "<<setw(4)<<s.getNormalWords()
        <<"Average word length: "<<setw(7)<<fixed<<setprecision(2)<<s.getAverageWordLength()<<endl;
        printLine('_',150);
        out<<endl;
    }

    double avgSentenceSize = totalSentences ? (double)totalWords / totalSentences : 0.0;

    printLine('_',150);
    out<<"AVERAGE SENTENCE LENGTH: "<<fixed<<setprecision(2)<<avgSentenceSize<<"WORDS\n";
    printLine('-',150);
}
void Report::printParagraphStats(){
    Queue<Paragraph> pq = analyzer.getParagraphs();

    if(pq.isEmpty()){
        out<<"Error in printParagraphStats;\n";
        return;
    }

    printLine('_',150);
    out<<setw(90)<<"LINE NUMBER THAT START EACH PARAGRAPH"<<endl;
    printLine('-',150);

    Paragraph p;
    while(!pq.isEmpty()){
        pq.dequeue(p);

        out<<"Paragraph: "<<setw(7)<<p.getNumber()<<"\tBeginning in line: "<<setw(7)<<p.getStartingLine()<<"\t Number of sentences: "<<p.getTotalSentences()<<endl;
    }

    printLine('_',150);
    out<<endl;
}

void Report::exportSortMetricsCSV(){
    ofstream file("output/sort_metrics.csv");

    file<<"algorithm,order,n,comparisons,swaps,time_s\n";

    LinkedList<SortMetrics> metrics = analyzer.getBenchmarkMetrics();
    LinkedList<int> tests = analyzer.getBenchmarkTests();

    LinkedList<SortMetrics>::Iterator m = metrics.begin();
    for(LinkedList<int>::Iterator t=tests.begin(); t!=tests.end(); t++){
        for(int i=0;i<4;i++){
            string alg = (i<2) ? "MergeSort" : "QuickSort";
            string order = (i%2==0) ? "Alphabetical" : "Frequency";
            file<<alg<<","<<order<<","<<(*t)<<","<<(*m).comparisons<<","<<(*m).swaps<<","<<(*m).elapsedTime<<endl;
            ++m;
        }
    }
    file.close();
}

void Report::exportLengthDist(){
    ofstream file("output/length_dist.csv");

    file<<"length,frequency\n";

    LinkedList<MapEntry> lengthDist = analyzer.getLengthDist();
    for(LinkedList<MapEntry>::Iterator it=lengthDist.begin(); it!=lengthDist.end(); it++){
        file<<(*it).key<<","<<(*it).value<<endl;
    }

    file.close();
}

void Report::generate(){
    printTitle("### START PROCESS ###");

    printTitle("### PARTIAL RESULT ###");
    printPartialResult();

    printTitle("### FULL RESULT ###");
    printFullResult();

    printLengthDist();

    printTitle("### END PROCESS ###");

    exportSortMetricsCSV();
    exportLengthDist();
}