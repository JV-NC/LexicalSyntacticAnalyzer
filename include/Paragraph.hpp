#ifndef PARAGRAPH_HPP
#define PARAGRAPH_HPP

class Paragraph{
private:
    int number;
    int startingLine;
    int totalSentences;
public:
    Paragraph(int n, int sL, int tS);
    
    int getNumber();
    int getStartingLine();
    int getTotalSentences();
};
#endif