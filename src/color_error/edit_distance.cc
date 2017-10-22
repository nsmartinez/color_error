#include <algorithm>
#include <limits>
#include <iostream>
#include <deque>

#include <color_error/edit_distance.h>

namespace werpp {

EditDistance::EditDistance(std::vector<AbstractEditOperation*> edit_ops):
    edit_ops_(edit_ops){}


EditDistanceResult& EditDistance::operator()(
        const std::string& id,
        const std::vector<std::string>& from_s,
        const std::vector<std::string>& to_s){

    uint_vec from, to;
    for(auto w : from_s)
        from.emplace_back(string_map_(w));
    for(auto w : to_s)
        to.emplace_back(string_map_(w));

    edit_node_mat_t edits(from.size() + 1, edit_node_vec_t(to.size() + 1));

    initialise(edits, from.size()+1, to.size()+1);

    // compute the edit distance
    for(auto i = 1u;i < from.size()+1; ++i)
        for(auto j = 1u;j < to.size()+1; ++j){
            // loop over operations, only keeping the minimum one
            edits[i][j] = std::accumulate(
                    begin(edit_ops_), end(edit_ops_),
                    EditNode(NONE, 0, 0, std::numeric_limits<unsigned int>::max()),
                    [&] 
                    (EditNode& x, AbstractEditOperation* y) { 
                        return x + y->edit_op(edits, from, to, i, j); }
            );
        }

    
    results_.emplace(id, EditDistanceResult(id, from, to, edits, string_map_));
    for(auto& sample_stats : results_.at(id).stats())
        stats_[sample_stats.first] += sample_stats.second;

    return results_.at(id);
}


const float EditDistance::error_rate() const{
    auto cost = 0u, n_ref_words = 0u;
    for(auto i : results_) {
        cost += i.second.cost();
        n_ref_words += i.second.n_ref_words();
    }
    return static_cast<float>(cost)/n_ref_words*100;
}


void WEREditDistance::initialise(edit_node_mat_t& edits,
                                 const unsigned int f_size,
                                 const unsigned int t_size){

    // Initialise the cost in the margins of the cost matrix
    for(auto ij = 1u;ij < f_size; ++ij){
        edits[ij][0].id = INSERTION;
        edits[ij][0].from_i = ij-1;
        edits[ij][0].cost = ij;
    }
    for(auto ij = 1u;ij < t_size; ++ij){
        edits[0][ij].id = DELETION;
        edits[0][ij].from_j = ij-1;
        edits[0][ij].cost = ij;
    }
   
} 

} // namespace werpp
