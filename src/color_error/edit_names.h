#ifndef __EDIT_NAMES_H__
#define __EDIT_NAMES_H__

#include <map>
#include <string>

namespace werpp {

enum EditOperationId { NONE, EQUAL, SUBSTITUTION, INSERTION, DELETION };

const std::string& edit_operation_names(const EditOperationId& id);

} // namespace werpp
#endif
