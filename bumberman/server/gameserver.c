#include "server.h"
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

char id[4];

typedef struct mensagem_cliente{
	char pos_x;
	char pos_y;
	char bomba; //0 -- nao tentei jogar bomba // 1 -- tentei jogar bomba


} msg_do_cliente;

typedef struct{
	char id;
	char pos_x;
	char pos_y;

	char bomba; //representa A INTENCAO DE BOMBA,nao a existencia dela em si,a existencia eh tratada individualmente no client
	char posbomba_x;
	char posbomba_y;

} jogador;

typedef struct p_broadcast{

	jogador jogadores[4]; //eh 2 pq recebe as posicoes(x,y) num plano cartesiano.

} msg_todos;

msg_todos basica; //essa eh a mensagem basica para todos a ser enviada.
struct msg_ret_t confirmacao_cliente;
msg_do_cliente recebe_do_cliente[4];

void iniciar_jogo();
void estabelecer_conexao();
void tratar_broadcast(int i); //trata e envia a struct basica

void main(){

	serverInit(max_clients); // inicia_server
    int aux = 0;
    printf("server is running...\n");
  	estabelecer_conexao();
  	printf("conexoes estabelecidas\n");

    iniciar_jogo();

    int i; //contador padrao

    while(1){ //loop referente ao jogo

	    if(aux==0){ //loop que so eh executado uma vez no jogo inteiro(no comeco)
			aux++;
			for(i=0;i<4;i++){ //loop referente a enviar a cada jogador sua atual posicao
				recebe_do_cliente[i].pos_x = basica.jogadores[i].pos_x;
				recebe_do_cliente[i].pos_y = basica.jogadores[i].pos_y;

				printf("passando a posicao %d - %d para jogador %d\n",basica.jogadores[i].pos_x,basica.jogadores[i].pos_y,id[i]);
				sendMsgToClient(&recebe_do_cliente[i],sizeof(msg_do_cliente),id[i]); //a principio,manda a localizacao de cada jogador para que ele saiba quem ele é em sua intencao de movimento.
			}
		broadcast(&basica,sizeof(msg_todos)); //manda para todos a matriz toda
		}

    	for(i=0;i<4;i++){ //loop referente a receber e tratar mensagem
    		confirmacao_cliente =  recvMsgFromClient(&recebe_do_cliente[i],basica.jogadores[i].id,DONT_WAIT); //OBS: confirmacao_cliente -> struct q indica o status da mensagem recebida ~~ recebe_do_cliente -> struct msg_do_cliente com sua intencao de movimento ou bomba.

    		if(confirmacao_cliente.status == MESSAGE_OK){ //se ele recebeu uma mensagem

        		tratar_broadcast(i); //vai tratar e enviar a struct basica de acordo com a mensagem que ele recebeu(zero parametros pois a struct eh global)
        	}
        	if(confirmacao_cliente.status == DISCONNECT_MSG){
        		basica.jogadores[i].pos_x = -1; //se ele estiver na posicao -1,ele nao ira printa-lo
        		basica.jogadores[i].pos_y = -1;
        	}
        }
    }
}

void estabelecer_conexao(){
    int n_conexoes = 0;
    int id_temp;

    while(n_conexoes < max_clients){
        id_temp = acceptConnection();

        if(id_temp != NO_CONNECTION){
        	if(n_conexoes < max_clients){ // if redundante p evitar resto do while
                id[n_conexoes] = id_temp;
                n_conexoes++;
            }else{
            	rejectConnection();
        	}
      	}//conexoes estabelecidas
    }
}

void iniciar_jogo(){

    basica.jogadores[0].id = 0;
    basica.jogadores[0].pos_x = 1; //linha
    basica.jogadores[0].pos_y = 1; //coluna

    basica.jogadores[1].id = 1;
    basica.jogadores[1].pos_x = 6;
    basica.jogadores[1].pos_y = 1;

    basica.jogadores[2].id = 2;
    basica.jogadores[2].pos_x = 1;
    basica.jogadores[2].pos_y = 10;

    basica.jogadores[3].id = 3;
    basica.jogadores[3].pos_x = 6;
    basica.jogadores[3].pos_y = 10;
}

void tratar_broadcast(int i){
    if(recebe_do_cliente[i].bomba == 1){ //ou o server recebe uma bomba,ou uma movimentacao
        basica.jogadores[i].bomba = 1; //atribui a intencao de bomba e sua posicao,em baixo do jogador
        basica.jogadores[i].posbomba_x = basica.jogadores[i].pos_x;
        basica.jogadores[i].posbomba_y = basica.jogadores[i].pos_y;

        broadcast(&basica,sizeof(msg_todos));
        basica.jogadores[i].bomba = 0; //nao existe mais intencao de bomba
    }else{
        basica.jogadores[i].pos_x = recebe_do_cliente[i].pos_x; //altera a posicao dele em broadcast(como ele printa a matriz e depois o jogador de acordo com a localizacao,eu nao preciso alterar nada na matriz,pq nada eh alterado nela)
        basica.jogadores[i].pos_y = recebe_do_cliente[i].pos_y;

        broadcast(&basica,sizeof(msg_todos));
    }
}
