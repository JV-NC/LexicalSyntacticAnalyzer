/**
 * @file Paragraph.hpp
 * @brief Defines Paragraph class.
 */

#ifndef PARAGRAPH_HPP
#define PARAGRAPH_HPP

/**
 * @class Paragraph
 * @brief Represents a paragraph extracted from the input text.
 *
 * A paragraph stores structural information such as its sequential number, the line where it starts, and how many sentences it contains.
 * 
 * @see Queue
 */
class Paragraph{
private:
    int number; ///< Paragraph index in the text
    int startingLine; ///< Line number where the paragraph starts
    int totalSentences; ///< Number of sentences in the paragraph
public:
    /** @brief Default constructor. */
    Paragraph();
    /**
     * @brief Constructs a paragraph with metadata.
     * @param n Paragraph number.
     * @param sL Starting line number.
     * @param tS Total number of sentences.
     */
    Paragraph(int n, int sL, int tS);
    
    /** @return Paragraph number. */
    int getNumber();
    /** @return Starting line number. */
    int getStartingLine();
    /** @return Total number of sentences. */
    int getTotalSentences();
};
#endif