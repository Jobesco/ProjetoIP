#include "client.h"
#include "default.h"
#define max_clients 4
#define tamanho_altura 8
#define tamanho_largura 12
#define pedra 0
#define verd_1 1
#define verd_2 2
#define marrom 3
#define quebra 4
#define player 5

char posicao[2] = {""};


char matriz[tamanho_altura][tamanho_largura] = {
    
    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra},
    {pedra,verd_1,marrom,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,verd_2,pedra},
    {pedra,verd_2,verd_1,quebra,marrom,verd_2,quebra,verd_2,quebra,quebra,verd_1,pedra},
    {pedra,quebra,quebra,marrom,verd_2,marrom,quebra,verd_1,marrom,quebra,quebra,pedra},
    {pedra,quebra,quebra,verd_2,verd_1,verd_2,quebra,quebra,verd_1,marrom,quebra,pedra},
    {pedra,verd_1,verd_2,quebra,quebra,marrom,marrom,verd_1,quebra,verd_1,quebra,pedra},
    {pedra,verd_1,quebra,quebra,quebra,quebra,quebra,quebra,quebra,verd_2,verd_1,pedra},
    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra}
    
};

typedef struct{
  
  char id;
  char pos_x;
  char pos_y;
  
} jogador;

typedef struct mensagem_cliente{
	char pos_x;
  	char pos_y;
} msg_do_cliente;

typedef struct p_broadcast{
  
  jogador jogadores[4]; //eh 2 pq recebe as posicoes(x,y) num plano cartesiano.
  
} msg_todos;

msg_do_cliente minhapos;
msg_todos basica;

void tratar_intencao(char controle);

void main(){

	char *IP;
	
	IP = (char*)calloc(50,sizeof(char));
	if(IP==NULL){
		printf("ERRO NA ALOCACAO\n");
		exit(1);
	}
	
	int estado;
	int desconectado = 0;
	int aux = 0;
	char controle;
    int retorno = 0;

	while(1){
	
	printf("Digite o IP onde deseja se conectar\n");
	
	scanf(" %s",IP);
	
	printf("Iremos logar com o IP %s\n", IP);
	estado = connectToServer(IP);
	
	break;
	}
	
	while(desconectado != 1){ // verifica se o client ainda joga
    
        
        if(estado == SERVER_UP){ //conexao estabelecida // prosseguir
            if(aux==0){
            	aux++;
            	recvMsgFromServer(&minhapos,WAIT_FOR_IT);
            }
            
            recvMsgFromServer(&basica,DONT_WAIT);
            
            controle = getch();
            tratar_intencao(controle);
            
            if(matriz[minhapos.pos_x][minhapos.pos_y] == 1 || matriz[minhapos.pos_x][minhapos.pos_y] == 2){
            
            retorno = sendMsgToServer(&minhapos,sizeof(msg_do_cliente)); // manda a intencao
            }
            
            if(retorno == SERVER_DISCONNECTED){
            	desconectado = 1;
            }
        
        }else if(estado == SERVER_DOWN){ //nao achou o server
            
            printf("Servidor nao encontrado!\n");
            break;
            
        }else if(estado == SERVER_FULL){ // cheio
            
            printf("Servidor lotado! Aguarde proxima partida\n");
            break;
            
        }else if(estado == SERVER_CLOSED){ // n aceita conexao
            
            printf("Servidor nao aceita novas conexoes!\n");
            break;
            
        }else if(estado == SERVER_TIMEOUT){ // demorou p responder
            
            printf("Voce esperou demais, verifique sua conexao de dados!\n");
            break;
            
        }
    }
}

void tratar_intencao(char controle){
	if(controle>96){
		controle -= 32;
	}
	
	switch(controle){
		case 'W':
			minhapos.pos_x -= 1;
			break;
		case 'A':
			minhapos.pos_y -= 1;
			break;
		case 'S':
			minhapos.pos_x += 1;
			break;
		case 'D':
			minhapos.pos_y += 1;
			break;
	
	}
}
