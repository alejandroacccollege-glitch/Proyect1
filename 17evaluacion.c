#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Reto 1
typedef enum {SENT, DELIVERED, FAILED} Status;

typedef struct {
    char text[50];
    Status status;
    char sender[20];
    int destinationCount;
    char *destination[20];
} Message;

//Reto 3
typedef enum {False, True} Boole;
typedef Boole (*FilterFunc)(Message *, void *);//Creates a pointer to a function kind bool 

void countMessages(Message *messaggeInserted, int N, char *userName, int *sent, int *recived)
{
    *sent = 0;
    *recived = 0;

    for (int i = 0; i < N; i ++){
    Message *messagePointer = messaggeInserted + i;
 
    if ((strcmp(userName, messagePointer->sender) == 0) 
    && (messagePointer->status == SENT)){
        (*sent)++;
    }// Validates if the user has a succesful message sent
    if ((strcmp(userName, messagePointer->sender) != 0) && (messagePointer->status == (DELIVERED))){
        for(int j = 0; j < messagePointer->destinationCount; j++){
            if ((strcmp(userName, *(messagePointer->destination + j)) == 0)){
                (*recived)++;
                break;
            }
        }
    }// Validates if the user has a succesful message recived
}
}

// Reto 5 (Funcion que se pasa de la función filterMessage)
Boole isMessageFrom(Message *message, void *data) {
    char *sender = (char*) data;
    return strcmp(message->sender, sender) == 0;
}// Looking for a sender in the given message

//Reto 4 
Message **filterMessage(Message **message, int N, FilterFunc filter, void *data, int *n){
    *n = 0;
    for(int i = 0; i < N; i++){
        if (filter(*(message + i), data) == True){ 
            (*n)++;
        }// Creates a new size of "n" if the there are a match data
    }

    Message **newArray = (Message**) malloc((*n)* sizeof(Message*));
    int helpIndex = 0; 

    for (int j = 0; j < N; j++){
        if (filter(*(message + j), data) == True){
            *(newArray + helpIndex) = *(message + j);
            helpIndex ++;
        }
    }// Fill a new array with the requested data
    return newArray;    
}

//Reto 6
void countVowels(char (*words)[30], int N, int *count) {
    for (int k = 0; k < 5; k++) {
        *(count + k) = 0;
    }

    for (int i = 0; i < N; i++) {
        int j = 0;
    
        while (*(*(words + i) + j) != '\0') {
            char character = *(*(words + i) + j);
            if (character == 'a' || character == 'A') {
                (*(count + 0))++;
            } else if (character == 'e' || character == 'E') {
                (*(count + 1))++;
            } else if (character == 'i' || character == 'I') {
                (*(count + 2))++;
            } else if (character == 'o' || character == 'O') {
                (*(count + 3))++;
            } else if (character == 'u' || character == 'U') {
                (*(count + 4))++;
            }

            j++;
        }
    }// Advances in each word adding 1 in the count
    //depending the vowel
}

int main(){
    //Reto 2
    Message listaMensajes[8] = {
        {"Hola Josue, reunion manana", DELIVERED, "ana", 1, {"josue"}},

        {"Enterado, ahi estare", SENT, "josue", 1, {"ana"}},

        {"Te paso el archivo", FAILED, "josue", 1, {"ana"}},

        {"Revision de avance de proyecto", DELIVERED, "carlos", 3, {"josue", "ana", "luis"}},

        {"Listo el reporte semanal", SENT, "josue", 1, {"pedro"}},

        {"Calificaciones publicadas", DELIVERED, "profesor", 2, {"ana", "josue"}},

        {"Fallo en la red", FAILED, "ana", 1, {"josue"}},

        {"Nos vemos en la tarde", DELIVERED, "pedro", 1, {"josue"}}
    };// An example of an array of messages kind Message
    int userSent = 0;
    int userRecived = 0;
    char *userTest = "josue";

    countMessages(listaMensajes, 8, userTest, &userSent, &userRecived);
    printf("Mensajes enviados: %d \n", userSent);
    printf("Mensajes recibidos: %d \n", userRecived);
    // Shows the recived and sended messages 

    
    //Reto 5
    Message message1={"Hola Josue, reunion manana", SENT, "juan", 1, {"juan"}};
    Message message2={"Hola Jared, reunion manana", DELIVERED, "pepe", 2, {"josue", "mario"}};
    Message message3={"Hola amiguito, Que tal?", FAILED, "juan", 3, {"josue", "luis", "pedro"}};
    Message message4={"Hola jochis, reunion manana", SENT, "ashton", 1, {"juan"}};
    Message message5={"Hola ashton, estas reprobado", SENT, "angel", 1, {"josue"}};
    Message message6={"Hola nila", FAILED, "ana", 1, {"josue"}};
    int filteredMessage = 0;
    Message *pointerArrayMessage[]={&message1, &message2, &message3, &message4, &message5, &message6};
    // An example used in the filterMessage function
    Message **filterIsMessageForm = filterMessage(pointerArrayMessage, 6, isMessageFrom, "juan", &filteredMessage);
    printf("\n");
    printf("Mensajes enviados por juan: ");
    for (int i = 0; i < filteredMessage; i++) {
    printf("Texto: %s\nRemitente: %s\n", (*(filterIsMessageForm + i))->text, (*(filterIsMessageForm + i))->sender);
    // Prints the data searched
    }
    free(filterIsMessageForm);

    //Reto 6
    char words[][30] = {"Apostadores", "Funciones", "Estructuras"};
    int count[5], N = 3;

    countVowels(words, N, count);
 
    char vowels[] = {'A', 'E', 'I', 'O', 'U'};
    printf("\nFrecuencia de vocales (A, E, I, O, U):\n");
    for (int k = 0; k < 5; k++) {
        printf("Vocal %c: %d\n", *(vowels + k), *(count + k));
    }// First we use the function countVowels and then print 
    //the the result 
    return 0;
}