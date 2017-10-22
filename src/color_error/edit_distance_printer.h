#include <string>
#include <iostream>
#include <fstream>

#include <color_error/edit_distance.h>

namespace werpp {

class EditDistancePrinter {
protected:
    const EditDistanceResult& sample_;

public:
    EditDistancePrinter(const EditDistanceResult& sample);
};


class EditDistancePrinterTerminal : EditDistancePrinter {

    const std::string kcolor_reset_ = "\033[39m";
    const std::string kcolor_red_ = "\033[31m";
    const std::string kcolor_green_ = "\033[32m";
    const std::string kcolor_blue_ = "\033[34m";


public:
    EditDistancePrinterTerminal(const EditDistanceResult& sample);

    friend std::ostream& operator<<(std::ostream& out, const EditDistancePrinterTerminal &printer);
};

} // namespace werpp
