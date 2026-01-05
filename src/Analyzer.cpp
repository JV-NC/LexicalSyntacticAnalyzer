#include "../include/Analyzer.hpp"
#include "cctype"
#include <fstream>
//TODO: maybe change LinkedList of HashTables for a Queue of HashTable (check later)
Analyzer::Analyzer(const string &stopWordsFilename, const string &expressionsFilename){
    loadStopWords(stopWordsFilename);
    loadExpressions(expressionsFilename);
    loadAbbreviations();
}

void Analyzer::loadStopWords(const string &filename){
    ifstream file(filename.c_str());
    string word;

    while(file>>word){
        stopWords.insert(normalizeWord(word));
    }
}
void Analyzer::loadExpressions(const string &filename){
    ifstream file(filename.c_str());
    string line;

    while(getline(file, line)){
        if(!line.empty()){
            expressions.insert(normalizeWord(line));
        }
    }
}
void Analyzer::loadAbbreviations(){
    const int abSize=6;
    string ab[abSize] = {"sr", "sra", "dr", "dra", "prof", "etc"};

    for(int i=0; i<abSize;i++){
        abbreviations.insert(ab[i]);
    }
}
bool Analyzer::isSentenceEnd(char c){
    return c=='.' || c=='!' || c=='?';
}
bool Analyzer::isWordChar(unsigned char c){
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        c >= 128;
}
bool Analyzer::isStopWord(string &word){
    for(LinkedList<string>::Iterator it=stopWords.begin(); it!=stopWords.end(); it++){
        if(*it == word)
            return true;
    }
    return false;
}
void Analyzer::checkExpressions(const string &line, int lineNumber, HashTable<Expression> &currentExpressions){
    for(LinkedList<string>::Iterator it=expressions.begin(); it!=expressions.end(); it++){
        const string &exp = *it;

        size_t pos = line.find(exp);
        while(pos!=string::npos){
            currentExpressions.insert(exp,lineNumber);
            allExpressions.insert(exp,lineNumber);

            pos = line.find(exp,pos+exp.length());
        }
    }
}
char Analyzer::utf8ToAscii(unsigned char lead, unsigned char next){
    if(lead != 0xC3)
        return '\0';

    switch(next){
        //A
        case 0x80: case 0x81: case 0x82: case 0x83:
        case 0xA0: case 0xA1: case 0xA2: case 0xA3:
            return 'a';

        //E
        case 0x88: case 0x89:
        case 0xA9: case 0xAA:
            return 'e';

        //I
        case 0x8D:
        case 0xAD:
            return 'i';

        //O
        case 0x93: case 0x94: case 0x95:
        case 0xB3: case 0xB4: case 0xB5:
            return 'o';

        //U
        case 0x9A:
        case 0xBA:
            return 'u';

        //C
        case 0x87:
        case 0xA7:
            return 'c';

        default:
            return '\0';
    }
}
string Analyzer::normalizeWord(const string &word){
    string result;

    for(size_t i=0; i<word.size(); i++){
        unsigned char c = word[i];

        if(c=='-'){
            result+='-';
        }
        else if(c==0xC3 && i+1<word.size()){
            char ascii = utf8ToAscii(c,word[i+1]);
            if(ascii!='\0')
                result+=ascii;
            i++;
        }
        else if(isalpha(c)){
            result+=tolower(c);
        }
    }

    return result;
}

string Analyzer::normalizeLine(const string &line){
    string result;
    for(size_t i = 0; i < line.size(); i++){
        unsigned char c = line[i];

        if(c==' '){
            result +=' ';
        }
        else if(c=='-'){
            result+='-';
        }
        else if(c == 0xC3 && i + 1 < line.size()){
            char ascii = utf8ToAscii(c,line[i + 1]);
            if(ascii!='\0')
                result += ascii;
            i++;
        }
        else if(isalpha(c)){
            result += tolower(c);
        }
    }
    return result;
}

void Analyzer::finalizeSentenceIfPending(
    int &sentenceNumber,
    int paragraphNumber,
    int &stopWordsNum,
    int &nonStopWords,
    int &totalWordLength,
    int &position,
    HashTable<Token> &currentTokens
){
    if(position > 0){
        sentenceNumber++;

        double avg = (nonStopWords > 0)
            ? static_cast<double>(totalWordLength) / nonStopWords
            : 0.0;

        sentences.enqueue(
            Sentence(paragraphNumber, sentenceNumber, stopWordsNum, nonStopWords, avg)
        );

        sentenceTokens.insert(currentTokens);
        currentTokens.clear();

        stopWordsNum = nonStopWords = totalWordLength = position = 0;
    }
}

