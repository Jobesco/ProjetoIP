#include "client.h"
#include "default.h"
#include "comum.h"
#define max_clients 4
#define tamanho_altura 27
#define tamanho_largura 22
#define pedra 0
#define verd_1 1
#define verd_2 2
#define marrom 3 //um muro mais escuro
#define quebra 4 //objetos quebraveis

char posicao[2] = {""};


char matriz[tamanho_altura][tamanho_largura] = {

    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra},
    {pedra,verd_1,verd_2,verd_1,quebra,verd_1,pedra,pedra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,pedra},
    {pedra,verd_2,verd_1,quebra,quebra,verd_2,pedra,pedra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,pedra,verd_1,verd_2,pedra,verd_2,verd_1,pedra},
    {pedra,verd_1,quebra,verd_1,verd_2,quebra,quebra,quebra,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,verd_2,pedra,verd_2,verd_1,quebra,verd_1,verd_2,pedra},
    {pedra,verd_2,verd_1,pedra,quebra,verd_2,quebra,quebra,verd_1,verd_2,verd_1,verd_2,quebra,quebra,quebra,quebra,verd_1,verd_2,quebra,pedra,verd_1,pedra},
    {pedra,quebra,quebra,quebra,pedra,verd_1,quebra,quebra,pedra,pedra,verd_2,verd_1,verd_2,pedra,verd_2,quebra,verd_2,pedra,quebra,quebra,quebra,pedra},
    {pedra,pedra,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,pedra,verd_1,quebra,verd_1,pedra,quebra,verd_2,quebra,pedra},
    {pedra,verd_1,quebra,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,pedra,verd_1,verd_2,quebra,verd_2,pedra,verd_2,pedra,verd_2,pedra,verd_2,pedra},
    {pedra,verd_2,quebra,verd_2,pedra,quebra,verd_1,verd_2,verd_1,verd_2,pedra,verd_2,verd_1,quebra,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,pedra},
    {pedra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,pedra,quebra,verd_2,verd_1,verd_2,quebra,verd_2,pedra},
    {pedra,quebra,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,pedra,verd_2,quebra,quebra,verd_1,verd_2,pedra,verd_2,verd_1,verd_2,pedra,quebra,verd_1,pedra},
    {pedra,pedra,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,quebra,quebra,verd_1,quebra,verd_1,verd_2,quebra,quebra,pedra},
    {pedra,pedra,quebra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,pedra,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,pedra},
    {pedra,quebra,quebra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,quebra,verd_2,quebra,verd_2,verd_1,verd_2,verd_1,quebra,quebra,verd_2,pedra},
    {pedra,verd_2,verd_1,quebra,verd_1,quebra,quebra,quebra,quebra,pedra,pedra,pedra,pedra,quebra,quebra,verd_2,verd_1,verd_2,quebra,quebra,verd_1,pedra},
    {pedra,verd_1,verd_2,quebra,verd_2,pedra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,quebra,verd_2,pedra},
    {pedra,verd_2,quebra,verd_2,verd_1,pedra,pedra,pedra,pedra,verd_2,quebra,verd_2,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,pedra,verd_2,verd_1,pedra},
    {pedra,verd_1,verd_2,quebra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,pedra,verd_2,quebra,quebra,verd_1,verd_2,pedra},
    {pedra,pedra,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,pedra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,pedra},
    {pedra,quebra,quebra,quebra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,quebra,quebra,quebra,verd_1,verd_2,quebra,verd_2,quebra,verd_2,pedra},
    {pedra,pedra,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,pedra,verd_2,quebra,verd_2,quebra,quebra,pedra,pedra,verd_1,quebra,verd_1,quebra,verd_1,pedra},
    {pedra,verd_1,verd_2,verd_1,pedra,verd_1,verd_2,verd_1,quebra,quebra,verd_2,verd_1,pedra,quebra,quebra,verd_1,verd_2,pedra,verd_2,quebra,pedra,pedra},
    {pedra,quebra,quebra,quebra,quebra,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,pedra},
    {pedra,verd_1,verd_2,quebra,pedra,verd_1,quebra,verd_1,quebra,quebra,quebra,quebra,verd_2,verd_1,quebra,verd_1,pedra,verd_1,quebra,pedra,verd_2,pedra},
    {pedra,verd_2,quebra,quebra,quebra,verd_2,quebra,verd_2,verd_1,qubra,quebra,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,pedra,verd_1,verd_2,verd_1,pedra},
    {pedra,verd_1,verd_2,pedra,quebra,verd_1,quebra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,pedra,verd_2,verd_1,verd_2,pedra},
    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra}

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
time_t inicioJogo,atualJogo;

