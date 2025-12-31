#include "../include/Report.hpp"
#include <iomanip>
//TODO: implement partial results, and paragraph/sentence stats
//TODO: implement stack for pontuation.
//TODO: refactor Queue for sentences in Analyzer
//TODO: expressions
//TODO: refactor printParagraphPartial for Paragraph parameter
//TODO: implement get(i) method for LinkedList
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
    Node<Paragraph> *p = analyzer.getParagraphs().getHead();
    int paragraphNumber = 1;
    
    while(p){
        printParagraphPartial(paragraphNumber);
        paragraphNumber++;
        p = p->next;
    }
}
void Report::printParagraphPartial(int paragraphNumber){
    // static Node<Sentence> *sentenceNode = analyzer.getSentences().getHead();
    // static Node<HashTable<Token>> *tokenNode = analyzer.getSentenceTokens().getHead();
    // static Node<HashTable<Expression>> *exprNode = analyzer.getParagraphExpressions().getHead();

    // //find current paragraph
    // Node<Paragraph> *p = analyzer.getParagraphs().getHead();
    // for(int i=1; i<paragraphNumber; i++)
    //     p = p->next;

    // int sentenceCount = p->data.getTotalSentences();

    // for(int i=0; i<sentenceCount; i++){
    //     printLine('_',150);

    //     out<<left
    //        <<setw(25)<<"WORD"
    //        <<setw(15)<<"PARAGRAPH"
    //        <<setw(15)<<"SENTENCE"
    //        <<setw(15)<<"LINE"
    //        <<setw(15)<<"APPEARANCES"
    //        <<setw(20)<<"POSITIONS\n";

    //     printLine('-',150);

    //     //print sentence tokens
    //     HashTable<Token> &hash = tokenNode->data;
    //     for(int j=0; j<hash.getTableSize(); j++){
    //         LinkedList<Token> &bucket = hash.getBucket(i);
    //         Node<Token> *node = bucket.getHead();

    //         while(node){
    //             Token &token = node->data;

    //             out<<left<<setw(20)<<token.getText()<<setw(12)<<token.getFrequency();

    //             Node<Occurrence> *occNode = token.getOccurrences().getHead();

    //             bool first = true;

    //             while(occNode){
    //                 Occurrence &occ = occNode->data;

    //                 if(!first){
    //                     out<<setw(20)<<" "<<setw(12)<<" ";

    //                 }

    //                 out<<setw(15)<<occ.paragraph<<setw(15)<<occ.sentence<<setw(15)<<occ.line<<setw(15)<<occ.position<<endl;

    //                 first = false;
    //                 occNode = occNode->next;
    //             }

    //             printLine('-',150);
    //             node = node->next;
    //         }
    //     }

    //     printLine('_',150);

    //     //Sentence stats
    //     out<<"=> Number of words with stop words: "
    //        <<sentenceNode->data.getAllWords()
    //        <<setw(60)
    //        <<" => Number of words without stop words: "
    //        <<sentenceNode->data.getNormalWords()
    //        <<'\n';

    //     printLine('-',150);

    //     sentenceNode = sentenceNode->next;
    //     tokenNode = tokenNode->next;
    // }

    // //paragraph stats
    // printLine('_',150);
    // out<<left<<setw(40)<<"EXPRESSION"
    //    <<setw(15)<<"FREQUENCY"
    //    <<setw(15)<<"LINE\n";
    // printLine('-',150);

    // HashTable<Expression> &exprHash = exprNode->data;
    // for(int i=0; i<exprHash.getTableSize(); i++){
    //     Node<Expression> *e = exprHash.getBucket(i).getHead();
    //     while(e){
    //         Expression &exp = e->data;
    //         out<<left<<setw(20)<<exp.getText()<<setw(12)<<exp.getFrequency()<<setw(12);
    //         Node<int> *line = exp.getLines().getHead();
    //         while(line){
    //             out<<line->data<<" ";
    //             line = line->next;
    //         }
    //         e = e->next;
    //     }
    // }

    // printLine('=',150);
    // out<<">> Beginning paragraph in line: "
    //    <<p->data.getStartingLine()
    //    <<"  Number of sentences: "
    //    <<p->data.getTotalSentences()
    //    <<'\n';
    // printLine('=',150);

    // exprNode = exprNode->next;
}
void Report::printFullResult(){
    HashTable<Token> &hash = analyzer.getTokens();
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