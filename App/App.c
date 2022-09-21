#include "App.h"

// Terminate is a global variable used (extern) in all files to track whether the program should terminate or not.
// With (0) as initial value, it represents the OK sign for the program to continue.
uint8_t Terminate = 0;

// Three struct variables that save data over the whole process
ST_cardData_t A_cardData;
ST_terminalData_t A_termData;
ST_transaction_t A_transData;



void appStart(void){
    //The first 3 functions take the address of the A_cardData as input to check and save card data
    getCardHolderName(&A_cardData);
    getCardExpiryDate(&A_cardData);
    getCardPAN(&A_cardData);

    //These functions take the address of the A_termData as input to check and save Terminal data
    getTransactionDate(&A_termData);
    isCardExpired(A_cardData, A_termData);
    getTransactionAmount(&A_termData);
    setMaxAmount(&A_termData);
    isBelowMaxAmount(&A_termData);

    //Here, both the card and terminal data are transferred into the A_transData (server module)
    A_transData.cardHolderData = A_cardData;
    A_transData.terminalData = A_termData;

    //Here server module check the validity of the account and balance and save the whole transaction
    recieveTransactionData(&A_transData);
    saveTransaction(&A_transData);

    //Resitting the Terminate variable for the program to function in multiple processes
    Terminate =0;
}