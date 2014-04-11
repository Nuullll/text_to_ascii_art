#ifndef TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
#define TEXT_TO_ASCII_ART_SRC_CONVERTER_H_

#include <string>
#include <ostream>

namespace text_to_ascii_art {

class Converter
{
 public:
    Converter();
    ~Converter();

    bool LoadTypeface(const char *filename);
    std::string Convert(std::string text);
    void Print(std::string text, std::ostream &os);

 private:

};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_CONVERTER_H_
