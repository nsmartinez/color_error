#ifndef __STRING_MAPPER_H__
#define __STRING_MAPPER_H__

#include <string>
#include <unordered_map>

namespace werpp {

class StringMapper {
    std::unordered_map<std::string, unsigned int> word_to_uint_;
    std::unordered_map<unsigned int, std::string> uint_to_word_;
    unsigned int n_elems_;

public:
    StringMapper();
    const unsigned int& operator()(const std::string &word);
    const std::string& operator()(const unsigned int &word_id) const;
};

} // namespace werpp
#endif
