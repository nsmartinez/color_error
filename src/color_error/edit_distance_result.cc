#include <iostream>

#include <color_error/edit_distance_result.h>

namespace werpp {


EditDistanceResult::EditDistanceResult(const std::string& id,
                                       const uint_vec& from,
                                       const uint_vec& to,
                                       const edit_node_mat_t& edits,
                                       const StringMapper& mapper):
        id_(id),
        cost_(edits[from.size()][to.size()].cost),
        n_ref_words_(to.size()-1){

    for(EditNode node = edits[from.size()][to.size()];
            node.id != NONE;
            node = edits[node.from_i][node.from_j]){
        path_.emplace_front(
                ResultNode(node.id, mapper(from[node.from_i]), mapper(to[node.from_j]))
                    );
        ++stats_[edit_operation_names(node.id)];
    }
}


} // namespace werpp
