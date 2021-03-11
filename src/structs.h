/*
  Author: Charles, charles.m.hau@gmail.com
  Date: 12:20 AM, 2021-03-11
  
  Description: 
  
  * The string and objects of Kou Suan
*/

#include "aux_functions.h"

#ifndef KOUSUAN_STRUCTS_H
#define KOUSUAN_STRUCTS_H

#define LINE "------------------------------------"
#define SHORT_LINE "----------"
#define NON_OPCODE ' '
#define END_SIGN "000"
#define END_ROUND 255
#define PRINT_NEGATIVE_SIGN true
#define VERSION "1.4.0"

const std::string COPYRIGHT = {
        "VER "
        VERSION
        " Charles H., charles.m.hau@gmail.com, Mar 9, 2021. CA"};

// help information
const std::string INFO {
        "             Kou Suan                \n\n"
        "\"Kou Suan\"(mental arithmetic) is an\n"
        "important part of Chinese elementary \n"
        "education. Candidates will calculate\n"
        "arithmetics with +/-/*/÷ within a time.\n"
        "\n"
        "             Options             \n\n"
        "          -h         help\n"
        "          -m         enable multiplication\n"
        "          -d         0~9999  range of numbers\n"
        "          -r         1~99 maximum round of games\n\n"
        "          -l         2~6 length of arithmetics\n\n"
        "          -v         enable vertical printing\n\n"
        "             Notes            \n\n"
        "  If the result is negative, \"-\" will be\n"
        "added for you.\n"
        "  enter \"" END_SIGN "\" to exit the game.\n\n"};

const std::string END_SCREEN = "GREAT JOB BRO! CONTINUE? (y/1/n/0/h)";

// welcome banner
const std::string BANNER {
        "██╗  ██╗ ██████╗ ██╗   ██╗    ███████╗██╗   ██╗ █████╗ ███╗   ██╗\n"
        "██║ ██╔╝██╔═══██╗██║   ██║    ██╔════╝██║   ██║██╔══██╗████╗  ██║\n"
        "█████╔╝ ██║   ██║██║   ██║    ███████╗██║   ██║███████║██╔██╗ ██║\n"
        "██╔═██╗ ██║   ██║██║   ██║    ╚════██║██║   ██║██╔══██║██║╚██╗██║\n"
        "██║  ██╗╚██████╔╝╚██████╔╝    ███████║╚██████╔╝██║  ██║██║ ╚████║\n"
        "╚═╝  ╚═╝ ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝\n"
        "                                                             " VERSION
        "\n                                                                                        "};

const std::string BYE {
        " ,ggggggggggg,   ,ggg,         gg    ,ggggggg, \n"
        "dP\"\"\"88\"\"\"\"\"\"Y8,dP\"\"Y8a        88  ,dP\"\"\"\"\"\"Y8b\n"
        "Yb,  88      `8bYb, `88        88  d8'    a  Y8\n"
        " `\"  88      ,8P `\"  88        88  88     \"Y8P'\n"
        "     88aaaad8P\"      88        88  `8baaaa     \n"
        "     88\"\"\"\"Y8ba      88        88 ,d8P\"\"\"\"     \n"
        "     88      `8b     88       ,88 d8\"          \n"
        "     88      ,8P     Y8b,___,d888 Y8,          \n"
        "     88_____,d8'      \"Y88888P\"88,`Yba,,_____, \n"
        "    88888888P\"             ,ad8888  `\"Y8888888 \n"
        "                          d8P\" 88              \n"
        "                        ,d8'   88              \n"
        "                        d8'    88              \n"
        "                        88     88              \n"
        "                        Y8,_ _,88              \n"
        "                         \"Y888P\"               "
};

// user's option
struct Option {
    unsigned short digit = 99;
    unsigned short round = 5;
    unsigned short length = 2;
    bool add = true;
    bool sub = true;
    bool mul = false;
    bool vertical_print = false;
};

// an arithmetic problem.
struct Problem {
    std::string problem_str;
    int answer;
    bool vertical_print = false;
};

// the result of each round
struct Result {
    bool success = true;
    float sec = 0.0;
    unsigned short round = 0;
    unsigned short current_round = 0;
    Problem problem;
};

// the result of all the round; a game
struct FinalResult {
    unsigned short success = 0;
    unsigned short failure = 0;
    float totalSec = 0;

    [[nodiscard]] std::string to_string() const {
        std::string rate = success + failure == 0 ?
                           "NO ROUND" :
                           std::to_string(((float)success) / (float)(success + failure) * 100);
        return std::string(LINE) + "\n"
                                   "SUCCESS: " + rate + "%  TIME: " + std::to_string(totalSec / 1000) + "\n"
               + LINE + "\n";
    }
};

#endif //KOUSUAN_STRUCTS_H
