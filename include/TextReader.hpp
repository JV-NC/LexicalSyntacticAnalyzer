/**
 * @file TextReader.hpp
 * @brief Defines TextReader class
 */

#ifndef TEXTREADER_HPP
#define TEXTREADER_HPP

#include <fstream>
#include <string>

using namespace std;

/**
 * @class TextReader
 * @brief Utility class for sequential line-based text reading.
 *
 * Wraps an input file stream and tracks the current line number.
 */
class TextReader{
private:
    ifstream file; ///< Input file stream
    int currentLine; ///< Current line number

public:
    /**
     * @brief Opens a text file.
     * @param filename Path to the input file.
     */
    TextReader(const string &filename);
    /** @brief Closes the file. */
    ~TextReader();

    /** @return True if file is open. */
    bool isOpen();
    /** @return True if there is another line to read. */
    bool hasNextLine();
    /**
     * @brief Reads the next line from the file.
     * @return Line content.
     */
    string nextLine();
    /** @return Current line number. */
    int getCurrentLine();
};

#endif