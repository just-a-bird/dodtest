#include "conditions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#if WIN32
#include <conio.h>
#else
#include "kbhit.h"
#endif

outputTable runConditions(const personTable &persons) {
    outputTable outputs;

    vector<conditionRow> conditionRows = {
//      { >=40k?, >=80K?, MARRIED?, KIDS?, WIDOW?,                          _output },
        {    YES,    ANY,      ANY,   ANY,    ANY,            &outputs._taxBracketA },
        {    YES,    YES,      ANY,   ANY,    ANY,            &outputs._taxBracketB },
        {    ANY,     NO,      ANY,   YES,    ANY,    &outputs._childCareAssistance },
        {    ANY,    ANY,       NO,   YES,    ANY, &outputs._singleParentAssistance },
        {    ANY,     NO,      ANY,   ANY,    YES,       &outputs._widowsAssistance }
    };

    /* All five bits are there, any zero = failure to match */
    const unsigned int meetsAll = 0b11111;

    vector<readyToExecConditionRow> rows;
    /* Skipping the bit where you compute the masks, ideally both of these
       things would already be computed, though it wouldn't take long' */

    for (unsigned int i = 0; i < persons.size(); i++) {
        unsigned int conditions = 0;
        conditions |= (persons._salary[i] >= 40000.00)                   << 0;
        conditions |= (persons._salary[i] >= 80000.00)                   << 1;
        conditions |= (persons._marriageStatus[i] == TOGETHER)           << 2;
        conditions |= (persons._parentStatus[i] == HAS_CHILDREN)         << 3;
        conditions |= (persons._marriageStatus[i] == PARTNER_DECEASED)   << 4;

        for (unsigned int j = 0; j < rows.size(); j++) {
            unsigned int conditionsMet = (conditions ^ rows[j]._xorMask) | rows[j]._ignoreMask;
            if (conditionsMet == meetsAll) {
                rows[j]._output->push_back(i);
            }
        }
    }
    return outputs;
}


int main(int argc, char* argv[]) {
    const unsigned int peopleCount = 10;
    personTable persons = personTable();
    srand((unsigned int)time(NULL));

    for (unsigned int i = 0; i < peopleCount; i++) {
        
    }

    while (!_kbhit());

    return 0;
}