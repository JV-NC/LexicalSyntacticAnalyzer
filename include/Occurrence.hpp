#ifndef OCCURRENCE_HPP
#define OCCURRENCE_HPP

struct Occurrence{
    int paragraph;
    int sentence;
    int line;
    int position;

    Occurrence(int p, int s, int l, int pos): paragraph(p), sentence(s), line(l), position(pos) {}
};

#endif
