#include "default.h"
#include "client.h"
#define max_clients 4
#define tamanho_altura 8
#define tamanho_largura 12
#define pedra 0
#define verd_1 1
#define verd_2 2
#define marrom 3
#define quebra 4

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
    
    char pos_x;
    char pos_y;
    
} jogador;

char *tratar_controle(char controle, char posix_atual[]){
    
    char *posix = (char *)malloc(2*sizeof(char));// posicao atualizada
    
    if(posix != NULL){
        
        switch (controle) {
            
            case 37:  // esquerda
                
                posix[0] = posix_atual[0]-'a';
                posix[1] = (posix_atual[1]-'a')-1;
                break;
        
            case 38: // cima
                
                posix[0] = (posix_atual[0]-'a')+1;
                posix[1] = (posix_atual[1]-'a');
                break;
                
            case 39: // direita
                
                posix[0] = posix_atual[0]-'a';
                posix[1] = (posix_atual[1]-'a')+1;
                break;
            
            case 40: //baixo
                
                posix[0] = (posix_atual[0]-'a')-1;
                posix[1] = (posix_atual[1]-'a');
                break;
                
            default:
                
                posix[0] = -1;
                posix[1] = -1;
                break;
        
        }
        
    }
    return posix;
}

int enviar_mensagem(jogador p1, char controle){
    
    char *posix;
    
    if(controle != NO_KEY_PRESSED){
        
        posix = tratar_controle(controle,posicao);
        p1.pos_x = posix[0];
        p1.pos_y = posix[1];
        
    }
    
    int retorno = sendMsgToServer(&p1, sizeof(jogador));//envia mensagem pro server
    
    return retorno;
    
}

void muda_posicao(jogador p1, char posix[]){
    
    matriz[posix[0]][posix[1]] = verd_1; // ou verd_2
    matriz[p1.pos_x][p1.pos_y] = player; // substitui a nova posicao pelo jogador
    
}

void main(){

	char IP[50];
	int estado;
	jogador player;
	int desconectado = 0;
	
	char controle = getch_();
    int retorno = 0;
    int bytes_lidos = 0;
	
	while(1){
	
	printf("Digite o IP onde deseja se conectar");]
	
	scanf(" %s",IP);
	
	estado = connectToServer(&IP);
	
	break;
	}
	
	while(desconectado != 1){ // verifica se o client ainda joga
    
        controle = getch_();
        
        if(estado == SERVER_UP){ //conexao estabelecida // prosseguir
            
            retorno = enviar_mensagem(p1,controle); // manda a msg
            
            if(retorno != SERVER_DISCONNECTED && retorno == sizeof(jogador)){ // msg enviada
            
                bytes_lidos = recvMsgFromServer(&p1, WAIT_FOR_IT); // aguarda a confirmacao do server
                muda_posicao(p1, posicao); // após constatado a validade da jogada, a posix muda
                
            } else if(retorno == SERVER_DISCONNECTED){
            	desconectado = 1;
            }
        
        }else if(estado == SERVER_DOWN){ //nao achou o server
            
            printf("Servidor nao encontrado!\n");
            
        }else if(estado == SERVER_FULL){ // cheio
            
            printf("Servidor lotado! Aguarde proxima partida\n");
            
        }else if(estado == SERVER_CLOSED){ // n aceita conexao
            
            printf("Servidor nao aceita novas conexoes!\n");
            
        }else if(estado == SERVER_TIMEOUT){ // demorou p responder
            
            printf("Voce esperou demais, verifique sua conexao de dados!\n");
            
        }
    }
	
	
	
	

}
