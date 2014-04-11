#ifndef TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
#define TEXT_TO_ASCII_ART_SRC_CONVERTER_H_

#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "typeface.h"

namespace text_to_ascii_art {

class Converter
{
 public:
    Converter();

    // Load a certain typeface.
    // If the filename is not given, it will try to load the typeface file
    // in a default path.
    // If a typeface with a same name already exists, the old typename will
    // be removed and the new one will be loaded.
    bool LoadTypeface(const std::string &typeface_name,
                      const char *filename = nullptr);

    // Convert the given text into ASCII art.
    std::string Convert(std::string text);
    // Convert the text, and print it into the os.
    void Print(std::string text, std::ostream &os);

    // Return the vector of loaded typefaces.
    // The pair contains the name of the typeface and the character number
    // in that typeface.
    std::vector<std::pair<std::string, int>> LoadedTypeface() const;

 private:
    std::map<std::string, Typeface> typefaces_;
};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