bool Analyzer::isDotInNumber(const string &line, size_t i){
    if(i==0 || i+1>=line.size())
        return false;
    return isdigit(line[i-1]) && isdigit(line[i+1]);
}

bool Analyzer::isAbbreviation(const string &word){
    for(LinkedList<string>::Iterator it=abbreviations.begin(); it!=abbreviations.end(); it++){
        if((*it)==word){
            return true;
        }
    }
    return false;
}

bool Analyzer::isOpening(char c){
    return c=='(' || c=='[' || c=='{' || c=='"' || c=='\'';
}
bool Analyzer::isClosing(char c){
    return c==')' || c==']' || c=='}' || c=='"' || c=='\'';
}
bool Analyzer::matches(char open, char close){
    return (open=='(' && close==')') || (open=='[' && close==']') || (open=='{' && close=='}') || (open=='"' && close=='"') || (open=='\'' && close=='\'');
}

void Analyzer::generateLengthDistribution(){
    lengthDist.clear();

    for(int i=0;i<tokens.getTableSize();i++){
        for(LinkedList<Token>::Iterator it=tokens.getBucket(i).begin(); it!=tokens.getBucket(i).end(); it++){
            int len = (*it).getText().length();
            int freq = (*it).getFrequency();
            lengthDist.increment(len, freq);
        }
    }

    //sort
    int n = 0;
    LinkedList<MapEntry> &list = lengthDist.getEntries();

    MapEntry *arr = list.toArray(n);
    if(!arr || n == 0) return;

    SortMetrics metrics;
    Sorter<MapEntry>::quickSort(arr, n, mapEntryKeyAsc, metrics);

    list.clear();
    for(int i=0;i<n;i++){
        list.insert(arr[i]);
    }

    delete[] arr;
}

void Analyzer::runSortingBenchmarks(){
    int size;
    Token *base = tokens.toArray(size);
    Token *arr;
    SortMetrics metrics;
    if(!base || size==0)
        return;

    int tests[] = {100, 500, 1000, 5000, 10000, size};

    for(int t=0;t<6;t++){
        int n = tests[t];

        if(n>size)
            continue;

        arr = cloneArray(base,n);
        Sorter<Token>::mergeSort(arr,n,tokenAlpha,metrics);
        benchmarkMetrics.insert(metrics);
        delete[] arr;
        metrics.clear();
        

        arr = cloneArray(base,n);
        Sorter<Token>::mergeSort(arr,n,tokenFreq,metrics);
        benchmarkMetrics.insert(metrics);
        delete[] arr;
        metrics.clear();

        arr = cloneArray(base,n);
        Sorter<Token>::quickSort(arr,n,tokenAlpha,metrics);
        benchmarkMetrics.insert(metrics);
        delete[] arr;
        metrics.clear();

        arr = cloneArray(base,n);
        Sorter<Token>::quickSort(arr,n,tokenFreq,metrics);
        benchmarkMetrics.insert(metrics);
        delete[] arr;
        metrics.clear();

        benchmarkTests.insert(n);
    }
}

