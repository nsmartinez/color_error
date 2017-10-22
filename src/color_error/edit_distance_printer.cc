#include <color_error/edit_distance_printer.h>

namespace werpp {


EditDistancePrinter::EditDistancePrinter(const EditDistanceResult& sample):sample_(sample){}


EditDistancePrinterTerminal::EditDistancePrinterTerminal(const EditDistanceResult& sample):
    EditDistancePrinter(sample){}


std::ostream& operator<<(std::ostream& out, const EditDistancePrinterTerminal &printer){

    out << "Id: " << printer.sample_.id() << " Cost: " << printer.sample_.error_rate() << " " ;
    for(auto op : printer.sample_.stats())
        out << op.first << " " << op.second << " ";
    out << std::endl;


    for(const auto& result_node: printer.sample_.path()){
        if(result_node.operation == EQUAL){
            out << result_node.from_w;
        } else if(result_node.operation == SUBSTITUTION){
            out << printer.kcolor_blue_ << result_node.from_w << "->"
                << result_node.to_w << printer.kcolor_reset_;
        } else if(result_node.operation == INSERTION){
            out << printer.kcolor_green_ << result_node.from_w << printer.kcolor_reset_;
        } else if(result_node.operation == DELETION){
            out << printer.kcolor_red_ << result_node.to_w << printer.kcolor_reset_;
        } else {
            throw AbstractOperationException();
        }
        out << " ";
    }
    out << std::endl;

    return out;
}

} // namespace werpp
