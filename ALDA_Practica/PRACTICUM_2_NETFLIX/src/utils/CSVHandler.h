// volledig gemaakt door robin
// doel: csv file lezen en in netflix inserten

#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include "../Netflix.h"
#include "internal/csv_reader.hpp"

class CSVHandler {
private:
    ///@brief reference naar de netflix waarin geinsert moet worden
    Netflix* netflix;
    /**
     * @brief splitst een comma separated string in een set van zijn substrings
     * @param str: volledige comma separated string
     * @return: set van substrings
     * @Author Robin
     */
    static std::unordered_set<std::string> splitString(const std::string& str);
public:
    explicit CSVHandler(Netflix* netflix);
    /**
     * @brief leest de csv file
     * @param fileName: csv file
     * @Author Robin
     */
    void handleCSV(const std::string& fileName);
};



#endif //CSVHANDLER_H
