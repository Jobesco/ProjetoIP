#include "client.h"
#include "default.h"
#include "comum.h"
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

    {pedra,verd_1,verd_1,verd_1,verd_2,verd_1,verd_1,verd_1,verd_1,verd_1,verd_2,pedra},
    {pedra,verd_2,verd_1,verd_1,verd_1,verd_2,verd_1,verd_2,verd_1,verd_1,verd_1,pedra},
    {pedra,verd_1,verd_1,verd_1,verd_2,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,pedra},
    {pedra,verd_1,verd_1,verd_2,verd_1,verd_2,verd_1,verd_1,verd_1,verd_1,verd_1,pedra},
    {pedra,verd_1,verd_2,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,pedra},
    {pedra,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,verd_1,verd_2,verd_1,pedra},

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

  char bomba; //se em algum momento,bomba for 1
  char posbomba_x;
  char posbomba_y;


  
} jogador;

typedef struct mensagem_cliente{
	char pos_x;
  	char pos_y;

  	char bomba; //0 -- nao tentei jogar bomba // 1 -- tentei jogar bomba


} msg_do_cliente;

typedef struct p_broadcast{
  
  jogador jogadores[4]; //eh 2 pq recebe as posicoes(x,y) num plano cartesiano.
  
} msg_todos;


msg_do_cliente minha_intencao;
msg_todos basica;

void tratar_intencao(char *controle);

void main(){

	char *IP = (char*)calloc(30,sizeof(char));

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

    int i,j,k;
    int tamanho_msg_entregue = 0;
    int verifica=0;

    time_t inicioConexao,atualConexao; //para garantir q ele continue conectando


	while(1){
	
	printf("Digite o IP onde deseja se conectar\n");

	scanf(" %s",IP);
	printf("Iremos logar ao IP %s\n", IP);

	inicioConexao = time(NULL);
	atualConexao = time(NULL);
	while(difftime(atualConexao,inicioConexao) < 2){
		atualConexao = time(NULL);
		printf("Por favor aguarde!(%.0lf segundos)\n",difftime(atualConexao,inicioConexao));
		estado = connectToServer(IP);
		if(estado == SERVER_UP)
			break;
	}

	
	scanf(" %s",IP);
	
	printf("Iremos logar com o IP %s\n", IP);
	estado = connectToServer(IP);

	
	break;
	}
	
	while(desconectado != 1){ // verifica se o client ainda joga
    
        
        if(estado == SERVER_UP){ //conexao estabelecida // prosseguir
            if(aux==0){
            	aux++;

            	printf("Conectado!\n");
            	recvMsgFromServer(&minha_intencao,WAIT_FOR_IT);
            	printf("minha posicao eh %d - %d\n", minha_intencao.pos_x,minha_intencao.pos_y);
            	recvMsgFromServer(&basica,WAIT_FOR_IT);

            	for(i=0;i<8;i++){
                    for(j=0;j<12;j++){
                    	verifica = 0;
                    	for(k=0;k<4;k++){
	                        if(basica.jogadores[k].pos_x == i && basica.jogadores[k].pos_y == j){
	                            printf("%d",basica.jogadores[k].id+1); // valor p simbolizar o jogador
	                            verifica++;
	                        }
	                    }
	                    if(verifica==0){ //se ele n printou ngm,ele printa a matriz
	                    	if(matriz[i][j] == 1 || matriz[i][j] == 2)
	                    		printf("0");
	                    	else
	                    		printf("N");
	                    }
                    }printf("\n");     
                }
            }

           	tamanho_msg_entregue = recvMsgFromServer(&basica,DONT_WAIT);

            if(tamanho_msg_entregue != NO_MESSAGE){ // a mensagem foi recebida!
            	system("clear");
                for(i=0;i<8;i++){
                    for(j=0;j<12;j++){
                    	verifica = 0;
                    	for(k=0;k<4;k++){
	                        if(basica.jogadores[k].pos_x == i && basica.jogadores[k].pos_y == j){
	                            printf("%d",basica.jogadores[k].id+1); // valor p simbolizar o jogador
	                            verifica++;
	                        }
	                    }
	                    if(verifica==0){ //se ele n printou ngm,ele printa a matriz
	                    	if(matriz[i][j] == 1 || matriz[i][j] == 2)
	                    		printf("0");
	                    	else
	                    		printf("N");
	                    }
                    }printf("\n");     
                } 
            }

            controle = getch();
	            tratar_intencao(&controle);
	            if(controle == NO_KEY_PRESSED){ //quer dizer q ele executou uma alteracao possivel
	            	retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente)); // manda a intencao
	            }

	            if(retorno == SERVER_DISCONNECTED){
	                desconectado = 1;
	            }
            
            if(controle != 0){
            	if(controle != 'K'){
	            	if(matriz[minha_intencao.pos_x][minha_intencao.pos_y] == 1 || matriz[minha_intencao.pos_x][minha_intencao.pos_y] == 2){
	            		retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente)); // manda a intencao
	            	}
            	}else{
            		retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente));
            		minha_intencao.bomba = 0;
            	}
            

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
            

            printf("Servidor nao encontrado :S\n");

            printf("Servidor nao encontrado!\n");

            break;
            
        }else if(estado == SERVER_FULL){ // cheio
            

            printf("Servidor lotado!\nAguarde proxima partida :/\n");

            printf("Servidor lotado! Aguarde proxima partida\n");

            break;
            
        }else if(estado == SERVER_CLOSED){ // n aceita conexao
            
            printf("Servidor nao aceita novas conexoes! >:U\n");

            printf("Servidor nao aceita novas conexoes!\n");

            break;
            
        }else if(estado == SERVER_TIMEOUT){ // demorou p responder
            

            printf("Voce esperou demais, verifique sua conexao de dados! :P\n");

            printf("Voce esperou demais, verifique sua conexao de dados!\n");

            break;
            
        }
    }
}


int verifica_posix(int posix_x, int posix_y){
    
    if(matriz[posix_x][posix_y] == 1 || matriz[posix_x][posix_y] == 2){
        return 1;
    }else{
        return 0;
    }
    
}

void tratar_intencao(char *controle){
	if(controle[0]>96){
		controle[0] -= 32;
	}
	
	switch(controle[0]){
		case 'W':
            if(verifica_posix(minha_intencao.pos_x-1, minha_intencao.pos_y) == 1){
                minha_intencao.pos_x -= 1;
            }
            break;
            
        case 'A':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y-1) == 1){
                minha_intencao.pos_y -= 1;
            }
            break;
            
        case 'S':
            if(verifica_posix(minha_intencao.pos_x+1, minha_intencao.pos_y) == 1){
                minha_intencao.pos_x += 1;
            }
            break;
            
        case 'D':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y+1) == 1){
                minha_intencao.pos_y += 1;
            }
            break;
		case 'K': //caso seja uma bomba,ela vai ter a posicao do jogador
			minha_intencao.bomba = 1;
			break;

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
