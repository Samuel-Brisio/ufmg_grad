#ifndef GPHPP
#define GPHPP

#include <iostream>
#include <vector>

class GaleShapley {
    public:
        GaleShapley(
            std::vector <char> proposeSideList,
            std::vector < int > passiveSideList,
            std::vector < std::vector < int > > proposeSidePreference,
            std::vector < std::vector < int > > passiveSidePreference
            );

        void gpExecution();
        void printResult();

    private:

        void inicializeUnmatchConteiner();

};

#endif