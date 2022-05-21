//
// Created by zach on 5/20/22.
//

#ifndef DISCORD_BOT_UTIL_H
#define DISCORD_BOT_UTIL_H


#include <vector>

namespace util
{
    std::pair<long int, long int> find_item_in_list();
    void reset_file_ptr(std::fstream& stream);
    void remove_item_from_list(std::pair<long int, long int> location, int idx);
    void clear_line(long int pos, std::fstream& stream, std::size_t end);
    void mk_backup(std::string&& file_loc);

    template <typename T>
    void print_vec(std::vector<T>& v);
}


#endif //DISCORD_BOT_UTIL_H
