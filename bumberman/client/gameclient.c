#include "client.h"
#include "default.h"
#include "comum.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define max_clients 4
#define tamanho_altura 17
#define tamanho_largura 27
#define Ltela 999 // Definir tamanho padrao da largura
#define Atela 629 // Definir tamanho padrao da altura
#define pedra 0
#define verd_1 1
#define verd_2 2
#define marrom 3 //um muro mais escuro
#define quebra 4 //objetos quebraveis

char posicao[2] = {""};

typedef struct historico{

  int n_bombas_soltadas;
  int n_partidas_jogadas;
  int n_partidas_ganhas;
  double win_ratio; // partidas ganhas / partidas jogadas

}historico;

char matriz[tamanho_altura][tamanho_largura] = {

    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra},
    {pedra,verd_1,verd_2,verd_1,quebra,verd_1,pedra,pedra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,pedra,verd_1,verd_2,verd_1,pedra},
    {pedra,verd_2,verd_1,quebra,quebra,verd_2,pedra,pedra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,pedra,verd_1,verd_2,pedra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,pedra},
    {pedra,verd_1,quebra,verd_1,verd_2,quebra,quebra,quebra,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,verd_2,pedra,verd_2,verd_1,quebra,verd_1,verd_2,quebra,quebra,quebra,verd_2,verd_1,pedra},
    {pedra,verd_2,verd_1,pedra,quebra,verd_2,quebra,quebra,verd_1,verd_2,verd_1,verd_2,quebra,quebra,quebra,quebra,verd_1,verd_2,quebra,pedra,verd_1,verd_2,verd_1,pedra,verd_1,verd_2,pedra},
    {pedra,quebra,quebra,quebra,pedra,verd_1,quebra,quebra,pedra,pedra,verd_2,verd_1,verd_2,pedra,verd_2,quebra,verd_2,pedra,quebra,quebra,quebra,verd_1,quebra,verd_1,quebra,quebra,pedra},
    {pedra,pedra,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,pedra,verd_1,quebra,verd_1,pedra,quebra,verd_2,quebra,quebra,quebra,quebra,pedra,quebra,pedra},
    {pedra,verd_1,quebra,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,pedra,verd_1,quebra,quebra,verd_2,quebra,verd_2,pedra,verd_2,pedra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,pedra},
    {pedra,verd_2,quebra,verd_2,pedra,quebra,verd_1,verd_2,verd_1,verd_2,pedra,verd_2,verd_1,quebra,verd_1,quebra,verd_1,verd_2,quebra,verd_2,quebra,quebra,verd_1,quebra,pedra,quebra,pedra},
    {pedra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,pedra,quebra,verd_2,verd_1,verd_2,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,pedra},
    {pedra,quebra,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,pedra,verd_2,quebra,quebra,verd_1,verd_2,pedra,verd_2,verd_1,verd_2,pedra,quebra,verd_1,verd_2,pedra,verd_2,verd_1,pedra,pedra},
    {pedra,pedra,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,quebra,quebra,verd_1,quebra,verd_1,verd_2,quebra,quebra,verd_1,quebra,verd_1,quebra,verd_1,pedra},
    {pedra,pedra,quebra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,pedra,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,quebra,verd_1,quebra,verd_1,quebra,pedra},
    {pedra,quebra,quebra,quebra,verd_2,verd_1,verd_2,verd_1,verd_2,quebra,verd_2,quebra,verd_2,quebra,verd_2,verd_1,verd_2,verd_1,quebra,quebra,verd_2,pedra,verd_2,quebra,pedra,verd_1,pedra},
    {pedra,verd_2,verd_1,quebra,verd_1,quebra,quebra,quebra,quebra,pedra,pedra,pedra,pedra,quebra,quebra,verd_2,verd_1,verd_2,pedra,quebra,verd_1,quebra,pedra,quebra,verd_1,verd_2,pedra},
    {pedra,verd_1,verd_2,quebra,verd_2,pedra,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,verd_2,verd_1,quebra,verd_1,verd_2,verd_1,quebra,quebra,verd_2,verd_1,pedra,verd_1,verd_2,verd_1,pedra},
    {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra}

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

  jogador jogadores[4];

} msg_todos;

