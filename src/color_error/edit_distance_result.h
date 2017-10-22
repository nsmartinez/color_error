#ifndef __EDIT_DISTANCE_RESULT_H__
#define __EDIT_DISTANCE_RESULT_H__

#include <vector>
#include <string>
#include <map>
#include <deque>
#include <unordered_map>

#include <color_error/edit_names.h>
#include <color_error/edit_operation.h>
#include <color_error/string_mapper.h>


namespace werpp {

struct ResultNode {
    const EditOperationId operation;
    const std::string from_w, to_w;

    ResultNode(const EditOperationId & operation,
               const std::string& from_w,
               const std::string& to_w):
        operation(operation), from_w(from_w), to_w(to_w){}
};

class EditDistanceResult {
    const std::string id_;
    std::deque<ResultNode> path_;
    std::unordered_map<std::string, unsigned int> stats_;
    const unsigned int cost_;
    const unsigned int n_ref_words_;
public:
    EditDistanceResult(const std::string& id,
                       const uint_vec& from,
                       const uint_vec& to,
                       const edit_node_mat_t& edits,
                       const StringMapper& mapper);

    inline const std::string& id() const { return id_; }
    inline const std::unordered_map<std::string, unsigned int>& 
        stats() const { return stats_; }
    inline const std::deque<ResultNode>& 
        path() const { return path_; }
    inline const unsigned int cost() const { return cost_; }
    inline const unsigned int n_ref_words() const { return n_ref_words_; }
    inline const float error_rate() const { return static_cast<float>(cost_)/n_ref_words_*100; }
};


} // namespace werpp
#endif
