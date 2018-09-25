#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>
#include <errno.h>
#include <memory.h>

#include "escutar.h"
#include "escrever.h"
//******** Header para Sockets************************************************************
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
//****************************************************************************************
#define NUM_THREADS 2
typedef struct {
        int vizinhoA;
        int vizinhoB;
        int porta;
		int function;
        char cliente;
    }Tcliente;


//*******CRIAR THREADS **************************************************

void * function (void *arg){
	Tcliente *Cliente = (Tcliente *)(arg);	

    switch(Cliente->cliente){
        case 'A':
            Cliente->porta = 5001;
            Cliente->vizinhoA = Cliente->porta + 1;
            Cliente->vizinhoB = Cliente->porta + 2;
            
        break;

        case 'B':
            Cliente->porta = 5002;
            Cliente->vizinhoA = Cliente->porta + 1;
            Cliente->vizinhoB = Cliente->porta + 2;
                    
        break;

        case 'C':
            Cliente->porta = 5003;
            Cliente->vizinhoA = Cliente->porta + 1;
            Cliente->vizinhoB = Cliente->porta + 2;
            
        break;

        case 'D':
            Cliente->porta = 5004;
            Cliente->vizinhoA = Cliente->porta + 1;
            Cliente->vizinhoB = Cliente->porta - 3;
            
        break;

        case 'E':
            Cliente->porta = 5005;
            Cliente->vizinhoA = Cliente->porta - 4;
            Cliente->vizinhoB = Cliente->porta - 3;
            
        break;

        default:
            printf("\n Operação Invalida \n");
            exit(0);
        break;    
    }

	if(Cliente->function == 1){
	    escutar(Cliente->porta);
        
	}else{
        escrever(Cliente->vizinhoA, Cliente->vizinhoB, Cliente->cliente);
	}
}

//*******************************************************************************************************

  /* É igual a  int main(int argc, char *argv[])  */
int main(int qntd_argumentos , char *argumentos_valores[])
{
    Tcliente Cliente;
    Cliente.cliente  = *argumentos_valores[1]; 

	pthread_t threads[NUM_THREADS];

    while(1){
        int i=1;  

        system("clear");
        
        for(i = 1; i <= NUM_THREADS; i++){
            Cliente.function=i;
            //printf("\n função: %d", Cliente.function);
            pthread_create(&threads[i], NULL, function, (void *) (&Cliente));		
            sleep(1);
            
        }

        i=1;
        
        for(i=1; i<= NUM_THREADS; i++){		
            pthread_join(threads[i], NULL);
        }
    }
	
} 