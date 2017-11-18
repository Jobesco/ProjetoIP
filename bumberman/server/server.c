#include "server.h"
#include "default.h"

#define max_clients 4
#define tamanho_altura 8
#define tamanho_largura 12
#define pedra 0
#define verd_1 1
#define verd_2 2
#define marrom 3
#define quebra 4

char matriz[tamanho_altura][tamanho_largura] = { //ele pode acessar 6x10
    
        {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra},
        {pedra,verd_1,marrom,quebra,verd_2,verd_1,quebra,quebra,quebra,verd_1,verd_2,pedra},
        {pedra,verd_2,verd_1,quebra,marrom,verd_2,quebra,verd_2,quebra,quebra,verd_1,pedra},
        {pedra,quebra,quebra,marrom,verd_2,marrom,quebra,verd_1,marrom,quebra,quebra,pedra},
        {pedra,quebra,quebra,verd_2,verd_1,verd_2,quebra,quebra,verd_1,marrom,quebra,pedra},
        {pedra,verd_1,verd_2,quebra,quebra,marrom,marrom,verd_1,quebra,verd_1,quebra,pedra},
        {pedra,verd_1,quebra,quebra,quebra,quebra,quebra,quebra,quebra,verd_2,verd_1,pedra},
        {pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra,pedra}
                                               
};

typedef struct msg_do_cliente{
	char pos_x;
  	char pos_y;
} msg_do_cliente;

typedef struct{
  
  char id;
  char pos_x;
  char pos_y;
  
} jogador;

typedef struct{
  
  jogador jogadores[4]; //eh 2 pq recebe as posicoes(x,y) num plano cartesiano.
  
} msg_todos;

void iniciar_jogo(msg_todos basica){
  
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

int estabelecer_conexao(){
    
    int n_conexoes = 0;
    int id_temp = acceptConnection();
    
    serverInit(max_clients); // inicia_server
  
    
    while(n_conexoes < max_clients){
        
        if(n_conexoes < max_clients && id_temp != NO_CONNECTION ){ // if redundante p evitar resto do while
            
                id[n_conexoes] = id_temp;
                n_conexoes++;
                
            }else{
            
            rejectConnection();
            
        }
      
      }//conexoes estabelecidas
    return 1;   
}

msg_todos basica; //essa eh a mensagem basica para todos a ser enviada. 

msg_ret_t recebe_cliente[4];

msg_do_cliente msg_do_cliente[4];

void main(){
    
  estabelecer_conexao();
    iniciar_jogo(basica);
    int contador; //contador padrao
  
    while(1){ //loop referente ao jogo
      
      broadcast(basica,sizeof(msg_todos)); // manda a mensagem p geral!
      
      recebe_cliente[0] =  recvMsgFromClient(msg_do_cliente[0] , basica.jogadores[0].id , DONT_WAIT);
      recebe_cliente[1] =  recvMsgFromClient(msg_do_cliente[1] , basica.jogadores[1].id , DONT_WAIT);
      recebe_cliente[2] =  recvMsgFromClient(msg_do_cliente[2] , basica.jogadores[2].id , DONT_WAIT);
      recebe_cliente[3] =  recvMsgFromClient(msg_do_cliente[3] , basica.jogadores[3].id , DONT_WAIT);
      
      for(i=0;i<4;i++){
        if(recebe_cliente[i].status == MESSAGE_OK){ //ele vai receber,por hora,a intencao de movimento.
          if(matriz[msg_do_cliente[i].posx][msg_do_cliente[i].pos_y] == 1 || matriz[msg_do_cliente[i].posx][msg_do_cliente[i].pos_y] == 2){ //caso a casa correspondente na matriz da intencao de movimento do personagem seja 1 ou 2(casas caminhaveis)

              basica.jogadores[i].pos_x = msg_do_cliente[i].posx; //altera a posicao dele em broadcast(como ele printa a matriz e depois o jogador de acordo com a localizacao,eu nao preciso alterar nada na matriz,pq nada eh alterado nela)
              basica.jogadores[i].pos_y = msg_do_cliente[i].posy;
          }
        }
        
        if(recebe_cliente[i].status == DISCONNECT_MSG){
          basica.jogadores[i].pos_x = -1; //se ele estiveer na posicao -1,ele nao ira printa-lo
            basica.jogadores[i].pos_y = -1;
        }
           
      }
      
      
      
    }
      
}