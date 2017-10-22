#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <color_error/edit_distance.h>
#include <color_error/edit_distance_printer.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cerr << "USAGE: color_error <transcribe_sentences> <reference_sentences>" << std::endl;
        return 1;
    }

    std::ifstream rec_file(argv[1]), ref_file(argv[2]);

    werpp::WEREditDistance wer_edit;

    unsigned int i = 0;
    for(std::string rec_line, ref_line;
            std::getline(rec_file, rec_line) &&
            std::getline(ref_file, ref_line);){

        std::vector<std::string> from, to;
        std::istringstream split_rec(rec_line), split_ref(ref_line);

        for(std::string rec_word;
            std::getline(split_rec, rec_word, ' ');
            from.emplace_back(rec_word));
        for(std::string ref_word;
            std::getline(split_ref, ref_word, ' ');
            to.emplace_back(ref_word));

        auto wer_result = wer_edit(std::to_string(i++), from, to);
        werpp::EditDistancePrinterTerminal printer(wer_result);
        std::cout << printer;

    }
    std::cout << "WER: " << wer_edit.error_rate() << " ";
    for(auto kv: wer_edit.stats())
        std::cout << kv.first << " " << kv.second << " ";
    std::cout << std::endl;

    return 0;
}
