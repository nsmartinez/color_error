#include <color_error/string_mapper.h>

namespace werpp {

StringMapper::StringMapper():n_elems_(0){}

const unsigned int& StringMapper::operator()(const std::string &word){
    if(word_to_uint_.find(word) == end(word_to_uint_)){
        word_to_uint_[word] = ++n_elems_;
        uint_to_word_[n_elems_] = word;
    }

    return word_to_uint_[word];
}

const std::string& StringMapper::operator()(const unsigned int &word_id) const {
    return uint_to_word_.at(word_id);
}

} // namespace werpp
