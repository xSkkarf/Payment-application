//
// Created by mosta on 8/23/2022.
//

#include "Server.h"

extern uint8_t Terminate;

// Pointer of type ST_accountsDB_t to mark the specific account that contain the key PAN it is searching for.
ST_accountsDB_t *ref;

// Sample accounts with different PANS, states, and balances.
ST_accountsDB_t DB_arr[255] = { {1000, RUNNING, "789456123123456798"},
                                {5000, RUNNING, "456123789456123789"},
                                {3000, BLOCKED, "123798456123465987"},
                                {2000, RUNNING, "321654987456132798"},
                                {9000, BLOCKED, "654789123654987321"},
                                {7000, RUNNING, "648971248962468452"},
                                {6000, BLOCKED, "654987123456798732"},
                                {1000, BLOCKED, "321546789513654897"},
                                {4000, RUNNING, "136871323216548751"},
                                {8000, RUNNING, "645854132168787654"}};

// Transaction history array initialized with zeros.
ST_transaction_t Trans_arr[256] = {0};

// global sequence number.
uint32_t seq_num=1;

// This variable saves the state of the transaction whether it is approved or declined (with reason).
EN_transStat_t result;


// This function does some checks on the card and terminal using the other functions.
EN_transStat_t recieveTransactionData(ST_transaction_t *transData){

    /* If anything other than SERVER_OK is returned this means 1,
       then the condition is met and result variable saves return condition.*/

    // here, ref is passed by reference to change its value if the key is found in the database.
    if(isValidAccount(transData->cardHolderData, &ref)){
        printf("FRAUD_CARD\n");
        result = FRAUD_CARD;
        return FRAUD_CARD;
    }

    if(isBlockedAccount(ref)){
        printf("DECLINED_STOLEN_CARD\n");
        result = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(isAmountAvailable(&transData->terminalData)){
        printf("DECLINED_INSUFFECIENT_FUND\n");
        result = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }

    // If the data passed all the checks, the balance is updated in the database and the result saves APPROVED.
    ref->balance -= transData->terminalData.transAmount;
    result = APPROVED;
    printf("Transaction is successful!\n");
    return APPROVED;
}

// This function search for the PAN in the database
// I changed the parameter from normal variable to (pointer to pointer) in order to pass (ref) by reference and change it.
EN_serverError_t isValidAccount(ST_cardData_t cardData, ST_accountsDB_t **accountRefrence){
    if(!Terminate){
        uint8_t flag = 0;

        // it loops over the whole array (linear search) and use strcmp() function to compare the whole string.
        // strcmp() returns 0 if the two strings are equal.
        for (int i = 0; i < 10; i++) {
            if (strcmp(cardData.primaryAccountNumber, DB_arr[i].primaryAccountNumber) == 0) {

                // In case the two strings are equal, the value that (ref) holds changes to the specific account in database.
                *accountRefrence = &DB_arr[i];
                flag = 1;
            }
        }

        if (flag) {
            return SERVER_OK;
        } else {
            printf("ACCOUNT_NOT_FOUND\n");
            Terminate = 1;
            return ACCOUNT_NOT_FOUND;
        }
    }
}

// Checks on the state of the account.
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(!Terminate){
        if(ref->state == BLOCKED){
            Terminate =1;
            printf("BLOCKED_ACCOUNT\n");
            return BLOCKED_ACCOUNT;
        } else{
            return SERVER_OK;
        }
    }
}

// Checks on the balance of the account and compare it to the transaction amount.
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(!Terminate){
        if (termData->transAmount > ref->balance) {
            Terminate = 1;
            printf("LOW_BALANCE\n");
            return LOW_BALANCE;
        }else{
            return SERVER_OK;
        }
    }
}

// Saves result to the transaction data variable as well as the sequence number.
EN_serverError_t saveTransaction(ST_transaction_t *transData){

    transData->transState = result;
    transData->transactionSequenceNumber = seq_num;

    //Then adds the whole variable (transaction data) to the transaction history array.
    Trans_arr[seq_num] = *transData;

    //increment sequence number for the next operation.
    seq_num++;

    //don't really understand the purpose of this function (getTransaction)
    getTransaction(transData->transactionSequenceNumber, transData);


}

// If the sequence number of any variable is 0, that means it is not saves yet, because sequence number's initial value is 1.
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    if(Trans_arr[transactionSequenceNumber].transactionSequenceNumber == 0){
        printf("TRANSACTION_NOT_FOUND\n");
        return TRANSACTION_NOT_FOUND;
    }else{
        return SERVER_OK;
    }
}
