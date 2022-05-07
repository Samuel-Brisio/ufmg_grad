#include "gs.hpp"

GaleShapley::GaleShapley(
    std::vector <char> proposeSideList,
    std::vector < int > passiveSideList,
    std::vector < std::vector < int > > proposeSidePreference,
    std::vector < std::vector < char > > passiveSidePreference
) {

_proposeSideList = proposeSideList;
_passiveSideList = passiveSideList;
_proposeSidePreference = proposeSidePreference;
_passiveSidePreference = passiveSidePreference;

inicializeUnmatchConteiner();
}

void GaleShapley::inicializeUnmatchConteiner() {
    for(auto elem: _proposeSideList) {
        unmatch.push(elem);
    }
}

int GaleShapley::findNextPassiveEntity(char proposeEnt) {
    int idxPropose = proposeEnt - 'a';
    int idxNextPassive = track[proposeEnt];

    return _proposeSidePreference[idxPropose][idxNextPassive]; 
}

bool GaleShapley::passivePrefersProposer(char proposeEnt, int passiveEnt) {
    char passiveActualMatch = passiveSideSolution[passiveEnt];

    for(auto e: _passiveSidePreference[passiveEnt]) {
        if( e == passiveActualMatch) return false;
        if( e == proposeEnt) return true;
    }

    assert(false); // if this instruction is executed something is very wrong
}

void GaleShapley::gpExecution() {
    while(unmatch.size() != 0) {
        char proposeEntity = unmatch.front();
        unmatch.pop();

        if (track.find(proposeEntity) == track.end()) track.insert(std::pair < char, int > (proposeEntity, 0));
        
        int passiveEntity = findNextPassiveEntity(proposeEntity);

        // passive is unmatch
        if ( passiveSideSolution.find(passiveEntity) == passiveSideSolution.end() ) { 
            proposeSideSolution.insert_or_assign(proposeEntity, passiveEntity);
            passiveSideSolution.insert_or_assign(passiveEntity, proposeEntity);
        }

        else {
            bool willChange = passivePrefersProposer(proposeEntity, passiveEntity);

            // passive prefers the new proposer
            if(willChange) {
                char oldProposeEntity = passiveSideSolution[passiveEntity];
                track[oldProposeEntity]++;
                
                passiveSideSolution[passiveEntity] = proposeEntity;
                proposeSideSolution.insert_or_assign(proposeEntity, passiveEntity);
            }

            // passive will not change his patner
            else {
                unmatch.push(proposeEntity);
                track[proposeEntity]++;
                assert(track[proposeEntity] < _passiveSideList.size()); // check if proposeEntity is unmatch after propose to all the passives
            }
        }
    }
}


void GaleShapley::printResult() {
    for(auto e: proposeSideSolution) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }

    std::cout << std::endl;

    for(auto e: passiveSideSolution) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }
}
