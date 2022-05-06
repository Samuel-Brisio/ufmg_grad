#ifndef GPHPP
#define GPHPP

#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

class GaleShapley {
    public:
        GaleShapley(
            std::vector <char> proposeSideList,
            std::vector < int > passiveSideList,
            std::vector < std::vector < int > > proposeSidePreference,
            std::vector < std::vector < char > > passiveSidePreference
            );

        void gpExecution();
        void printResult();

    private:
        std::vector <char> _proposeSideList;
        std::vector < int > _passiveSideList;
        std::vector < std::vector < int > > _proposeSidePreference;
        std::vector < std::vector < char > > _passiveSidePreference;

        std::queue <char> unmatch;
        std::map < char, int > track;
        std::map < char, int > proposeSideSolution;
        std::map < int, char > passiveSideSolution; 

        void inicializeUnmatchConteiner();
        void inicializeMaps();
        int findNextPassiveEntity(char proposeEnt); // find the next passive entity on the propose preference list
        bool passivePrefersProposer(char proposeEnt, int passiveEnt); // verify if the passive like the new propose more than the old one
};

#endif