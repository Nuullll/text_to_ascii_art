#ifndef TEXT_TO_ASCII_ART_SRC_CHARACTER_H_
#define TEXT_TO_ASCII_ART_SRC_CHARACTER_H_

#include <string>
#include <vector>

class Character
{
 public:
    Character(const std::string &);
    ~Character();

    int width() const { return width_; }
    int height() const { return height_; }

 private:
    int width_;
    int height_;
    std::vector<std::string> char_map_;
};

#endif  // TEXT_TO_ASCII_ART_SRC_CHARACTER_H_
