#include <list>

#include <color_error/edit_operation.h>

namespace werpp {

EditNode SubstitutionOperation::edit_op(const edit_node_mat_t& cost_matrix,
                                               const uint_vec& from,
                                               const uint_vec& to,
                                               const unsigned int& i,
                                               const unsigned int& j){
    return EditNode(from[i-1]==to[j-1]?EQUAL:SUBSTITUTION,
                    i-1,
                    j-1,
                    cost_matrix[i-1][j-1].cost + (from[i-1]==to[j-1]?eq_cost_:sub_cost_));
}

EditNode InsertionOperation::edit_op(const edit_node_mat_t& cost_matrix,
                                            const uint_vec& from,
                                            const uint_vec& to,
                                            const unsigned int& i,
                                            const unsigned int& j){
    return EditNode(INSERTION,
                    i-1,
                    j,
                    cost_matrix[i-1][j].cost + cost_);
}

EditNode DeletionOperation::edit_op(const edit_node_mat_t& cost_matrix,
                                           const uint_vec& from,
                                           const uint_vec& to,
                                           const unsigned int& i,
                                           const unsigned int& j){
    return EditNode(DELETION,
                    i,
                    j-1,
                    cost_matrix[i][j-1].cost + cost_);
}

} // namespace werpp
