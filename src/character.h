#ifndef TEXT_TO_ASCII_ART_SRC_CHARACTER_H_
#define TEXT_TO_ASCII_ART_SRC_CHARACTER_H_

#include <string>
#include <vector>

namespace text_to_ascii_art {

// Contain the map of a character.
// It ensures that the map is a rectangle.
class Character
{
 public:
    // Constructed by a single string (with a '\n' at the last of each line).
    // Save every line into a separate string (without the last '\n').
    // If the width of the lines do not match, blank in end of the shorter
    // lines will be filled with space.
    explicit Character(const std::string &);

    const std::vector<std::string> & character_map() const;

    int width() const { return width_; }
    int height() const { return character_map_.size(); }

 private:
    int width_;
    std::vector<std::string> character_map_;
};

}  // namespace text_to_ascii_art

#endif  // TEXT_TO_ASCII_ART_SRC_CHARACTER_H_
