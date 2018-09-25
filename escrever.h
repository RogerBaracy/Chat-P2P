
//******** Header para Sockets************************************************************
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#define LEN 255
struct sockaddr_in socket_vizinhoA;
struct sockaddr_in socket_vizinhoB;

//*****************************************************************************************
void escrever(int vizinhoA, int vizinhoB, char cliente)
{
	printf("\n Cliente %c", cliente);
	printf("\n enviar para vizinho A  %d", vizinhoA);
	printf("\n enviar para vizinho B  %d", vizinhoB);	
	
	int infosocket_vizinhoA=0; //descritor socket
	int infosocket_vizinhoB=0; //descritor socket
	int servidor=0;
	int lenA = sizeof(socket_vizinhoA);
	int lenB = sizeof(socket_vizinhoB);
	char mensagem[LEN];

//***************************************************************************************************
	infosocket_vizinhoA = socket(AF_INET, SOCK_STREAM, 0);//Criando o Socket para vizinhoA
	infosocket_vizinhoB = socket(AF_INET, SOCK_STREAM, 0);//Criando o Socket para vizinhoB						
//****************** DEFININDO A STRUCT sockaddr_in servidor *******************************************
	socket_vizinhoA.sin_family    =AF_INET; 	 //Tipo de protocolo a ser usado 
	socket_vizinhoB.sin_family    =AF_INET; 	 //Tipo de protocolo a ser usado  

	socket_vizinhoA.sin_port     =htons(vizinhoA);// Porta a ser usada
	socket_vizinhoB.sin_port     =htons(vizinhoB);// Porta a ser usada
	//vizinhoA.sin_addr.s_addr = inet_addr("192.168.1.9"); // Endereço IP do Ciente

	socket_vizinhoA.sin_addr.s_addr = INADDR_ANY;// Utiliza o ip do sistema
	socket_vizinhoB.sin_addr.s_addr = INADDR_ANY;// Utiliza o ip do sistema

	memset(socket_vizinhoA.sin_zero, 0x0, 8);
	memset(socket_vizinhoB.sin_zero, 0x0, 8);
//***************************************************************************************************
	int tentativas =0;

	do{
		perror("socket ");

	}while((infosocket_vizinhoA== -1) && (infosocket_vizinhoB== -1));		

	tentativas =0;

	do{
		perror("connect ");
		tentativas++;
		if(tentativas>=3){
			exit;
		}
	}while(connect(infosocket_vizinhoA, (struct sockaddr*)&socket_vizinhoA, lenA) != -1);

	tentativas =0;

	do{
		perror("connect ");
		tentativas++;
		if(tentativas>=3){
			exit;
		}
	}while(connect(infosocket_vizinhoB, (struct sockaddr*)&socket_vizinhoB, lenB) != -1);	
//*********************************************************************************************************

	while(1){	
		printf("\n Digite a mensagem : ");
		memset(&mensagem, 0x0, sizeof(mensagem));
		fgets(mensagem,LEN,stdin);			

		send(infosocket_vizinhoA,mensagem, LEN, 0);
		send(infosocket_vizinhoB,mensagem, LEN, 0);

	}	

}