int verifica=0; //tambem é global,referente a funcao printa_matriz

void tratar_intencao(char *controle,int inicio_aux_Bomba[],char *possoBombar);
int verifica_posix(int posix_x, int posix_y,int inicio_aux_Bomba[]);
void printa_matriz(int inicio_aux_Bomba[]);
void contador_Bombas(int inicio_aux_Bomba[],time_t inicio_Bomba[],time_t atual_Bomba[],char *possoBombar);
char controla_raio_explosao(char matou,int inicio_aux_Bomba[]);

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
    int i,j,k; //estou desglobalizando os contadores,apenas para manter um funcionamento mais saudavel das funcoes

    int tamanho_msg_entregue = 0;

    int inicio_aux_Bomba[max_clients] = {0};

    char possoBombar = 0;

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

                inicioJogo = time(NULL); //inicia o timer do jogo
            }

            if(difftime(atualJogo = time(NULL),inicioJogo) >= 240){ //referente ao tempo de cada partida
                desconectado = 0;
            }

           	tamanho_msg_entregue = recvMsgFromServer(&basica,DONT_WAIT); //recebe mensagem

            if(tamanho_msg_entregue != NO_MESSAGE){ // a mensagem foi recebida!
                printa_matriz(inicio_aux_Bomba); //com certeza nao printa a matriz(gerar humor,ele printa sim)
            }

            controle = getch(); //recebe um valor em char que indica a tecla apertada,retorna NO_KEY_PRESSED se ele nao apertou tecla alguma
            tratar_intencao(&controle,inicio_aux_Bomba,&possoBombar); //verifica se ele pode executar o movimento antes mesmo de enviar para o servidor,assim,o servidor executa menos tarefas
            contador_Bombas(inicio_aux_Bomba,inicio_Bomba,atual_Bomba,&possoBombar); //ve se tem bomba

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

int verifica_posix(int posix_x, int posix_y,int inicio_aux_Bomba[]){ //posix diz onde eu quero estar

    int i;
        for(i=0;i<max_clients;i++){
            if(inicio_aux_Bomba[i] != 0){ //se essa bomba estiver rodando
                if(posix_x == basica.jogadores[i].posbomba_x && posix_y == basica.jogadores[i].posbomba_y) //se tiver uma bomba onde ele quer ir,ele nao pode ir.
                    return 0;
            }
        }
        if(matriz[posix_x][posix_y] == 1 || matriz[posix_x][posix_y] == 2){
            return 1;
        }else{
            return 0;
        }
}

void tratar_intencao(char *controle,int inicio_aux_Bomba[],char *possoBombar){

  if(controle[0]>96){
		controle[0] -= 32;
	}

	switch(controle[0]){
		case 'W':
            if(verifica_posix(minha_intencao.pos_x-1, minha_intencao.pos_y,inicio_aux_Bomba) == 1){
                minha_intencao.pos_x -= 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;

        case 'A':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y-1,inicio_aux_Bomba) == 1){
                minha_intencao.pos_y -= 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;

        case 'S':
            if(verifica_posix(minha_intencao.pos_x+1, minha_intencao.pos_y,inicio_aux_Bomba) == 1){
                minha_intencao.pos_x += 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;

        case 'D':
            if(verifica_posix(minha_intencao.pos_x, minha_intencao.pos_y+1,inicio_aux_Bomba) == 1){
                minha_intencao.pos_y += 1;
            }else
            	controle[0] = NO_KEY_PRESSED;
            break;
		case 'K': //caso seja uma bomba,ela vai ter a posicao do jogador
            if(possoBombar[0] == 0){ //se ele n tiver nenhuma bomba no mapa ja
			         minha_intencao.bomba = 1;
               possoBombar[0] = 1;
            }
            break;
	 }
}

void printa_matriz(int inicio_aux_Bomba[]){ //por hora,em printa matriz,ele so atualiza o relogio se o cara se movimentar,cabe a glr de allegro colocar um timer independente e funcional
    system("clear"); //limpa o cmd
    int i,j,k;
    printf("%.0lf\n",240 - difftime(atualJogo,inicioJogo));

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
                else if(matriz[i][j] == quebra)
                    printf("Q");
                else
                    printf("N");
            }
        }printf("\n");
    }
}

