//
// Created by mosta on 8/23/2022.
//

#ifndef FWD_PROJECT_CARD_H
#define FWD_PROJECT_CARD_H

//Since the Card.h is the lowest level of includes, I put here all the global includes.
#include <stdio.h>
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
/***************************************************************************************/


    //Function prototypes & structs & enums related to the card module//

    typedef enum EN_cardError_t
    {
        CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
    }EN_cardError_t;


    typedef struct ST_cardData_t
    {
        uint8_t cardHolderName[25];
        uint8_t primaryAccountNumber[20];
        uint8_t cardExpirationDate[6];
    }ST_cardData_t;


    EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
    EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
    EN_cardError_t getCardPAN(ST_cardData_t *cardData);




#endif //FWD_PROJECT_CARD_H
