#include <color_error/edit_names.h>

namespace werpp {

const std::string& edit_operation_names(const EditOperationId& id){
    // wrapping a static global in a function to avoid initializastion problems
    static const std::map<EditOperationId, std::string> edit_ops_names {{NONE, "A"},
                                                                       {EQUAL, "E"},
                                                                       {SUBSTITUTION, "S"},
                                                                       {INSERTION, "I"},
                                                                       {DELETION, "D"}};
    return edit_ops_names.at(id);
}

} // namespace werpp
