//
// Created by mosta on 8/23/2022.
//
#include "Card.h"
extern uint8_t Terminate;


EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    uint8_t in[25];
    printf("Enter card holder name [20-24]: ");

    //input for the whole line (including spaces).
    gets(in);

    //(it) is an iterator to loop inside in[25].
    //(count) counts the number of characters except for the ' ' (space).
    uint8_t count=0, it=0;

    //looping over the whole input and eliminating any non-alphabetic characters
    while(in[it]!= '\0'){
        if(in[it]!=' '){
            if((in[it]>='a' && in[it]<= 'z') || (in[it]>='A' && in[it]<= 'Z')){
                count++;
            }
        }
        it++;
    }

    if(count < 20 || count > 24){
        printf("WRONG_NAME\n");

        //For all the following functions, any non-OK return will set the Terminate variable to 1.
        Terminate =1;
        return WRONG_NAME;
    }else{
        //Filling the input into name field in card data. Maye I could've used strcpy().
        for(int i=0; i< count ; i++){
            cardData->cardHolderName[i] = in[i];
        }
        printf("\n");
        return CARD_OK;
    }


}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    //For the following functions, there will be a safe check to see if the program should terminate or not.
    if (!Terminate) {
        uint8_t in[6];
        printf("Enter card expiry date [MM/YY]: ");
        scanf("%s", in);
        uint8_t c = 0;
        uint8_t flag = 1;

        for (int i = 0; i < 6; i++) {
            //Counting the '\0' as it is supposed to be 1 to meet the requirement. one '\0' means there are exactly 5 characters.
            if (in[i] == '\0') {
                c++;
            }

            //Checks that all the input are numbers, except for th '/'.
            if ((in[i] < '0' || in[i] > '9') && i != 2 && i != 5) {
                flag = 0;
            }
        }

        if(c!= 1 || flag!=1){
            printf("WRONG_EXP_DATE\n");
            Terminate =1;
            return WRONG_EXP_DATE;
        }else{

            //Checks that the input is a valid date (month <=12)
            if((in[0] - '0')*10 + (in[1] - '0') <=12 && in[2] == '/'){
                //Fill expiry date into card data
                for(int i=0; i< 6; i++){
                    cardData->cardExpirationDate[i] = in[i];
                }
                printf("\n");
                return CARD_OK;
            }else{
                printf("WRONG_EXP_DATE\n");
                Terminate =1;
                return WRONG_EXP_DATE;
            }
        }
    }
}






EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    if(!Terminate){
        uint8_t in[20];
        printf("Enter PAN [16-20]: ");
        scanf_s("%s", in, 20);
        uint8_t count=0;
        uint8_t flag =1;

        //Checks that all input are numbers
        while(in[count]!= '\0'){
            if(in[count] >'9' || in[count] <'0'){
                flag =0;
            }
            count++;
        }

        //Checks on the size requirement
        if(count < 16 || count > 20 || flag ==0){
            printf("WRONG_PAN\n");
            Terminate =1;
            return WRONG_PAN;
        }else{
            //Fill PAN into card data
            for(int i=0; i< count ; i++){
                cardData->primaryAccountNumber[i] = in[i];
            }
            printf("\n");
            return CARD_OK;
        }
    }
}