typedef struct mov_anterior{
    char id;
    char pos_ant_x;
    char pos_ant_y;

    /*
    hora de entender as logicas
    digamos que temos uma matriz de 3,e temos um jogador no meio,ou seja,(1,1) [x,y]
    se ele apertou W,cima: (0,1) [x-1,y]
    se ele apertou A,esquerda: (1,0) [x,y-1]
    se ele apertou S,baixo: (2,1) [x+1,y]
    se ele apertou D,direita: (1,2) [x,y+1]
    */

} mov_anterior;

//variaveis globais usadas
mov_anterior antiga_pos[4];
char quemGanhou = 0;
msg_do_cliente minha_intencao;
msg_todos basica;
time_t inicioJogo,atualJogo;
int verifica = 0; //tambem é global,referente a funcao printa_matriz
historico hist; // declara struct do tipo historico
historico para_ler;
int n_bombas = 0;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *marro = NULL;
ALLEGRO_BITMAP *pedr = NULL;
ALLEGRO_BITMAP *quebr = NULL;
ALLEGRO_BITMAP *verde_1 = NULL;
ALLEGRO_BITMAP *verde_2 = NULL;
ALLEGRO_BITMAP *bomb = NULL;
ALLEGRO_BITMAP *sprites = NULL;
ALLEGRO_BITMAP *explosion = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
//ALLEGRO_TIMEOUT timeout;
// ALLEGRO_AUDIO_STREAM *musica = NULL;
// ALLEGRO_SAMPLE *sample = NULL;
bool sair = false;
char anterior[4] = {'S','S','S','S'};
int tmp_bomb = 0; // variavel pra printar qdo a bomba explodir
//fim das variaveis globais


//funcoes usadas.
void atrib_jog_ant();
void atribui_pos_ant();
void tratar_intencao(char *controle,int inicio_aux_Bomba[],char *possoBombar);
int verifica_posix(int posix_x, int posix_y,int inicio_aux_Bomba[]);
void printa_matriz(int inicio_aux_Bomba[]);
void contador_Bombas(int inicio_aux_Bomba[],time_t inicio_Bomba[],time_t atual_Bomba[],char *possoBombar);
char controla_raio_explosao(char matou,int inicio_aux_Bomba[]);
int verifica_fim_jogo();
void apresentar_historico();
void salvar_historico();
void alterar_historico(char ganhou);
bool inicializar();
void destroy ();
//fim das funcoes usadas


