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
int verifica_posix(int posix_x, int posix_y);

int jogador_perto(int posBLocal_x, int posBLocal_y){

    if(matriz[posBLocal_x][posBLocal_y] == ){ // verifica se na posix da bomba tem um jogador


    }
    if(matriz[posBLocal_x][posBLocal_y+1] == 0 || matriz[posBLocal_x][posBLocal_y+1] == 1 || matriz[posBLocal_x][posBLocal_y+1] == 2 || matriz[posBLocal_x][posBLocal_y+1] == 3){ // tem alguem por perto

        switch(matriz[posBLocal_x][posBLocal_y+1]){ // continuar !!!!!!!!!!!!!

            case 0:



        }

    }

}

void main(){

	char *IP;
	
	IP = (char*)calloc(50,sizeof(char));

	if(IP==NULL){
		printf("ERRO NA ALOCACAO\n");
		exit(1);
	}
	
	int estado;
	int desconectado = 0;
	int aux = 0,auxBomba = 0;
	char controle;
    int retorno = 0;

    int i,j,k;
    int tamanho_msg_entregue = 0;
    int verifica=0;
    int posBLocal_x,posBLocal_y;

    time_t inicioConexao,atualConexao; //para garantir q ele continue conectando
    time_t current_time;
    time_t previous_time;
    previous_time = time(NULL);
    current_time = time(NULL);


	while(1){
	
		printf("Digite o IP onde deseja se conectar\n");

		scanf(" %s",IP);
		printf("Iremos logar ao IP %s\n", IP);

		inicioConexao = time(NULL);
		atualConexao = time(NULL);
		printf("Por favor aguarde!\n");

		while(difftime(atualConexao,inicioConexao) < 2){

			atualConexao = time(NULL);
			estado = connectToServer(IP);
			if(estado == SERVER_UP)
				break;
		}
		break;
	}
	int existe_bomba = 0;

	while(desconectado != 1){ // verifica se o client ainda joga

        if(existe_bomba == 1){ // o user acabou de colocar uma bomba e o cronometro inicia

            current_time = time(NULL); // a cada instante , recebe o tempo do relogio

            if(difftime(current_time,previous_time)>=4){ // a bomba explode 

                matriz[posBLocal_x][posBLocal_y] = 0; // volta ao normal

                // verifica se existe alguem por perto !!!


            }
        } 

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

	                        if(basica.jogadores[k].pos_x == i && basica.jogadores[k].pos_y == j && (basica.jogadores[k].posbomba_x != i && basica.jogadores[k].posbomba_y != j)){
	                            printf("%d",basica.jogadores[k].id+1); // valor p simbolizar o jogador
	                            verifica++;
	                        }else if(basica.jogadores[k].bomba == 1 && basica.jogadores[k].posbomba_x == i && basica.jogadores[k].posbomba_y == j){ //caso tenha uma bomba no mapa
	                        	printf("b%d",basica.jogadores[k].id+1); //printa a bomba(mas o jogador vai em cima,caso esteja no mesmo bloco,por hora)

	                        	verifica++;
                                matriz[i][j] = 'b'; // coloca uma bomba na matriz
                                existe_bomba = 1; // comeca a contar o tempo
                                // inicia o timer da bomba
                                previous_time = time(NULL);
                                posBLocal_x = i; // recebe o x e armazena
                                posBLocal_y = j;

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

            for(i=0;i<4;i++){ //loop referente a tratar a explosao

            	if(basica.jogadores[k].bomba == 1){ //se existir uma bomba

            		if(auxBomba == 0){

            			inicioConexao = time(NULL);
            			auxBomba++;

            		}else{
            			atualConexao = time(NULL);
            			if(difftime(atualConexao,inicioConexao) >= 4){ //se a bomba estiver na hr de explodir (tempo sujeito a mudancas)
            				printf("BOOM\n");

            				auxBomba = 0;
            			}
            		}

            	}
            }

            controle = getch();
	        tratar_intencao(&controle);
            
            if(controle != NO_KEY_PRESSED){ //se ele apertou uma tecla

            	if(controle != 'K'){

	            	retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente)); // manda a intencao

            	}else{

                    if(matriz[jogador.pos_x][jogador.posix_y] != 'b'){ // nao existe uma bomba na posicao atual

                		retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente));
                		minha_intencao.bomba = 0;
                        time_t tempo_atual = time(NULL);
                        //conta_tempo(tempo_atual,4);

                    }
            	}

            }

            if(retorno == SERVER_DISCONNECTED){
	        	desconectado = 1;
	        }
        
        }else if(estado == SERVER_DOWN){ //nao achou o server
            
            printf("Servidor nao encontrado :S\n");
            break;
        }else if(estado == SERVER_FULL){ // cheio
            
            printf("Servidor lotado!\nAguarde proxima partida :/\n");
            break;
        }else if(estado == SERVER_CLOSED){ // n aceita conexao
            
            printf("Servidor nao aceita novas conexoes! >:U\n");
            break;
        }else if(estado == SERVER_TIMEOUT){ // demorou p responder
            
            printf("Voce esperou demais, verifique sua conexao de dados! :P\n");
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
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;
            
        case 'A':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y-1) == 1){
                minha_intencao.pos_y -= 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;
            
        case 'S':
            if(verifica_posix(minha_intencao.pos_x+1, minha_intencao.pos_y) == 1){
                minha_intencao.pos_x += 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;
            
        case 'D':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y+1) == 1){
                minha_intencao.pos_y += 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;
		case 'K': //caso seja uma bomba,ela vai ter a posicao do jogador
			minha_intencao.bomba = 1;
			break;
	}
}