void Analyzer::analyze(TextReader &reader){
    int paragraphNumber = 1, sentenceNumber = 0, startingLine = 1;
    int stopWordsNum = 0, nonStopWords = 0, totalWordLength = 0, position = 0;
    HashTable<Token> currentTokens;
    HashTable<Expression> currentExpressions;
    Stack<char> currentStack;
    string word, lastToken;

    while(reader.hasNextLine()){
        string line = reader.nextLine();

        string normalizedLine = normalizeLine(line);
        checkExpressions(normalizedLine, reader.getCurrentLine(), currentExpressions);

        if(line.empty()){
            finalizeSentenceIfPending(
                sentenceNumber,
                paragraphNumber,
                stopWordsNum,
                nonStopWords,
                totalWordLength,
                position,
                currentTokens
            );
            if(sentenceNumber>0){
                paragraphs.enqueue(
                    Paragraph(paragraphNumber, startingLine, sentenceNumber)
                );
                paragraphExpressions.insert(currentExpressions);
                punctuationBalance.enqueue(currentStack);
            }
            
            currentExpressions.clear();
            currentStack.clear();
            paragraphNumber++;
            sentenceNumber = 0;
            startingLine = reader.getCurrentLine()+1;
            continue;
        }

        for(size_t i=0; i<=line.size(); i++){
            unsigned char c = (i< line.size()) ? line[i]: ' ';

            if(isOpening(c)){
                char top;
                if((c=='"' || c=='\'') && currentStack.peek(top) && top==c){
                    char dummy;
                    currentStack.pop(dummy);
                }else{
                    currentStack.push(c);
                }
            }else if(isClosing(c)){
                char top;
                if(currentStack.peek(top) && matches(top, c)){
                    char dummy;
                    currentStack.pop(dummy);
                }else{
                    currentStack.push(c); //closing error
                }
            }

            if(isWordChar(c)){
                word+=c;
            }else if(c=='-' && !word.empty() && i+1<line.size() && isWordChar(line[i+1])){ //compound word
                word+=c;
            }else{
                if(!word.empty()){
                    word = normalizeWord(word);
                    if(!word.empty()){
                        position++;

                        if(!isStopWord(word)){
                            currentTokens.insert(
                                word,
                                paragraphNumber,
                                sentenceNumber+1,
                                reader.getCurrentLine(),
                                position
                            );
                            tokens.insert(
                                word,
                                paragraphNumber,
                                sentenceNumber+1,
                                reader.getCurrentLine(),
                                position
                            );
                            lastToken = word;

                            nonStopWords++;
                            totalWordLength += word.length();
                        }else{
                            stopWordsNum++;
                        }
                    }
                    word.clear();
                }

                if(isSentenceEnd(c)){
                    if(c=='.'){
                        //Elipsis check
                        if(i+1<line.size() && line[i+1]=='.'){
                            continue;
                        }
                        //Between numbers check
                        if(isDotInNumber(line,i)){
                            continue;
                        }
                        //Abbreviation check
                        if(isAbbreviation(lastToken)){
                            continue;
                        }
                    }
                    
                    if(nonStopWords == 0 && stopWordsNum == 0){
                        continue;
                    }

                    sentenceNumber++;

                    double avg = (nonStopWords>0)
                        ? static_cast<double>(totalWordLength)/nonStopWords
                        : 0.0;

                    sentences.enqueue(
                        Sentence(paragraphNumber, sentenceNumber, stopWordsNum, nonStopWords, avg)
                    );
                    
                    sentenceTokens.insert(currentTokens);
                    currentTokens.clear();
                    stopWordsNum=0;
                    nonStopWords=0;
                    totalWordLength=0;
                    position=0;
                }
            }
        }
    }

    finalizeSentenceIfPending(
        sentenceNumber,
        paragraphNumber,
        stopWordsNum,
        nonStopWords,
        totalWordLength,
        position,
        currentTokens
    );
    if(sentenceNumber>0){
        paragraphs.enqueue(
            Paragraph(paragraphNumber, startingLine, sentenceNumber)
        );
        paragraphExpressions.insert(currentExpressions);
        punctuationBalance.enqueue(currentStack);
    }

    generateLengthDistribution();
    runSortingBenchmarks();
}

Token* Analyzer::cloneArray(Token* src, int n){
    Token* dst = new Token[n];
    for(int i = 0; i < n; i++)
        dst[i] = src[i];
    return dst;
}

HashTable<Token>& Analyzer::getTokens(){
    return tokens;
}
LinkedList<HashTable<Token>>& Analyzer::getSentenceTokens(){
    return sentenceTokens;
}
HashTable<Expression>& Analyzer::getAllExpressions(){
    return allExpressions;
}
LinkedList<HashTable<Expression>>& Analyzer::getParagraphExpressions(){
    return paragraphExpressions;
}
Queue<Sentence>& Analyzer::getSentences(){
    return sentences;
}
Queue<Paragraph>& Analyzer::getParagraphs(){
    return paragraphs;
}
Queue<Stack<char>>& Analyzer::getPunctuationBalance(){
    return punctuationBalance;
}
LinkedList<MapEntry>& Analyzer::getLengthDist(){
    return lengthDist.getEntries();
}
LinkedList<SortMetrics>& Analyzer::getBenchmarkMetrics(){
    return benchmarkMetrics;
}
LinkedList<int>& Analyzer::getBenchmarkTests(){
    return benchmarkTests;
}