void main(){

	char *IP;

	IP = (char *)calloc(50,sizeof(char));

	if(IP==NULL){
		printf("ERRO NA ALOCACAO\n");
		exit(1);
	}

	int estado;
	int desconectado;
	int aux = 0;
	char controle;
    int retorno = 0;
    int i,j,k; //estou desglobalizando os contadores,apenas para manter um funcionamento mais saudavel das funcoes
    int tamanho_msg_entregue = 0;
    int inicio_aux_Bomba[max_clients] = {0};
    char possoBombar = 0;
    time_t inicioConexao,atualConexao; //para garantir q ele continue conectando
    time_t inicio_Bomba[max_clients],atual_Bomba[max_clients];
    int respostaJogo = 1;

    while(respostaJogo == 1){
    	while(1){

    		printf("Digite o IP onde deseja se conectar\n");

    		scanf(" %s",IP);
    		printf("Iremos logar ao IP %s\n", IP);

    		inicioConexao = time(NULL);
    		atualConexao = time(NULL);
    		printf("Por favor aguarde!\n");

    		while(difftime(atualConexao,inicioConexao) < 3){
    			atualConexao = time(NULL);
    			estado = connectToServer(IP);
    			if(estado == SERVER_UP)
    				break;
    		}
            n_bombas = 0;
            desconectado = 0;
            aux = 0;
            tamanho_msg_entregue = 0;
            possoBombar = 0;
            quemGanhou = 0;
            verifica = 0;
            break;
        }
        if (!inicializar()) {
          puts("Falha ao carregar bibliotecas!!!");
          return 1;
        }
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_text(fonte, al_map_rgb(255, 255, 255), Ltela / 2, 200, ALLEGRO_ALIGN_CENTRE, "Ei, ainda falta alguns jogadores!!!");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), Ltela / 2, 250, ALLEGRO_ALIGN_CENTRE, "Enquanto espera... ");
        al_draw_text(fonte, al_map_rgb(255, 255, 255), Ltela / 2, 300, ALLEGRO_ALIGN_CENTRE, "Observe este lindo background... =D");
        al_flip_display();
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

                atribui_pos_ant(); //duvido vc adivinhar O QUE ESSA FUNCAO FAZ HEHE

                //detalhe: ele recebe a pos do while anterior,depois recebe uma nova,tcharam
               	tamanho_msg_entregue = recvMsgFromServer(&basica,DONT_WAIT); //recebe mensagem
                atrib_jog_ant();
                if(tamanho_msg_entregue != NO_MESSAGE){ // a mensagem foi recebida!
                    printa_matriz(inicio_aux_Bomba); //com certeza nao printa a matriz(gerar humor,ele printa sim)
                }
                controle = NO_KEY_PRESSED;
                while (!al_is_event_queue_empty(fila_eventos)) {
                  ALLEGRO_EVENT evento;
                  al_get_next_event(fila_eventos, &evento);
                  //al_wait_for_event(fila_eventos, &evento);
                  //al_wait_for_event_until(fila_eventos, &evento, &timeout);
                  if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                      switch(evento.keyboard.keycode) {
                      case ALLEGRO_KEY_W : controle = 'W';
                          break;
                      case ALLEGRO_KEY_S: controle = 'S';
                          break;
                      case ALLEGRO_KEY_A: controle = 'A';
                          break;
                      case ALLEGRO_KEY_D: controle = 'D';
                          break;
                      case ALLEGRO_KEY_K: controle = 'K';
                          break;
                      default : controle = NO_KEY_PRESSED;
                      }
                  }
                  else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                      destroy();
                      sair = true;
                      return 0;
                  }
                }
                //al_wait_for_event(fila_eventos, &evento);
                //controle = getch(); //recebe um valor em char que indica a tecla apertada,retorna NO_KEY_PRESSED se ele nao apertou tecla alguma
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
              if(verifica_fim_jogo() == 1){
                  desconectado = 1;
                  printf("Deseja Jogar novamente?\n0 - Nao\n1 - Sim\n");
                  scanf(" %d",&respostaJogo);
                  if(respostaJogo == 1)
                    printf("Infelizmente a biblioteca q usamos nao permite que ele reconecte sem recompilar,hehe\nPor favor,reinicie o cliente para poder jogar novamente!\n");
                respostaJogo = 0;
              } // autoexplicativo

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
}

int verifica_fim_jogo(){
    int i;
    quemGanhou = 0;
    for(i=0;i<max_clients;i++){
        if(basica.jogadores[i].pos_x == -1){
            quemGanhou++;
        }
    }
    if(quemGanhou == max_clients-1){//quer dizer que o jogo acabou.

        if(minha_intencao.pos_x == -1){
            alterar_historico(0); //se for 0,ele perdeu
            return 1;
        }else{
            printf("Voce ganhou!\n");
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_text(fonte, al_map_rgb(255, 255, 255), Ltela / 2, 250, ALLEGRO_ALIGN_CENTRE, "Voce GANHOU!!!");
            al_flip_display();
            //al_rest(3.0);
            alterar_historico(1); //se for 1,ele ganhou
            return 1;
        }
    }
    return 0;
}

