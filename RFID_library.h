struct RFID_CARD{
   char *NAME;
   char *PASSWD;
   unsigned char CARD_UNIQUE_ID[4];
}CARD[4];
unsigned char received_CARD_ID[4];
char correctCard=0;
int user;

void RFID_ACCOUNT_DETAILS(){
   /////////////////////////////////
   CARD[0].NAME = "USER1";
   CARD[0].PASSWD = "1234";
   CARD[0].CARD_UNIQUE_ID[0] = 'C';
   CARD[0].CARD_UNIQUE_ID[1] = 'B';
   CARD[0].CARD_UNIQUE_ID[2] = '2';
  
   CARD[1].NAME = "USER2";
   CARD[1].PASSWD = "4321";
   CARD[1].CARD_UNIQUE_ID[0] = '8';
   CARD[1].CARD_UNIQUE_ID[1] = 'A';
   CARD[1].CARD_UNIQUE_ID[2] = '0';

   CARD[2].NAME = "USER3";
   CARD[2].PASSWD = "1111";
   CARD[2].CARD_UNIQUE_ID[0] = '6';
   CARD[2].CARD_UNIQUE_ID[1] = 'F';
   CARD[2].CARD_UNIQUE_ID[2] = 'F';

   CARD[3].NAME = "USER4";
   CARD[3].PASSWD = "2222";
   CARD[3].CARD_UNIQUE_ID[0] = '2';
   CARD[3].CARD_UNIQUE_ID[1] = '1';
   CARD[3].CARD_UNIQUE_ID[2] = '6';
   ////////////////////////////////
}