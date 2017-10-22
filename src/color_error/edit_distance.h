#ifndef __EDIT_DISTANCE_H__
#define __EDIT_DISTANCE_H__

#include <vector>
#include <string>
#include <map>
#include <deque>
#include <unordered_map>

#include <color_error/edit_node.h>
#include <color_error/edit_operation.h>
#include <color_error/edit_distance_result.h>
#include <color_error/string_mapper.h>

namespace werpp {

class EditDistance {
    // edit operations in this operation
    std::vector<AbstractEditOperation*> edit_ops_;
    // counts of the edit_operation perfomed
    std::unordered_map<std::string, unsigned int> stats_;
    std::map<std::string, EditDistanceResult> results_;
    StringMapper string_map_;
protected:
    virtual void initialise(edit_node_mat_t& edits,
                            const unsigned int f_size,
                            const unsigned int t_size) = 0;
public:
    EditDistance(std::vector<AbstractEditOperation*> edit_ops);
    ~EditDistance(){for(auto x:edit_ops_) delete x;}
    EditDistanceResult& operator()(const std::string& id,
                                   const std::vector<std::string>& from_s,
                                   const std::vector<std::string>& to_s);


    const float error_rate() const;
    inline const StringMapper& string_map() { return string_map_; }
    inline const std::unordered_map<std::string, unsigned int> stats() { return stats_; }
};


class WEREditDistance : public EditDistance {
protected:
    void initialise(edit_node_mat_t& edits,
                    const unsigned int f_size,
                    const unsigned int t_size);
public:
    WEREditDistance():EditDistance(
            std::vector<AbstractEditOperation*>{
                new InsertionOperation(),
                new DeletionOperation(),
                new SubstitutionOperation()}){};
};


} // namespace werpp
#endif
