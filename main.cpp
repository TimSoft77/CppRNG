#include <iostream>
#include <random>
#include <array>
#include <chrono>
#include <fstream>
#include <sstream>

int main()
{
    // Setup
    int passwordLength = 16;
    float alSym = 1.0; // !@#$%^&*()+ TODO refine
    float alN = 1.0;
    float alL = 1.0;
    float alU = 1.0;
    float alSim = 0.0; // iI1loO0 TODO implement

    // Revise data per file
    std::ifstream setupFile;
    std::string str;
    bool b;
    setupFile.open("setup.txt");
    if (setupFile)
    {
        std::string line;
        {
            // Password length
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> passwordLength;
        }
        {
            // Allow symbols
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> b;
            if (b)
            {
                alSym = 1.0;
            }
            else
            {
                alSym = 0.0;
            }
        }
        {
            // Allow numbers
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> b;
            if (b)
            {
                alN = 1.0;
            }
            else
            {
                alN = 0.0;
            }
        }
        {
            // Allow lowercase
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> b;
            if (b)
            {
                alL = 1.0;
            }
            else
            {
                alL = 0.0;
            }
        }
        {
            // Allow uppercase
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> b;
            if (b)
            {
                alU = 1.0;
            }
            else
            {
                alU = 0.0;
            }
        }
        {
            // Allow similar
            getline(setupFile, line);
            std::istringstream sline(line);
            sline >> str >> b;
            if (b)
            {
                alSim = 1.0;
            }
            else
            {
                alSim = 0.0;
            }
        }
    }

    // obtain a seed from the timer based on user input
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    std::cout << "Press enter to continue";
    std::cin.get();
    myclock::duration d = myclock::now() - beginning;
    unsigned seed = d.count();

    // Set up random generator and distribution
    // Reference: https://en.cppreference.com/w/cpp/language/ascii
    std::mt19937_64 gen(seed); // TODO replace with a CSPRNG, e.g., https://github.com/Duthomhas/CSPRNG
    std::array<float, 7> intervals{33.0, 48.0, 58.0, 41.0, 91.0, 97.0, 123.0};
    std::array<float, 6> weights{alSym, alN, 0.0, alU, 0.0, alL};
    std::piecewise_constant_distribution<float> dist(intervals.begin(), intervals.end(), weights.begin());

    // Generate passord
    std::string password;
    for (int i = 0; i < passwordLength; i++)
    {
        password.push_back(static_cast<char>(dist(gen)));
    }
    std::cout << password;
}
