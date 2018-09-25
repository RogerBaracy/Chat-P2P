//utilize no terminal o mensagem "nc receberhost "PORTA" " para ver e escrever a mensagem
//******** Header para Sockets************************************************************
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
//****************************************************************************************
#define LEN 255

struct sockaddr_in receber;

void escutar( int porta)
{  
	
	printf("\n escutar porta %d", porta);
		int infosocket=0; //descritor socket
		int cliente=0;
		//int PORTA = porta;
		int len = sizeof(receber);
		char mensagem[LEN];
		unsigned short int contador=0;	
		unsigned char BytesLidos=0;    
		infosocket = socket(AF_INET, SOCK_STREAM, 0);//Criando o Socket -> utilize no terminal o mensagem "man socket" para mais informações
							
	//****************** DEFININDO A STRUCT sockaddr_in receber *******************************************
		receber.sin_family    =AF_INET; 	 //Tipo de protocolo a ser usado     
		receber.sin_port     =htons(porta);// Porta a ser usada
		//receber.sin_addr.s_addr = inet_addr("***.***.***.***.***"); // Endereço IP do Ciente
		receber.sin_addr.s_addr = INADDR_ANY;// Utiliza o ip do sistema
		memset(receber.sin_zero, 0x0, 8);
	//***************************************************************************************************
		int tentativas =0;
		do{
			perror("socket ");
			sleep(3);

			tentativas++;
			if(tentativas>=3){
				exit;
			}	
		}while(infosocket== -1);
		
		//printf("\n Socket Escutar ! \n");
		tentativas =0;
		do{
			perror("bind");

			tentativas++;
			if(tentativas>=3){
				exit;
			}	
			
		}while(bind(infosocket,(struct sockaddr*)&receber, sizeof(receber))== -1);

		listen(infosocket,1);
		
		do{
			perror("bind ");
			tentativas++;
			if(tentativas>=3){
				exit;
			}	
			
		}while ((cliente = accept(infosocket, (struct sockaddr*)&receber, &len)) == -1);	
	//*****************************************************************************************************
		memset(&mensagem, 0x00, sizeof(mensagem));
		printf("\n Aguardando resposta do cliente ...\n");	
		while(1){	
					
			if((BytesLidos = recv(cliente,mensagem,LEN,0))>0)
			{					
				mensagem[BytesLidos] ='\0';	
				printf("%s \n",mensagem);
			
				BytesLidos=0;
				memset(&mensagem, 0x00, sizeof(mensagem));
				
			}
		}
	
}
