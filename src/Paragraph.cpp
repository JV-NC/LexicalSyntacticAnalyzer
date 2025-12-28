#include "../include/Paragraph.hpp"

Paragraph::Paragraph(int n, int sL, int tS):
    number(n),
    startingLine(sL),
    totalSentences(tS) {}

int Paragraph::getNumber(){
    return number;
}
int Paragraph::getStartingLine(){
    return startingLine;
}
int Paragraph::getTotalSentences(){
    return totalSentences;
}