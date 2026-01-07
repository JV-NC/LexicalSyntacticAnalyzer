/**
 * @file Occurrence.hpp
 * @brief Defines Occurence struct.
 */

#ifndef OCCURRENCE_HPP
#define OCCURRENCE_HPP


/**
 * @struct Occurence
 * @brief Represents a single occurrence of a token in the text.
 *
 * Stores the paragraph, sentence, line and position where
 * a word or expression appears.
 *
 * @see Token
 */
struct Occurrence{
    int paragraph; /**< Paragraph number */
    int sentence; /**< Sentence number */
    int line; /**< Line number */
    int position; /**< Position in sentence */

    /**
     * @brief Constructs an occurrence record.
     *
     * @param p Paragraph number.
     * @param s Sentence number.
     * @param l Line number.
     * @param pos Position in sentence.
     */
    Occurrence(int p, int s, int l, int pos): paragraph(p), sentence(s), line(l), position(pos) {}
};

#endif
