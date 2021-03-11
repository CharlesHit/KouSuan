/*
  Author: Charles, charles.m.hau@gmail.com
  Date: 12:22 AM, 2021-03-11
  
  Description: 
  
  * the auxiliary function of Kou Suan
*/

#ifndef KOUSUAN_AUX_FUNCTIONS_H
#define KOUSUAN_AUX_FUNCTIONS_H

char int_to_opcode(int op) {
    switch ( op ) {
        case 0:
            return '+';
        case 1:
            return '-';
        case 2:
            return '*';
        case 3:
            return '/';
        default:
            return '?';
    }
}

// for vertical printing. e.g.
// 2 + 2
// =>
//    2
// +  2
// ------
std::string &&vertical_format(std::string &&s, char oprand_at_head, unsigned short max_width = 4) {
    char buff[100];
    sprintf(buff, "%c%*s%4s\n", oprand_at_head, max_width, " ", s.c_str());
    s = buff;
    return std::forward<std::string>(s);
}

// waiting for user's pressing return.
void pause_for_return () {
    std::cin.clear();
    std::string temp;
    getline(std::cin, temp);
}

// check if an option exists
bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

// grab the options' content
char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if ( itr != end && ++itr != end ) {
        return *itr;
    }
    return nullptr;
}
#endif //KOUSUAN_AUX_FUNCTIONS_H
