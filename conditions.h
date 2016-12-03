#pragma once
#include <vector>
using namespace std;


enum filter { ANY, YES, NO };

enum parent { HAS_CHILDREN, NO_CHILDREN };

enum marriage { TOGETHER, DIVORCED, PARTNER_DECEASED, NEVER_MARRIED };

// Structure of arrays
struct personTable {
    vector<parent> _parentStatus;
    vector<marriage> _marriageStatus;
    vector<double> _salary;
    
    void addPerson(parent parentStatus, marriage marriageStatus, double salary) {
        _parentStatus.push_back(parentStatus);
        _marriageStatus.push_back(marriageStatus);
        _salary.push_back(salary);
    }

    unsigned int size() const {
        return _salary.size();
    }
};

struct outputTable {
    vector<int> _taxBracketA;
    vector<int> _taxBracketB;
    vector<int> _childCareAssistance;
    vector<int> _singleParentAssistance;
    vector<int> _widowsAssistance;
};

struct conditionRow {
    filter _makesAtLeast40k;
    filter _makesAtLeast80k;
    filter _together;
    filter _hasChildren;
    filter _partnerDeceased;
    vector<int>* _output;
};

struct readyToExecConditionRow {
    /* _xorMask has a 0 bit for each filter that must be true,
    * and a 1 bit for each filter that must be false
    * and _ignoreMask has a 1 for each filter that doesn't matter */
    unsigned int _xorMask;
    unsigned int _ignoreMask;
    vector<int>* _output;
};

outputTable runConditions(personTable const & persons);