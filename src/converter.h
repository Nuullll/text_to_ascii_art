#ifndef TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
#define TEXT_TO_ASCII_ART_SRC_CONVERTER_H_

#include <map>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "font.h"

namespace text_to_ascii_art {

class Converter
{
 public:
    Converter();

    // Load a certain font.
    // If the filename is not given, it will try to load the font file
    // in a default path.
    // If a font with a same name already exists, the old typename will
    // be removed and the new one will be loaded.
    bool LoadFont(const std::string &font_name,
                      const char *filename = nullptr);

    // Convert the given text into ASCII art.
    std::string Convert(const std::string &text);
    // Convert the text, and print it into the os.
    void Print(const std::string &text, std::ostream &os);

    // Return the vector of loaded fonts.
    // The pair contains the name of the font and the character number
    // in that font.
    std::vector<std::pair<std::string, int>> LoadedFonts() const;

 private:
    std::map<std::string, Font> fonts_;
};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
