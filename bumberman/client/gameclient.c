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

int i,j,k; //contadores globais!!!
int verifica=0; //tambem é global,referente a funcao printa_matriz

void tratar_intencao(char *controle);
int verifica_posix(int posix_x, int posix_y);
void printa_matriz(int inicio_aux_Bomba[]);
void contador_Bombas(int inicio_aux_Bomba[],time_t inicio_Bomba[],time_t atual_Bomba[]);

void main(){

	char *IP;

	IP = (char *)calloc(50,sizeof(char));

	if(IP==NULL){
		printf("ERRO NA ALOCACAO\n");
		exit(1);
	}

	int estado;
	int desconectado = 0;
	int aux = 0,auxBomba = 0;
	char controle;
    int retorno = 0;

    int tamanho_msg_entregue = 0;

    int inicio_aux_Bomba[max_clients] = {0};

    time_t inicioConexao,atualConexao; //para garantir q ele continue conectando
    time_t inicio_Bomba[max_clients],atual_Bomba[max_clients];

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

	while(desconectado != 1){ // verifica se o client ainda joga

        if(estado == SERVER_UP){ //conexao estabelecida // prosseguir
            if(aux==0){
            	aux++;
            	printf("Conectado!\n");
            	recvMsgFromServer(&minha_intencao,WAIT_FOR_IT); //vai receber sua posicao e armazenar em minha_intencao(que a partir da posicao dele,sera modificada conforme ele se movimenta)

            	printf("minha posicao eh %d - %d\n", minha_intencao.pos_x,minha_intencao.pos_y);
            	recvMsgFromServer(&basica,WAIT_FOR_IT);

            	printa_matriz(inicio_aux_Bomba);
            }

           	tamanho_msg_entregue = recvMsgFromServer(&basica,DONT_WAIT); //recebe mensagem

            if(tamanho_msg_entregue != NO_MESSAGE){ // a mensagem foi recebida!
            	system("clear"); //limpa o cmd
                printa_matriz(inicio_aux_Bomba); //com certeza nao printa a matriz(gerar humor,ele printa sim)
            }

            contador_Bombas(inicio_aux_Bomba,inicio_Bomba,atual_Bomba); //ve se tem bomba

            controle = getch(); //recebe um valor em char que indica a tecla apertada,retorna NO_KEY_PRESSED se ele nao apertou tecla alguma
            tratar_intencao(&controle); //verifica se ele pode executar o movimento antes mesmo de enviar para o servidor,assim,o servidor executa menos tarefas

            if(controle != NO_KEY_PRESSED){ //se ele apertou uma tecla
            	if(controle != 'K'){ //se ele nao apertou K,ele tentou se mover(verificado antes por tratar_intencao)
	            	retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente)); // manda a intencao de bomba
            	}else{
            		retorno = sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente)); //manda a intencao de movimento,mas a struct ja contem bomba e movimento,entao nao faz diferenca
            		minha_intencao.bomba = 0; //reseta,pois ele nao tem mais INTENCAO de enviar uma bomba p server dar broadcast
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

void printa_matriz(int inicio_aux_Bomba[]){
    for(i=0;i<tamanho_altura;i++){
        for(j=0;j<tamanho_largura;j++){
            verifica = 0;
            for(k=0;k<4;k++){
                if(basica.jogadores[k].pos_x == i && basica.jogadores[k].pos_y == j){
                    printf("%d",basica.jogadores[k].id+1); // valor p simbolizar o jogador
                    verifica++;
                }else if(inicio_aux_Bomba[k] == 1 && basica.jogadores[k].posbomba_x == i && basica.jogadores[k].posbomba_y == j){ //caso tenha uma bomba no mapa
                    printf("b"); //printa a bomba(mas o jogador vai em cima,caso esteja no mesmo bloco,por hora)
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

void contador_Bombas(int inicio_aux_Bomba[],time_t inicio_Bomba[],time_t atual_Bomba[]){

    for(i=0;i<max_clients;i++){ //contador das bombas,atualmente independe de basica para continuar rodando,mas depende para inicializar(como deve ser)

          if(basica.jogadores[i].bomba == 1){ //se ele tiver recebido uma bomba
              inicio_aux_Bomba[i] = 1; // 0 -- ninguem botou bomba // 1 -- alguem botou bomba
              inicio_Bomba[i] = time(NULL); //inicializa o contador
          }
          if(inicio_aux_Bomba[i] != 0){ //ou seja,ele tiver um contador iniciado
              atual_Bomba[i] = time(NULL);
              if(difftime(atual_Bomba[i],inicio_Bomba[i]) >= 3){ //a bomba explode!
                  inicio_aux_Bomba[i] = 0;
                  printf("BOOM\n");
              }
         }
    }
}
