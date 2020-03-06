pthread_t rede;

#define BUFLEN 6
#define PORT 8888
char SERVER[16];
struct sockaddr_in si_other;
int s, slen=sizeof(si_other);
char message[BUFLEN];

int modoRede = 0;
int jogadorSelecionado;
int enviouVitoria = 0;


void die(char *s){
    perror(s);
    exit(1);
}


void pressiona(char key[]){
    strcpy(message, key);
    if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1) die("sendto()");
}


void *socketRede(void *tmp){
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) die("socket");
    memset((char *) &si_me, 0, sizeof(si_me));   
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1) die("bind");
    while(modoRede == 1){
        fflush(stdout);
        memset(buf,'\0', BUFLEN);
        if((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) die("recvfrom()");
        
        if(strcmp(buf, "ppa") == 0) keyVet[(int)('a')] = 1;
        else if(strcmp(buf, "ppw") == 0) keyVet[(int)('w')] = 1;
        else if(strcmp(buf, "pps") == 0) keyVet[(int)('s')] = 1;
        else if(strcmp(buf, "ppd") == 0) keyVet[(int)('d')] = 1;
        else if(strcmp(buf, "lla") == 0) keyVet[(int)('a')] = 0;
        else if(strcmp(buf, "llw") == 0) keyVet[(int)('w')] = 0;
        else if(strcmp(buf, "lls") == 0) keyVet[(int)('s')] = 0;
        else if(strcmp(buf, "lld") == 0) keyVet[(int)('d')] = 0;
        
        else if(strcmp(buf, "ppj") == 0) keyVet[(int)('j')] = 1;
        else if(strcmp(buf, "ppi") == 0) keyVet[(int)('i')] = 1;
        else if(strcmp(buf, "ppk") == 0) keyVet[(int)('k')] = 1;
        else if(strcmp(buf, "ppl") == 0) keyVet[(int)('l')] = 1;
        else if(strcmp(buf, "llj") == 0) keyVet[(int)('j')] = 0;
        else if(strcmp(buf, "lli") == 0) keyVet[(int)('i')] = 0;
        else if(strcmp(buf, "llk") == 0) keyVet[(int)('k')] = 0;
        else if(strcmp(buf, "lll") == 0) keyVet[(int)('l')] = 0;
        
        else if(strcmp(buf, "pp1") == 0) keyVet[(int)('1')] = 1;
        else if(strcmp(buf, "pp2") == 0) keyVet[(int)('2')] = 1;
        else if(strcmp(buf, "pp8") == 0) keyVet[(int)('8')] = 1;
        else if(strcmp(buf, "pp9") == 0) keyVet[(int)('9')] = 1;
        
        else if(strcmp(buf, "pp3") == 0) keyVet[(int)('3')] = 1;
        else if(strcmp(buf, "pp0") == 0) keyVet[(int)('0')] = 1;
        else if(strcmp(buf, "ll3") == 0) keyVet[(int)('3')] = 0;
        else if(strcmp(buf, "ll0") == 0) keyVet[(int)('0')] = 0;
        
        else if(strcmp(buf, "F1") == 0) aceleracaoJogo -= 0.5;
        else if(strcmp(buf, "F2") == 0) aceleracaoJogo += 0.5;
        else if(strcmp(buf, "F3") == 0) {escala-=0.1; distanciaJogadores /= 1.5;}
        else if(strcmp(buf, "F4") == 0) {escala+=0.1; distanciaJogadores *= 1.5;}
        
        else if(strcmp(buf, "IN") == 0){reiniciaJogo(); enviouVitoria = 0;}
        else if(strcmp(buf, "sto") == 0) pausaJogo();
        else if(strcmp(buf, "exi") == 0) exit(0);
        else if(strcmp(buf, "vj1") == 0){vidaJogador2 = 0; enviouVitoria = 1;}
        else if(strcmp(buf, "vj2") == 0){vidaJogador1 = 0; enviouVitoria = 1;}
        else{
			int posx = atoi(buf);
			if(jogadorSelecionado == 1){
				posxJogador2 = posx;
			}else{
				posxJogador1 = posx;
			}
		}
		if(vidaJogador1 <= 0 && enviouVitoria == 0){pressiona("vj2"); enviouVitoria = 1;}
		if(vidaJogador2 <= 0 && enviouVitoria == 0){pressiona("vj1"); enviouVitoria = 1;}
		//fprintf(stderr, "%s\n", buf);
    }
}


void ligaRede(int j){
	FILE *fp = fopen("ips.txt", "r");
	if(fp == NULL){
		printf("Erro ao localizar endereço ip.\n");
		return;
	}else{
		fscanf(fp, "%s", SERVER);
		if(j == 2) fscanf(fp, "%s", SERVER);
		jogadorSelecionado = j;
		printf("\nMODO DE REDE ATIVO\n\nToda conexão será enviada para %s e voce será o jogador %d.\n", SERVER, j);
		fclose(fp);
	}
	int ex;
	ex = pthread_create(&rede, NULL, socketRede, NULL);
	if(ex != 0) printf("Erro ao criar a thread\n");
	
	modoRede = 1;
	
	if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) die("socket");
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton(SERVER , &si_other.sin_addr) == 0){
        fprintf(stderr, "inet_aton() failed\n");
        return;
    }
}
