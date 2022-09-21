//
// Created by mosta on 8/23/2022.
//

#include<time.h>
#include "Terminal.h"

extern uint8_t Terminate;

// This function gets the date from the system date then some calculations are done to save it in the form of dd/mm/yyyy
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    if(!Terminate){
        time_t t;
        t = time(NULL);
        struct tm tm = *localtime(&t);
        uint32_t dy, mn, yy;
        dy = tm.tm_mday;
        mn = tm.tm_mon+1;
        yy = tm.tm_year+1900;

        //putting every digit in the number in a certain index in the array.
        termData->transactionDate[0] = dy/10 +48;
        termData->transactionDate[1] = dy%10 +48;

        // 47 represents the '/' in ascii.
        termData->transactionDate[2] = 47;

        termData->transactionDate[3] = mn/10 +48;
        termData->transactionDate[4] = mn%10 +48;

        termData->transactionDate[5] = 47;

        termData->transactionDate[6] = yy/1000 +48;
        termData->transactionDate[7] = (yy/100)%10 +48;
        termData->transactionDate[8] = (yy/10)%10 +48;
        termData->transactionDate[9] = yy%10 +48;

        termData->transactionDate[10] = '\0';
        return TERMINAL_OK;
    }
}

//This function calculate then compare the expiry date and the terminal date
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    if(!Terminate){
        uint8_t Exp_year = (cardData.cardExpirationDate[3]-'0') *10 + (cardData.cardExpirationDate[4]-'0');
        uint8_t Term_year = (termData.transactionDate[8]-'0') * 10 + (termData.transactionDate[9]-'0');

        uint8_t Exp_month = (cardData.cardExpirationDate[0]-'0') *10 + (cardData.cardExpirationDate[1]-'0');
        uint8_t Term_month = (termData.transactionDate[3]-'0') * 10 + (termData.transactionDate[4]-'0');

        if(Exp_year < Term_year){
            printf("EXPIRED_CARD\n");
            Terminate =1;
            return EXPIRED_CARD;
        }else if(Exp_year==Term_year){
            if(Exp_month < Term_month){
                printf("EXPIRED_CARD\n");
                Terminate =1;
                return EXPIRED_CARD;
            } else{
                return TERMINAL_OK;
            }
        }else{
            return TERMINAL_OK;
        }
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    if(!Terminate){
        float in;
        printf("Enter transaction amount [>0]: ");
        scanf("%f", &in);

        //check if the input is less than zero
        if(in <= 0){
            printf("INVALID_AMOUNT");
            Terminate =1;
            return INVALID_AMOUNT;
        } else{
            printf("\n");
            termData->transAmount = in;
            return TERMINAL_OK;
        }
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    if(!Terminate){
        float in;
        printf("Enter Max amount: ");
        scanf("%f", &in);

        //check if the input is less than zero
        if(in <= 0){
            printf("INVALID_MAX_AMOUNT");
            Terminate =1;
            return INVALID_MAX_AMOUNT;
        } else{
            printf("\n");
            termData->maxTransAmount = in;
            return TERMINAL_OK;
        }
    }
}

//This function compare between the max and transaction amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(!Terminate){
        if(termData->transAmount > termData->maxTransAmount){
            printf("EXCEED_MAX_AMOUNT");
            Terminate =1;
            return EXCEED_MAX_AMOUNT;
        }else{
            printf("\n");
            return TERMINAL_OK;
        }
    }
}



