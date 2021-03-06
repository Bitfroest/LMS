#ifndef LMS_EXTRA_STRING_H
#define LMS_EXTRA_STRING_H

#include <string>
#include <vector>

namespace lms {
namespace extra {

/**
 * Remove surrounding whitespace from a std::string.
 * @param s The string to be modified.
 * @param t The set of characters to delete from each end
 * of the string.
 * @return trimmed string
 */
std::string trim(const std::string& str, const std::string &delims = " \t\n\r\f\v");

/**
 * TODO write test cases
 * @brief split
 * @param string
 * @param strLength
 * @param splitter
 * @return
 */
std::vector<std::string> split(const char *string, int strLength, char splitter);

std::vector<std::string> split(const std::string &string, char splitter);

/**
 * @brief Returns the directory of a path without trailing slash.
 *
 * /tmp/test.file -> /tmp
 * /tmp/test.file/ -> /tmp
 * tmp/test.file -> tmp
 * / -> /
 *
 * @param path a filesystem path
 * @return filesystem path without basename
 */
std::string dirname(std::string path);

/**
 * @brief Check if a pathname is absolute, meaning it starts with a slash and
 * is not empty.
 * @param path path to check
 * @return true if absolute, false otherwise
 */
bool isAbsolute(const std::string &path);

/**
 * @brief Platform safe implementation for std::getline. \r and \n are handled
 * correctly.
 * @param is input stream
 * @param str line
 * @return the same input stream as given
 */
std::istream& safeGetline(std::istream& is, std::string& str);

} // namespace extra
} // namespace lms

#endif /* LMS_EXTRA_STRING_H */
