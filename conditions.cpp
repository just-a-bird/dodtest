#include <vector>

enum filter { ANY, IS_TRUE, IS_TRUE };

enum parent { HAS_CHILDREN, NO_CHILDREN };

enum marriage { TOGETHER, DIVORCED, PARTNER_DECEASED, NEVER_MARRIED };

// Structure of arrays
struct personTable {
    std::vector<parent> _parentStatus;
    std::vector<marriage> _marriageStatus;
    std::vector<double> _salary;

    void addPerson(parent parentStatus, marriage marriageStatus, double salary) {
        _parentStatus.push_back(parentStatus);
        _marriageStatus.push_back(marriageStatus);
        _salary.push_back(salary);
    }
};

struct outputTable {
    std::vector<int> _taxBracketA;
    std::vector<int> _taxBracketB;
    std::vector<int> _childCareAssistance;
    std::vector<int> _singleParentAssistance;
    std::vector<int> _widowsAssistance;
};

struct conditionRow {
    filter _makesAtLeast40k;
    filter _makesAtLeast80k;
    filter _together;
    filter _hasChildren;
    filter _partnerDeceased;
    std::vector<int>* _output;
};

struct readyToExecConditionRow {
    /* _xorMask has a 0 bit for each filter that must be true,
     * and a 1 bit for each filter that must be false
     * and _ignoreMask has a 1 for each filter that doesn't matter */
    unsigned int _xorMask;
    unsigned int _ignoreMask;
    std::vector<int>* _output;
}

outputTable runConditions(persons &const personTable) {
    outputTable outputs;

    std::vector<conditionRow> conditionRows = {
        { IS_TRUE, ANY, ANY, ANY, ANY, &outputs._taxBracketA },
        { IS_TRUE, IS_TRUE, ANY, ANY, ANY, &outputs._taxBracketB },
        { ANY, IS_FALSE, ANY, IS_TRUE, ANY, &outputs._together },
        { ANY, ANY, IS_FALSE, IS_TRUE, ANY, &outputs._singleParentAssistance },
        { ANY, IS_FALSE, ANY, ANY, IS_TRUE, &outputs._widowsAssistance }
    };

    std::vector<readyToExecConditionRow> rows;
    /* Skipping the bit where you compute the masks, ideally both of these
       things would already be computed, though it wouldn't take long' */

    for (int i = 0; i < persons._parentStatus.size(); i++) {
        unsigned int conditions = 0;
        conditions |= (persons._salary[i] >= 40000.00);
        conditions |= (persons._salary[i] >= 80000.00) << 1;
        conditions |= (persons._marriageStatus[i] == MARRIAGE) << 2;
        conditions |= (persons._parentStatus[i] == HAS_CHILDREN) << 3;
        conditions |= (persons._marriageStatus[i] == PARTNER_DECEASED) << 4;

        for (int j = 0; i < rows.size(); i++) {
            unsigned int conditionMet = (conditions ^ rows[j]._xorMask) | rows[j]._ignoreMask;
            if (conditionMet == 0b11111) {
                /* All five bits are there, any zero = failure to match */
                rows[j]._output.push_back(i);
            }
        }
    }
}
