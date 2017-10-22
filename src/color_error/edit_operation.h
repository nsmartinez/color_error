#ifndef __EDIT_OPERATION_H__
#define __EDIT_OPERATION_H__

#include <vector>
#include <string>
#include <map>
#include <exception>

#include <color_error/edit_node.h>

namespace werpp {

typedef std::vector<unsigned int> uint_vec;
typedef std::vector<uint_vec> uint_mat;

class AbstractEditOperation {
    const EditOperationId id_ = NONE;
public:
    AbstractEditOperation(const EditOperationId& id):id_(id){}
    virtual ~AbstractEditOperation(){}
    virtual EditNode edit_op(const edit_node_mat_t& cost_matrix,
                                    const uint_vec& from,
                                    const uint_vec& to,
                                    const unsigned int& i,
                                    const unsigned int& j) = 0;
    inline const EditOperationId& id() const {return id_;}
};

class SubstitutionOperation : public AbstractEditOperation {
    const unsigned int sub_cost_ = 1, eq_cost_ = 0;

public:
    SubstitutionOperation():AbstractEditOperation(SUBSTITUTION){}
    EditNode edit_op(const edit_node_mat_t& cost_matrix,
                     const uint_vec& from,
                     const uint_vec& to,
                     const unsigned int& i,
                     const unsigned int& j);
};

class InsertionOperation : public AbstractEditOperation {
    const unsigned int cost_ = 1;

public:
    InsertionOperation():AbstractEditOperation(INSERTION){}
    EditNode edit_op(const edit_node_mat_t& cost_matrix,
                     const uint_vec& from,
                     const uint_vec& to,
                     const unsigned int& i,
                     const unsigned int& j);
};

class DeletionOperation : public AbstractEditOperation {
    const unsigned int cost_ = 1;

public:
    DeletionOperation():AbstractEditOperation(DELETION){}
    EditNode edit_op(const edit_node_mat_t& cost_matrix,
                     const uint_vec& from,
                     const uint_vec& to,
                     const unsigned int& i,
                     const unsigned int& j);
};

class AbstractOperationException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Unknow Operation";
  }
};

} // namespace werpp
#endif