void apresentar_historico(){ // usar allegro em uma ViewController diferente

    FILE *file = fopen("status.bin","r");

    if(file != NULL){

        fread(&hist,sizeof(hist),1,file);
        printf("Voce ja soltou %d bombas ate agora!\n",hist.n_bombas_soltadas);
        printf("Voce ganhou %d partidas ate agora,hehe.\n",hist.n_partidas_ganhas);
        printf("Voce perdeu %d de um total de %d\n",hist.n_partidas_jogadas - hist.n_partidas_ganhas,hist.n_partidas_jogadas );
        printf("Um Win-Ratio de %.0lf!\n",hist.win_ratio*100);
        fclose(file);

    }
}

void salvar_historico(){

  FILE *file = fopen("status.bin","w");

    if(file != NULL){

        fwrite(&hist,sizeof(hist),1,file); // escrever
        fclose(file);

    }
}

void alterar_historico(char ganhou){

    FILE *file = fopen("status.bin","r"); // se o arquivo nao existir, eh criado um

    if(file != NULL){ // caso o arquivo possa ser aberto

        fread(&hist,sizeof(hist),1,file);
        hist.n_bombas_soltadas += n_bombas;
        if(ganhou == 0){ // o jogador perdeu
          hist.n_partidas_jogadas++;
          hist.win_ratio = hist.n_partidas_ganhas / hist.n_partidas_jogadas;// ve aqui
        }else{// ele ganhou
          hist.n_partidas_jogadas++;
          hist.n_partidas_ganhas++;
          hist.win_ratio = hist.n_partidas_ganhas / hist.n_partidas_jogadas;
        }
        fclose(file);
    }
    salvar_historico();
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
               n_bombas++; // incrementa o nº de bombas lançadas
            }
            break;
	 }
}

void printa_matriz(int inicio_aux_Bomba[]){ //por hora,em printa matriz,ele so atualiza o relogio se o cara se movimentar,cabe a glr de allegro colocar um timer independente e funcional
    system("clear"); //limpa o cmd
    int i,j,k,l,m;
    printf("%.0lf\n",240 - difftime(atualJogo,inicioJogo));
    for(i=0, l=0;i<tamanho_altura;i++, l+=37){
        for(j=0, m=0;j<tamanho_largura;j++, m+=37){
            verifica = 0;
            for(k=0;k<max_clients;k++){
                if(basica.jogadores[k].pos_x == i && basica.jogadores[k].pos_y == j){
                    printf("%d",basica.jogadores[k].id+1); // valor p simbolizar o jogador
                    //al_draw_bitmap(sprites, m, l, 0);
                    switch (anterior[k]) { // printar a sprite de acordo com o jogador
                      case 'W': al_draw_bitmap_region(sprites,111,37*k,37,37,m,l,0);
                      break;
                      case 'A': al_draw_bitmap_region(sprites,0,37*k,37,37,m,l,0);
                      break;
                      case 'S': al_draw_bitmap_region(sprites,74,37*k,37,37,m,l,0);
                      break;
                      case 'D': al_draw_bitmap_region(sprites,37,37*k,37,37,m,l,0);
                      break;
                    }
                    //al_draw_bitmap_region(sprites,0,0,37,37,m,l,0);
                    verifica++;
                }
                else if(inicio_aux_Bomba[k] == 1 && basica.jogadores[k].posbomba_x == i && basica.jogadores[k].posbomba_y == j){ //caso tenha uma bomba no mapa
                    printf("b"); //printa a bomba(mas o jogador vai em cima,caso esteja no mesmo bloco,por hora)
                    if (tmp_bomb) {
                      al_draw_bitmap(explosion, m-37, l-37, 0); // if para a explosao
                    }
                    else {
                      al_draw_bitmap(bomb, m, l, 0);
                    }
                    verifica++;
                }
            }
            if(verifica==0){ //se ele n printou ngm,ele printa a matriz
                if(matriz[i][j] == 1 ) {
                  printf("0");
                  al_draw_bitmap(verde_1, m, l, 0);
                }else if(matriz[i][j] == 2){
                  printf("0");
                  al_draw_bitmap(verde_2, m, l, 0);
                }else if(matriz[i][j] == quebra){
                  printf("Q");
                  al_draw_bitmap(quebr, m, l, 0);
                }
                else{
                  printf("N");
                  al_draw_bitmap(pedr, m, l, 0);
                }
            }
        }printf("\n");
    }
    al_flip_display();
    if (tmp_bomb) { // delay qdo a variavel da bomba for um para manter a explosao por mais tempo
      al_rest(0.15); // tempo bem curto pra tentar manter a jogabilidade
      tmp_bomb = 0;
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
                    if(matou == 1){ // isso significa que ele morreu
                        minha_intencao.pos_x = -1;
                        minha_intencao.pos_y = -1;
                        matou = 0;
                        sendMsgToServer(&minha_intencao,sizeof(msg_do_cliente));
                        printf("Voce perdeu!\n");
                        al_draw_bitmap(background, 0, 0, 0);
                        al_draw_text(fonte, al_map_rgb(255, 255, 255), Ltela / 2, 250, ALLEGRO_ALIGN_CENTRE, "Voce PERDEU!!!");
                        al_flip_display();
                        al_rest(5.0);
                    }
                    inicio_aux_Bomba[i] = 0; //prepara para receber outra bomba
                    printf("BOOM\n");
                    printa_matriz(inicio_aux_Bomba);
               }
          }
     }
}

