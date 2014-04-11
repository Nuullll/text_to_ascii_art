#ifndef TEXT_TO_ASCII_ART_SRC_TYPEFACE_H_
#define TEXT_TO_ASCII_ART_SRC_TYPEFACE_H_

#include <map>
#include <string>

#include "character.h"

namespace text_to_ascii_art {

class Typeface
{
 public:
    Typeface();
    explicit Typeface(const char *filename);
    ~Typeface();

 private:
    bool loaded_;
    std::string typeface_name_;
    int font_size_;
    std::map<char, Character> characters;
};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_TYPEFACE_H_
