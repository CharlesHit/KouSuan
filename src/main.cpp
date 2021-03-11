/*
  Author: Charles, charles.m.hau@gmail.com
  Date: 07:29 PM, 2021-03-09

  Description:

  * The string and objects of Kou Suan
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <random>

#include "structs.h"

// the random seed
std::random_device rd;

// print welcome info, and take user's input
void welcome_prompt() {
    std::cin.clear();
    printf("\n\nWelcome to\n\n%s\n", BANNER.c_str());
    printf("Press return to start, enter \"n\" or 0 to exit, enter \"h\" for help\n> ");
    std::string ans;
    getline(std::cin, ans);

    if ( ans == "n" || ans == "N" || ans == "0" ) {
        printf("%s", BYE.c_str());
        exit(0);
    }
    while ( ans == "h" || ans == "H" ) {
        std::cin.clear();
        printf("%s\n", INFO.c_str());
        std::getline( std::cin, ans );

        std::cin.clear();
        printf("Press return to start, enter \"n\" or 0 to exit, enter \"h\" for help\n> ");
        std::getline( std::cin, ans );

        if ( ans == "n" || ans == "N" || ans == "0" ) {
            printf("%s", BYE.c_str());
            exit(0);
        }
        else if ( ans != "h" && ans != "H" ) {
            break;
        }
    }
}

// grab options
Option generate_option(int argc, char **argv) {
    Option option;
    if ( cmdOptionExists(argv, argv + argc, "-h") ) {
        printf("%s\n", INFO.c_str());
    }

    if ( cmdOptionExists(argv, argv + argc, "-m") ) {
        option.mul = true;
    }

    if ( cmdOptionExists(argv, argv + argc, "-d") ) {
        option.digit = atoi(getCmdOption(argv, argv + argc, "-d"));
        if ( option.digit > 9999 ) {
            option.digit = 9999;
        }
        if ( option.digit <= 0 ) {
            option.digit = 0;
        }
    }

    if ( cmdOptionExists(argv, argv + argc, "-r") ) {
        option.round = atoi(getCmdOption(argv, argv + argc, "-r"));
        if ( option.round > 99 ) {
            option.round = 99;
        }
        if ( option.round <= 0 ) {
            option.round = 10;
        }
    }

    if ( cmdOptionExists(argv, argv + argc, "-l") ) {
        option.length = atoi(getCmdOption(argv, argv + argc, "-l"));
        if ( option.length > 8 ) {
            option.length = 6;
        }
        if ( option.length <= 2 ) {
            option.length = 2;
        }
    }

    if ( cmdOptionExists(argv, argv + argc, "-v") ) {
        option.vertical_print = true;
    }

    return option;
}

// at each round, generate an arithmetic
Problem generate_arithmetic(const Option &option) {
    Problem problem {"", 0, option.vertical_print};

    std::uniform_int_distribution<int> length_generator(2, option.length);
    std::uniform_int_distribution<int> opcode_generator(0, option.mul ? 2 : 1);
    std::uniform_int_distribution<int> number_generator(0, option.digit);

    int length = length_generator(rd);
    problem.answer = number_generator(rd);
    problem.problem_str = std::to_string(static_cast<int>(problem.answer));
    if ( option.vertical_print ) {
        vertical_format(std::move(problem.problem_str), NON_OPCODE);
    }

    int opcode, number;
    for (int i = 0; i < length - 1; i++) {
        opcode = opcode_generator(rd);
        number = number_generator(rd);
        if ( problem.vertical_print ) {
            problem.problem_str = problem.problem_str +
                                  vertical_format(std::to_string(static_cast<int>(number)), int_to_opcode(opcode));
        }
        else {
            problem.problem_str =
                    problem.problem_str + int_to_opcode(opcode) + std::to_string(static_cast<int>(number));
        }

        // TODO
        if ( opcode == 0 ) {
            problem.answer += number;
        }
        else if ( opcode == 1 ) {
            problem.answer -= number;
        }
    }

    problem.vertical_print ? problem.problem_str += SHORT_LINE : problem.problem_str;
    return problem;
}

// at each round, print user prompt, and decide if print "-"
void print_arith_prompt(Problem &problem) {
    printf("%s\n> ", problem.problem_str.c_str());
    if ( PRINT_NEGATIVE_SIGN && problem.answer < 0 ) {
        printf("-");
        problem.answer *= -1;
    }
}

// collect user's input and return an object "Result"
Result collect_answers(Problem &p, const Option &option, unsigned short &current_round) {
    // collect player's answer, take the time
    std::string ans;
    auto start = std::chrono::high_resolution_clock::now();
    std::cin >> ans;
    auto end = std::chrono::high_resolution_clock::now();

    // if it is the end of the game
    if ( ans == END_SIGN ) {
        return {false,
                static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()),
                option.round,
                END_ROUND,
                p};
    }

    // if the result is not a valid number
    if ( ans.at(0) < '0' || ans.at(0) > '9' ) {
        return {false,
                static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()),
                option.round,
                current_round,
                p};
    }

    return {p.answer == stoi(ans),
            static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()),
            option.round,
            current_round,
            p};
}

// Write a Result to an object FinalResult
// return false if stop writing and terminate current game
bool write_to_final_result(const Result &res, FinalResult &final_result, bool print_each_round, bool
vertical_print = false) {
    const char *status = res.success ? "SUCCESS" : "NONONOO";

    if ( res.current_round == END_ROUND ) {
        printf("Thanks for playing!\n");
        return false;
    }

    if ( print_each_round && !vertical_print ) {
        printf("#%d %s! %s = %.2d | %.2f sec\n\n", res.round - res.current_round, status, res.problem.problem_str
                .c_str(), res.problem.answer, res.sec / 1000);
    }
    if ( print_each_round && vertical_print ) {
        printf("#%d %s! ANS = %.2d | %.2f sec\n\n", res.round - res.current_round, status, res.problem.answer, res
                                                                                                                       .sec /
                                                                                                               1000);
    }

    if ( res.success ) {
        final_result.success += 1;
    }
    else {
        final_result.failure += 1;
    }
    final_result.totalSec += res.sec;

    return true;
}

// print end prompt, take user's input
bool end_prompt(FinalResult final_result) {
    printf("%s\n", final_result.to_string().c_str());
    printf("%s\n", END_SCREEN.c_str());
    printf("> ");
    std::string ans;
    while (ans != "y" && ans != "Y" && ans != "1"
            && ans != "n" && ans != "N" && ans != "0"
            && ans != "h" && ans !="H") {
        std::cin >> ans;
        if ( ans == "n" || ans == "N" || ans == "0" ) {
            printf("%s", BYE.c_str());
            exit(0);
        }
        else if ( ans == "h" || ans == "H" ) {
            printf("%s\n", INFO.c_str());
            pause_for_return();
            printf("\n> ");
            ans = "";
        }
        else return false;
    }
    return false;
}

// the procedure of a game. return the final result.
FinalResult game(const Option &option) {
    FinalResult final_result;
    printf("\nRound #%d, READY?\n\n", option.round);
    pause_for_return();
    std::cin.clear();
    // for each round
    for (unsigned short i = 0; i < option.round; i++) {
        Problem problem = generate_arithmetic(option);
        print_arith_prompt(problem);
        Result res = collect_answers(problem, option, i);
        if ( !write_to_final_result(res, final_result, true, problem.vertical_print) ) {
            break;
        }
    }
    return final_result;
}

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    welcome_prompt();
    const Option option = generate_option(argc, argv);
    bool exit = false;
    while (!exit) {
        FinalResult final_result = game(option);
        exit = end_prompt(final_result);
    }
    return 0;
}
