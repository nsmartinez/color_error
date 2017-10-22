#ifndef __EDIT_NODE_H__
#define __EDIT_NODE_H__

#include <color_error/edit_names.h>

namespace werpp {

struct EditNode {
    EditOperationId id;
    unsigned int from_i, from_j, cost;

    EditNode():id(NONE),from_i(0u),from_j(0u),cost(0u){}
    EditNode(const EditOperationId &id,
             const unsigned int &from_i,
             const unsigned int &from_j,
             const unsigned int &cost):
        id(id), from_i(from_i), from_j(from_j), cost(cost){}
    // used in accumulate
    inline EditNode operator+(const EditNode& node){
        return (cost < node.cost)?*this:node;}
};

typedef std::vector<EditNode> edit_node_vec_t;
typedef std::vector<edit_node_vec_t> edit_node_mat_t;

} // namespace werpp
#endif
