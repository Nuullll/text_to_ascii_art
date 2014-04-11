#ifndef TEXT_TO_ASCII_ART_SRC_FONT_H_
#define TEXT_TO_ASCII_ART_SRC_FONT_H_

#include <map>
#include <string>

#include "character.h"

namespace text_to_ascii_art {

// Maintain a font from a certain file.
// The font can been seen as a wrapper of the file
class Font
{
 public:
    Font();
    explicit Font(const char *filename);

    // Return the number of characters loaded.
    // If is_loaded_ is already true, nothing will be read, and 0 will be
    // returned.
    int Load(const char *filename);

    // Get a certain character.
    // If the character do not exist in the font, nullptr will be returned.
    const Character * GetCharacter(char ch) const;

    bool is_loaded() const { return is_loaded_; }
    int max_height() const { return max_height_; }

 private:
    bool is_loaded_;
    int max_height_;
    std::map<char, Character> characters;
};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_FONT_H_
