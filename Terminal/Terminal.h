//
// Created by mosta on 8/23/2022.
//

#ifndef FWD_PROJECT_TERMINAL_H
#define FWD_PROJECT_TERMINAL_H

#include "../Card/Card.h"

/* Function prototypes & structs & enums related to the terminal module*/

typedef enum EN_terminalError_t
    {
        TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
    }EN_terminalError_t ;


    typedef struct ST_terminalData_t
    {
        float transAmount;
        float maxTransAmount;
        uint8_t transactionDate[11];
    }ST_terminalData_t;



    EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
    EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
    EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
    EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
    EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);





#endif //FWD_PROJECT_TERMINAL_H