char controla_raio_explosao(char matou,int inicio_aux_Bomba[]){ //
    int k;
    int verificou = 0;
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
              verificou = 1;

          }
          if(matriz[basica.jogadores[k].posbomba_x-1][basica.jogadores[k].posbomba_y] == quebra){

              matriz[basica.jogadores[k].posbomba_x-1][basica.jogadores[k].posbomba_y] = verd_1;
              verificou = 1;

          }
          if(matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y+1] == quebra){

              matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y+1] = verd_1;
              verificou = 1;

          }
          if(matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y-1] == quebra){

              matriz[basica.jogadores[k].posbomba_x][basica.jogadores[k].posbomba_y-1] = verd_1;
              verificou = 1;

          }
      }
    if(verificou != 0) {
      tmp_bomb = 1; // adiciona 1 a variavel para explosao
      printa_matriz(inicio_aux_Bomba);
    }
    return matou; //retorna 0 - nao morreu ou 1 - morreu
}

bool inicializar () {
  if (!al_init()) {
      puts("Falha ao inicializar a Allegro.\n");
      return false;
  }
  // if (!al_install_audio()) {
  //     fprintf(stderr, "Falha ao inicializar áudio.\n");
  //     return false;
  // }
  //
  // if (!al_init_acodec_addon()) {
  //     fprintf(stderr, "Falha ao inicializar codecs de áudio.\n");
  //     return false;
  // }
  //
  // if (!al_reserve_samples(1)) {
  //     fprintf(stderr, "Falha ao alocar canais de audio.\n");
  //     return false;
  // }
  // sample = al_load_sample("teste2.ogg");
  // if (!sample) {
  //     puts("Falha ao carregar sample.\n");
  //     return false;
  // }
  // musica = al_load_audio_stream("teste1.ogg", 4, 1024);
  // if (!musica) {
  //     puts("Falha ao carregar audio.\n");
  //     return false;
  // }
  //al_init_timeout(&timeout, 0.001);
  al_init_font_addon();
  if (!al_init_ttf_addon()) {
      puts("Falha ao inicializar add-on allegro_ttf.\n");
      return false;
  }
  if (!al_init_image_addon()) {
      puts("Falha ao inicializar add-on allegro_image.\n");
      return false;
  }
  if (!al_install_keyboard()) {
      puts("Falha ao inicializar o teclado.\n");
      return false;
  }
  janela = al_create_display(Ltela, Atela);
  if (!janela) {
      puts("Falha ao criar janela.\n");
      return false;
  }
  al_set_window_title(janela, "CINXPLODE");
//  al_set_window_position(janela, 200, 100); //setar a posicao da janela // HUGO
//  al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);// para poder ajustar o tamanho da tela. // HUGO
  fonte = al_load_font("comic.ttf", 48, 0);
  if (!fonte) {
      puts("Falha ao carregar \"fonte comic.ttf\".\n");
      al_destroy_display(janela);
      return false;
  }
  fila_eventos = al_create_event_queue();
  if (!fila_eventos) {
      puts("Falha ao criar fila de eventos.\n");
      al_destroy_display(janela);
      return false;
  }
  pedr = al_load_bitmap("pedr.bmp");
  if (!pedr) {
      puts("Falha ao carregar imagem pedra\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  marro = al_load_bitmap("marro.bmp");
  if (!marro) {
      puts("Falha ao carregar imagem marrom.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  quebr = al_load_bitmap("quebr.bmp");
  if (!quebr) {
      puts("Falha ao carregar imagem quebra.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  verde_1 = al_load_bitmap("verde_1.bmp");
  if (!verde_1) {
      puts("Falha ao carregar imagem verde_1.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  verde_2 = al_load_bitmap("verde_2.bmp");
  if (!verde_2) {
      puts("Falha ao carregar imagem verde_2.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  bomb = al_load_bitmap("bomb.bmp");
  if (!bomb) {
      puts("Falha ao carregar imagem bomb.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  sprites = al_load_bitmap("sprites.png");
  if (!sprites) {
      puts("Falha ao carregar imagem do sprites.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  explosion = al_load_bitmap("explosion.png");
  if (!explosion) {
      puts("Falha ao carregar imagem do explosion.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  background = al_load_bitmap("background.png");
  if (!background) {
      puts("Falha ao carregar imagem do background.\n");
      al_destroy_display(janela);
      al_destroy_event_queue(fila_eventos);
      return false;
  }
  al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // registrar eventos do teclado
  al_register_event_source(fila_eventos, al_get_display_event_source(janela)); // registrar eventos da janela
  return true;
}

void destroy () {
  al_destroy_font(fonte);
  al_destroy_display(janela);
  al_destroy_event_queue(fila_eventos);
}

void atribui_pos_ant(){ //antiga_pos[x].id/pos_ant_x/y
    antiga_pos[0].id = basica.jogadores[0].id;
    antiga_pos[0].pos_ant_x = basica.jogadores[0].pos_x;
    antiga_pos[0].pos_ant_y = basica.jogadores[0].pos_y;

    antiga_pos[1].id = basica.jogadores[1].id;
    antiga_pos[1].pos_ant_x = basica.jogadores[1].pos_x;
    antiga_pos[1].pos_ant_y = basica.jogadores[1].pos_y;

    antiga_pos[2].id = basica.jogadores[2].id;
    antiga_pos[2].pos_ant_x = basica.jogadores[2].pos_x;
    antiga_pos[2].pos_ant_y = basica.jogadores[2].pos_y;

    antiga_pos[3].id = basica.jogadores[3].id;
    antiga_pos[3].pos_ant_x = basica.jogadores[3].pos_x;
    antiga_pos[3].pos_ant_y = basica.jogadores[3].pos_y;

}

void atrib_jog_ant () { // verificar a posicao anteior do jogador
  int i;
  for (i=0;i<4;i++) {
      if (basica.jogadores[i].pos_x < antiga_pos[i].pos_ant_x)
      anterior[i] = 'W';
      if (basica.jogadores[i].pos_x > antiga_pos[i].pos_ant_x)
      anterior[i] = 'S';
      if (basica.jogadores[i].pos_y < antiga_pos[i].pos_ant_y)
      anterior[i] = 'A';
      if (basica.jogadores[i].pos_y > antiga_pos[i].pos_ant_y)
      anterior[i] = 'D';
    }
}
