#include "parking_system.hpp"   // adjust if your header name differs
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

static void printUsage() {
    std::cout
        << "ParkingSystem CLI\n\n"
        << "Usage:\n"
        << "  parking_cli --big N --medium N --small N [--cars t1 t2 ...]\n\n"
        << "Required:\n"
        << "  --big N       number of big slots\n"
        << "  --medium N    number of medium slots\n"
        << "  --small N     number of small slots\n\n"
        << "Optional:\n"
        << "  --cars ...    sequence of car types to add; prints result per car\n"
        << "               carType: 1=big, 2=medium, 3=small\n\n"
        << "Examples:\n"
        << "  parking_cli --big 1 --medium 1 --small 1 --cars 1 2 3 3\n"
        << "  parking_cli --big 2 --medium 0 --small 0 --cars 1 1 1\n"
        << "  parking_cli --big 1 --medium 1 --small 1\n";
}

static int toInt(const std::string& s) {
    char* end = nullptr;
    long v = std::strtol(s.c_str(), &end, 10);
    if (!end || *end != '\0') throw std::runtime_error("Not an integer: " + s);
    return static_cast<int>(v);
}

int main(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc > 1 ? static_cast<size_t>(argc - 1) : 0);
    for (int i = 1; i < argc; ++i) args.emplace_back(argv[i]);

    if (args.empty() || args[0] == "--help" || args[0] == "-h") {
        printUsage();
        return 0;
    }

    bool hasBig=false, hasMed=false, hasSmall=false;
    int big=0, med=0, small=0;
    std::vector<int> cars;

    for (size_t i = 0; i < args.size(); ) {
        const std::string& tok = args[i];

        auto needValue = [&](const std::string& flag) -> std::string {
            if (i + 1 >= args.size()) throw std::runtime_error("Missing value after " + flag);
            return args[i + 1];
        };

        if (tok == "--big") {
            big = toInt(needValue(tok));
            hasBig = true;
            i += 2;
            continue;
        }
        if (tok == "--medium") {
            med = toInt(needValue(tok));
            hasMed = true;
            i += 2;
            continue;
        }
        if (tok == "--small") {
            small = toInt(needValue(tok));
            hasSmall = true;
            i += 2;
            continue;
        }

        if (tok == "--cars") {
            i += 1; // consume --cars
            while (i < args.size() && !args[i].empty() && args[i][0] != '-') {
                cars.push_back(toInt(args[i]));
                i += 1;
            }
            continue;
        }

        if (tok == "--help" || tok == "-h") {
            printUsage();
            return 0;
        }

        throw std::runtime_error("Unknown argument: " + tok);
    }

    if (!hasBig || !hasMed || !hasSmall) {
        std::cerr << "Error: missing required flags: --big --medium --small\n\n";
        printUsage();
        return 2;
    }
    if (big < 0 || med < 0 || small < 0) {
        std::cerr << "Error: slot counts must be >= 0\n";
        return 2;
    }

    ParkingSystem ps(big, med, small);

    for (int t : cars) {
        if (t < 1 || t > 3) {
            std::cout << "false\n"; // or print an error; keeping it simple
            continue;
        }
        bool ok = ps.addCar(t);
        std::cout << (ok ? "true" : "false") << "\n";
    }

    return 0;
}