void contador_Bombas(int inicio_aux_Bomba[],time_t inicio_Bomba[],time_t atual_Bomba[],char *possoBombar){

    int i;
    for(i=0;i<max_clients;i++){ //contador das bombas,atualmente independe de basica para continuar rodando,mas depende para inicializar(como deve ser)

          if(basica.jogadores[i].bomba == 1){ //se ele tiver recebido uma bomba
              inicio_aux_Bomba[i] = 1; // 0 -- ninguem botou bomba // 1 -- alguem botou bomba
              inicio_Bomba[i] = time(NULL); //inicializa o contador
              basica.jogadores[i].bomba = 0; // impede a reinicializacao do timer da bomba!

          }
          if(inicio_aux_Bomba[i] != 0){ //ou seja,ele tiver um contador iniciado

                atual_Bomba[i] = time(NULL);
                if(difftime(atual_Bomba[i],inicio_Bomba[i]) >= 3){ //a bomba explode!
                    possoBombar[0] = 0; //reseta a condicao de usar bomba,podendo novamente soltar uma bomba
                    char matou;
                    matou = controla_raio_explosao(matou,inicio_aux_Bomba);
                    if(matou == 1){
                        minha_intencao.pos_x = -1;
                        minha_intencao.pos_y = -1;
                        matou = 0;
                        sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente));
                    }
                    inicio_aux_Bomba[i] = 0; //prepara para receber outra bomba
                    printf("BOOM\n");
               }
          }
     }
}

char controla_raio_explosao(char matou,int inicio_aux_Bomba[]){ //
    int k;
        for(k=0;k<max_clients;k++){
            if(minha_intencao.pos_x == basica.jogadores[k].posbomba_x +1 && minha_intencao.pos_y == basica.jogadores[k].posbomba_y){ // jogador abaixo

              matou = 1;

          }else if(minha_intencao.pos_x == basica.jogadores[k].posbomba_x -1 && minha_intencao.pos_y == basica.jogadores[k].posbomba_y){ // jogador acima

              matou = 1;

          }else if(minha_intencao.pos_x == basica.jogadores[k].posbomba_x && minha_intencao.pos_y == basica.jogadores[k].posbomba_y +1){// jogador a esquerda

              matou = 1;

          }else if(minha_intencao.pos_x == basica.jogadores[k].posbomba_x && minha_intencao.pos_y == basica.jogadores[k].posbomba_y -1){ // jogador a direita

              matou = 1;
          }else if(minha_intencao.pos_x == basica.jogadores[k].posbomba_x && minha_intencao.pos_y == basica.jogadores[k].posbomba_y){

              matou = 1;
          }

          if(matriz[basica.jogadores[k].posbomba_x+1][basica.jogadores[k].posbomba_y] == quebra){

              matriz[basica.jogadores[k].posbomba_x+1][basica.jogadores[k].posbomba_y] = verd_1;
              printa_matriz(inicio_aux_Bomba);

          }else if(matriz[basica.jogadores[k].posbomba_x-1][basica.jogadores[k].posbomba_y] == quebra){

              matriz[basica.jogadores[k].posbomba_x-1][basica.jogadores[k].posbomba_y] = verd_1;
              printa_matriz(inicio_aux_Bomba);

          }else if(matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y+1] == quebra){

              matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y+1] = verd_1;
              printa_matriz(inicio_aux_Bomba);

          }else if(matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y-1] == quebra){

              matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y-1] = verd_1;
              printa_matriz(inicio_aux_Bomba);

          }
      }
    return matou; //retorna 0 - nao morreu ou 1 - morreu
}