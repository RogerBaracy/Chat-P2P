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
            Cliente->vizinhoA = 5002;
            Cliente->vizinhoB = 5003;
            
        break;

        case 'B':
            Cliente->porta = 5002;
            Cliente->vizinhoA = 5003;
            Cliente->vizinhoB = 5004;
                    
        break;

        case 'C':
            Cliente->porta = 5003;
            Cliente->vizinhoA = 5004;
            Cliente->vizinhoB = 5005;
            
        break;

        case 'D':
            Cliente->porta = 5004;
            Cliente->vizinhoA = 5005;
            Cliente->vizinhoB = 5001;
            
        break;

        case 'E':
            Cliente->porta = 5005;
            Cliente->vizinhoA = 5001;
            Cliente->vizinhoB = 5002;
            
        break;

        default:
            printf("\n Operação Invalida \n");
            exit(0);
        break;    
    }

	if(Cliente->function == 0){
	    escutar(Cliente->porta, Cliente->vizinhoA, Cliente->vizinhoB);
        
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
  
        int i=0;  

        system("clear");
        
        for(i = 0; i < NUM_THREADS; i++){
            Cliente.function=i;
            //printf("\n função: %d", Cliente.function);
            pthread_create(&threads[i], NULL, function, (void *) (&Cliente));		
            sleep(1);
        }

        i=0;
        
        for(i=0; i<= NUM_THREADS; i++){		
            pthread_join(threads[i], NULL);
        }
} 
