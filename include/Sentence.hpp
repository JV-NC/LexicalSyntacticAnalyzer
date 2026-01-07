/**
 * @file Sentence.hpp
 * @brief Defines Sentence class.
 */

#ifndef SENTENCE_HPP
#define SENTENCE_HPP

/**
 * @class Sentence
 * @brief Represents statistical information about a sentence.
 *
 * Stores sentence position, word counts, and average word length, excluding or including stop words.
 * 
 * @see Queue
 */
class Sentence{
private:
    int paragraphNumber; ///< Paragraph index
    int sentenceNumber; ///< Sentence index
    int stopWords; ///< Number of stop words
    int nonStopWords; ///< Number of stop words
    double averageWordLength; ///< Average word length
public:
    /** @brief Default constructor. */
    Sentence();
    /**
     * @brief Constructs a sentence with full statistics.
     * @param pN Paragraph number.
     * @param sN Sentence number.
     * @param sWords Stop word count.
     * @param nWords Non-stop word count.
     * @param avrWordLength Average word length.
     */
    Sentence(int pN, int sN, int sWords, int nWords, double avrWordLength);
    
    /** @return Paragraph number. */
    int getParagraphNumber();
    /** @return Sentence number. */
    int getSentenceNumber();
    /** @return Total words (including stop words). */
    int getAllWords();
    /** @return Number of non-stop words. */
    int getNormalWords();
    /** @return Average word length. */
    double getAverageWordLength();
};
#endif