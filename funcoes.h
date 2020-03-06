float escala = 0.5;
int xCenario=512, yCenario=256, zCenario=256;
int distanciaJogadores = 20;

int rotacaoJogador1 = 90;
int rotacaoJogador2 = -90;

int estadoJogador1 = 0;
int estadoJogador2 = 0;

int vitoriaJogador1 = 0;
int vitoriaJogador2 = 0;

int posxJogador1 = -(xCenario/2)+128;
int posxJogador2 = (xCenario/2)-128;
int posyJogador1 = 0;
int posyJogador2 = 0;

int puloJogador1 = 100;
int puloJogador2 = 100;

int passoJogador1 = 0;
int passoJogador2 = 0;

int socoJogador1 = 6;
int socoJogador2 = 6;

int chuteJogador1 = 6;
int chuteJogador2 = 6;

float vidaJogador1 = 1;
float vidaJogador2 = 1;
float vidaEspecialJogador1 = 1;
float vidaEspecialJogador2 = 1;
int travaJogador1 = 1;
int travaJogador2 = 1;

int arrastaEspecial = 0;
int fimJogo = 0;

int especialJogador1 = 0;
int especialJogador2 = 0;
int posxEspecialJogador1 = 1;
int posxEspecialJogador2 = 1;

float danoSoco = 0.002;
float danoChute = 0.001;
float danoEspecial = 0.004;

int textoCentro = 0;
char texto[20];
char textoTempo[5] = "99";
char texturaParede[10];
char textoVitoria1[5] = "0";
char textoVitoria2[5] = "0";

int pause = 0;
int tempoAtual = 0;
int tempoAnteriorJogo = 0;
int tempoJogo = -4;
int tempoAnteriorIdle = 0;
int tempoIdle = 0;
int semaforoIdle = 0;

float aceleracaoJogo = 4;

int keyVet[256];
char flag, ordem=1;

vector<Ponto> jogadorNormalV;
vector<Textura> jogadorNormalT;
vector<Ponto> jogadorNormalN;

vector<Ponto> jogadorAbaixadoV;
vector<Textura> jogadorAbaixadoT;
vector<Ponto> jogadorAbaixadoN;

vector<Ponto> jogadorChuteFinalV;
vector<Textura> jogadorChuteFinalT;
vector<Ponto> jogadorChuteFinalN;

vector<Ponto> jogadorChuteIntermediarioV;
vector<Textura> jogadorChuteIntermediarioT;
vector<Ponto> jogadorChuteIntermediarioN;

vector<Ponto> jogadorSocoFinalV;
vector<Textura> jogadorSocoFinalT;
vector<Ponto> jogadorSocoFinalN;

vector<Ponto> jogadorSocoIntermediarioV;
vector<Textura> jogadorSocoIntermediarioT;
vector<Ponto> jogadorSocoIntermediarioN;

vector<Ponto> jogadorTomandoChuteV;
vector<Textura> jogadorTomandoChuteT;
vector<Ponto> jogadorTomandoChuteN;

vector<Ponto> jogadorTomandoSocoV;
vector<Textura> jogadorTomandoSocoT;
vector<Ponto> jogadorTomandoSocoN;

vector<Ponto> espadaV;
vector<Textura> espadaT;
vector<Ponto> espadaN;


void contaVitoria(int j){
	if(j == 1){
		vitoriaJogador1++;
		sprintf(textoVitoria1, "%d", vitoriaJogador1);
	}else{
		vitoriaJogador2++;
		sprintf(textoVitoria2, "%d", vitoriaJogador2);
	}	
}


pausaJogo(){
	if(fimJogo == 0){ 
		if(pause == 0){
			pause = 1;
			strcpy(texto, "Jogo Pausado");
			textoCentro = 1;
		}else{
			pause = 0;
			textoCentro = 0;
		}
	}
	glutPostRedisplay();
}


void mudaTexturaJogador(int t1, int t2){
	if(t1 == 0) textura1 = carregaBMP("textura/jogador0.bmp");
	if(t1 == 1) textura1 = carregaBMP("textura/jogador1.bmp");
	if(t1 == 2) textura1 = carregaBMP("textura/jogador2.bmp");
	if(t1 == 3) textura1 = carregaBMP("textura/jogador3.bmp");
	if(t1 == 4) textura1 = carregaBMP("textura/jogador4.bmp");
	if(t1 == 5) textura1 = carregaBMP("textura/jogador5.bmp");
	if(t1 == 6) textura1 = carregaBMP("textura/jogador6.bmp");
	if(t1 == 7) textura1 = carregaBMP("textura/jogador7.bmp");
	
	if(t2 == 0) textura2 = carregaBMP("textura/jogador0.bmp");
	if(t2 == 1) textura2 = carregaBMP("textura/jogador1.bmp");
	if(t2 == 2) textura2 = carregaBMP("textura/jogador2.bmp");
	if(t2 == 3) textura2 = carregaBMP("textura/jogador3.bmp");
	if(t2 == 4) textura2 = carregaBMP("textura/jogador4.bmp");
	if(t2 == 5) textura2 = carregaBMP("textura/jogador5.bmp");
	if(t2 == 6) textura2 = carregaBMP("textura/jogador6.bmp");
	if(t2 == 7) textura2 = carregaBMP("textura/jogador7.bmp");	
}


void carregaInit(){
	carregaOBJ("lutador/normal.obj", jogadorNormalV, jogadorNormalT, jogadorNormalN);
	carregaOBJ("lutador/abaixado.obj", jogadorAbaixadoV, jogadorAbaixadoT, jogadorAbaixadoN);
	carregaOBJ("lutador/chuteFinal.obj", jogadorChuteFinalV, jogadorChuteFinalT, jogadorChuteFinalN);
	carregaOBJ("lutador/chuteIntermediario.obj", jogadorChuteIntermediarioV, jogadorChuteIntermediarioT, jogadorChuteIntermediarioN);
	carregaOBJ("lutador/socoFinal.obj", jogadorSocoFinalV, jogadorSocoFinalT, jogadorSocoFinalN);
	carregaOBJ("lutador/socoIntermediario.obj", jogadorSocoIntermediarioV, jogadorSocoIntermediarioT, jogadorSocoIntermediarioN);
	carregaOBJ("lutador/tomandoChute.obj", jogadorTomandoChuteV, jogadorTomandoChuteT, jogadorTomandoChuteN);
	carregaOBJ("lutador/tomandoSoco.obj", jogadorTomandoSocoV, jogadorTomandoSocoT, jogadorTomandoSocoN);
    carregaOBJ("lutador/espada.obj", espadaV, espadaT, espadaN);
    
    espada = carregaBMP("textura/espada.bmp");
    
    srand((unsigned)time(NULL));
    int t1=0, t2=0;
    
    while(t1 == t2){
		t1 = rand() % 8;
		t2 = rand() % 8;
	}
	
	mudaTexturaJogador(t1, t2);
  
	t1 = rand() % 3;
	if(t1 == 0) chao = carregaBMP("textura/chao0.bmp");
	if(t1 == 1) chao = carregaBMP("textura/chao1.bmp");
	if(t1 == 2) chao = carregaBMP("textura/chao2.bmp");
	
	t2 = rand() % 5; 
	if(t2 == 0) parede = carregaBMP("textura/parede0.bmp");
	if(t2 == 1) parede = carregaBMP("textura/parede1.bmp");
	if(t2 == 2) parede = carregaBMP("textura/parede2.bmp");
	if(t2 == 3) parede = carregaBMP("textura/parede3.bmp");
	if(t2 == 4) parede = carregaBMP("textura/parede4.bmp");
	
	alutInit(NULL, 0);
	alGetError();
	if(LoadALData() == AL_FALSE){
		printf("Erro ao carregar o som.\n");
		return;
	}
	SetListenerValues();
	alSourcePlay(Sources[FUNDO]);
}


void cenario(){
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, chao);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3i(-(xCenario/2), 0, (zCenario/2));
			glTexCoord2f(0, 1);
			glVertex3i(-(xCenario/2), 0, -(zCenario/2));
			glTexCoord2f(1, 1);
			glVertex3i((xCenario/2), 0, -(zCenario/2));
			glTexCoord2f(1, 0);
			glVertex3i((xCenario/2), 0, (zCenario/2));
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, parede);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3i(-(xCenario/2), 0, -(zCenario/2));
			glTexCoord2f(0, 1);
			glVertex3i(-(xCenario/2), yCenario, -(zCenario/2));
			glTexCoord2f(1, 1);
			glVertex3i((xCenario/2), yCenario, -(zCenario/2));
			glTexCoord2f(1, 0);
			glVertex3i((xCenario/2), 0, -(zCenario/2));
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();	
}


void reiniciaJogo(){
	vidaJogador1 = 1;
	vidaJogador2 = 1;
	vidaEspecialJogador1 = 1;
	vidaEspecialJogador2 = 1;
	travaJogador1 = 1;
	travaJogador2 = 1;
	estadoJogador1 = 0;
	estadoJogador2 = 0;
	posxJogador1 = -(xCenario/2)+128;
	posxJogador2 = (xCenario/2)-128;
	posyJogador1 = 0;
	posyJogador2 = 0;
	tempoJogo = -4;
	especialJogador1 = 0;
	especialJogador2 = 0;
	posxEspecialJogador1 = 1;
	posxEspecialJogador2 = 1;
	sprintf(textoTempo, "%d", 99);
	pause = 0;
	fimJogo = 0;
}


float pulo(int t){
    return (25*t - (2*t*t)/2);
}


void calculaTempo(){
    tempoAtual = glutGet(GLUT_ELAPSED_TIME);
    int intervalo = tempoAtual - tempoAnteriorJogo;
    if(intervalo >= 1000 && pause != 1){
		tempoJogo++;
        tempoAnteriorJogo = tempoAtual;
		if(tempoJogo > 0) sprintf(textoTempo, "%d", 99-tempoJogo);
		glutPostRedisplay();
    }
    //intervalo = tempoAtual - tempoAnteriorIdle;
    //if(intervalo >= 15){
	//	tempoIdle++;
	//	tempoAnteriorIdle = tempoAtual;
	//}
}


void acaoJogador1(double ac){
	//pulo
    if(puloJogador1 < 100){
        puloJogador1++;
        posyJogador1 = pulo(puloJogador1);
        if(posyJogador1 <= 0){
            puloJogador1 = 100;
            posyJogador1 = 0;
            estadoJogador1 = 0;
        }
        flag = 1;
    }
    //soco
    if(socoJogador1 < 6){
		if(posxJogador1+2*distanciaJogadores >= posxJogador2 && estadoJogador2 != 1 && posyJogador2 < 30 && posyJogador1 < 30){
			estadoJogador2 = 7;
			posxJogador2 += ac;
			vidaJogador2 -= danoSoco;
		}
		if(socoJogador1 == 0) estadoJogador1 = 4; 
		if(socoJogador1 == 2) estadoJogador1 = 5;
		if(socoJogador1 == 5){
			estadoJogador1 = 0;
			if(estadoJogador2 == 7){
				estadoJogador2 = 0;
				alSourcePlay(Sources[SECO]);
				alSourcePlay(Sources[SOCO]);
			}else{
				alSourcePlay(Sources[SECO]);
			}
		}
		socoJogador1++;
		keyVet[(int)('1')] = 0;
		flag = 1;
    }
    //chute
    if(chuteJogador1 < 6){
		if(posxJogador1+2*distanciaJogadores >= posxJogador2 && posyJogador2 < 30 && posyJogador1 < 30){
			estadoJogador2 = 6;
			posxJogador2 += ac*2;
			vidaJogador2 -= danoChute;
		}
		if(chuteJogador1 == 0) estadoJogador1 = 2; 
		if(chuteJogador1 == 2) estadoJogador1 = 3;
		if(chuteJogador1 == 5){
			estadoJogador1 = 0;
			if(estadoJogador2 == 6){
				estadoJogador2 = 0;
				alSourcePlay(Sources[SECO]);
				alSourcePlay(Sources[CHUTE]);
			}else{
				alSourcePlay(Sources[SECO]);
			}
		}
		chuteJogador1++;
		keyVet[(int)('2')] = 0;
		flag = 1;
    }
    //especial
    if(especialJogador1 == 1){
		posxEspecialJogador1 += ac*3*escala;
		if((posxEspecialJogador1+distanciaJogadores >= posxJogador2 && posxJogador2+distanciaJogadores > posxEspecialJogador1) && estadoJogador2 != 1 && posyJogador2 < 50 && arrastaEspecial < 40){
			estadoJogador2 = 7;
			posxJogador2+=ac*1.3;
			arrastaEspecial++;
			vidaJogador2 -= danoEspecial;
			travaJogador2 = 1;
		}
		if(arrastaEspecial == 40 || (posxJogador2+distanciaJogadores < posxEspecialJogador1 && estadoJogador2 != 1)){
			if(estadoJogador2 == 7){
				estadoJogador2 = 0;
				travaJogador2 = 0;
				especialJogador1 = 0;
				alSourcePlay(Sources[CORTE]);
			}
			arrastaEspecial = 0;
		}
		if(posxEspecialJogador1 >= xCenario){
			especialJogador1 = 0;
			travaJogador2 = 0;
		}
		flag = 1;
	}
}


void acaoJogador2(double ac){
    //pulo
    if(puloJogador2 < 100){
        puloJogador2++;
        posyJogador2 = pulo(puloJogador2);
        if(posyJogador2 <= 0){
            puloJogador2 = 100;
            posyJogador2 = 0;
            estadoJogador2 = 0;
        }
        flag = 1;
    }
    //soco
    if(socoJogador2 < 6){
		if(posxJogador2-2*distanciaJogadores <= posxJogador1 && estadoJogador1 != 1 && posyJogador1 < 30 && posyJogador2 < 30){
			estadoJogador1 = 7;
			posxJogador1 -= ac;
			vidaJogador1 -= danoSoco;
		}
		if(socoJogador2 == 0) estadoJogador2 = 4; 
		if(socoJogador2 == 2) estadoJogador2 = 5;
		if(socoJogador2 == 5){
			estadoJogador2 = 0;
			if(estadoJogador1 == 7){
				estadoJogador1 = 0;
				alSourcePlay(Sources[SECO]);
				alSourcePlay(Sources[SOCO]);
			}else{
				alSourcePlay(Sources[SECO]);
			}
		}
		socoJogador2++;
		keyVet[(int)('8')] = 0;
		flag = 1;
    }
    //chute
    if(chuteJogador2 < 6){
		if(posxJogador2-2*distanciaJogadores <= posxJogador1 && posyJogador1 < 30 && posyJogador2 < 30){
			estadoJogador1 = 6;
			posxJogador1 -= ac*2;
			vidaJogador1 -= danoChute;
		}
		if(chuteJogador2 == 0) estadoJogador2 = 2; 
		if(chuteJogador2 == 2) estadoJogador2 = 3;
		if(chuteJogador2 == 5){
			estadoJogador2 = 0;
			if(estadoJogador1 == 6){
				estadoJogador1 = 0;
				alSourcePlay(Sources[SECO]);
				alSourcePlay(Sources[CHUTE]);
			}else{
				alSourcePlay(Sources[SECO]);
			}
		}
		chuteJogador2++;
		keyVet[(int)('9')] = 0;
		flag = 1;
    }
    //especial
    if(especialJogador2 == 1){
		posxEspecialJogador2 -= ac*3*escala;
		if((posxEspecialJogador2-distanciaJogadores <= posxJogador1 && posxJogador1-distanciaJogadores < posxEspecialJogador2) && estadoJogador1 != 1 && posyJogador1 < 50 && arrastaEspecial < 40){
			estadoJogador1 = 7;
			posxJogador1-=ac*1.3;
			arrastaEspecial++;
			vidaJogador1 -= danoEspecial;
			travaJogador1 = 1;
		}
		if(arrastaEspecial == 40 || (posxJogador1-distanciaJogadores > posxEspecialJogador2 && estadoJogador1 != 1)){
			if(estadoJogador1 == 7){
				estadoJogador1 = 0;
				travaJogador1 = 0;
				especialJogador2 = 0;
				alSourcePlay(Sources[CORTE]);
			}
			arrastaEspecial = 0;
		}
		if(posxEspecialJogador2 <= -xCenario){
			especialJogador2 = 0;
			travaJogador1 = 0;
		}
		flag = 1;
	}
}


void idle(){
	calculaTempo();
	
	if(tempoJogo < 0){
		sprintf(texto, " --- %d ---", tempoJogo*(-1));
		textoCentro = 1;
	}
	if(tempoJogo == 0){
		sprintf(texto, "  Lutem!", tempoJogo*(-1));
		textoCentro = 1;
		if(travaJogador1 == 1) alSourcePlay(Sources[LUTEM]);
		travaJogador1 = 0;
		travaJogador2 = 0;		
	}
	if(tempoJogo == 1){
		textoCentro = 0;
	}
	
	if(pause == 1) return;

	double ac = aceleracaoJogo;
	flag = 0;
	
	//teclas de ação do jogador 1
	if(keyVet[(int)('s')] == 1 && travaJogador1 == 0){
        estadoJogador1 = 1;
        flag = 1;
	}
	if(keyVet[(int)('w')] == 1 && travaJogador1 == 0){
        if(puloJogador1 == 100){
            puloJogador1 = 0;
            alSourcePlay(Sources[PULO]);
        }
    }
	if(keyVet[(int)('a')] == 1  && travaJogador1 == 0){
        posxJogador1 -= ac;
        passoJogador1++;
        if(passoJogador1 == 8){
			if(estadoJogador1 == 0){
				estadoJogador1 = 5;
			}else{
				estadoJogador1 = 0;
			}
			passoJogador1 = 0;
		}
        flag = 1;
    }
	if(keyVet[(int)('d')] == 1 && posxJogador1+distanciaJogadores <= posxJogador2  && travaJogador1 == 0){
        posxJogador1 += ac;
        passoJogador1++;
        if(passoJogador1 == 8){
			if(estadoJogador1 == 0){
				estadoJogador1 = 5;
			}else{
				estadoJogador1 = 0;
			}
			passoJogador1 = 0;
		}
        flag = 1;
	}
	if(keyVet[(int)('1')] == 1 && travaJogador1 == 0){
        socoJogador1 = 0;
	}
	if(keyVet[(int)('2')] == 1 && travaJogador1 == 0){
		chuteJogador1 = 0;
	}
	if(keyVet[(int)('3')] == 1 && especialJogador1 == 0 && posyJogador1 < 10 && travaJogador1 == 0){
		if(vidaEspecialJogador1 > 0.1){
			vidaEspecialJogador1 -= 0.2;
			estadoJogador1 = 4;
			posxEspecialJogador1 = posxJogador1+distanciaJogadores;
			especialJogador1 = 1;
			alSourcePlay(Sources[LANCA]);
		}
	}
	
	//teclas de ação do jogador 2
	if(keyVet[(int)('k')] == 1 && travaJogador2 == 0){
        estadoJogador2 = 1;
        flag = 1;
	}
	if(keyVet[(int)('i')] == 1 && travaJogador2 == 0){
        if(puloJogador2 == 100){
            puloJogador2 = 0;
            alSourcePlay(Sources[PULO]);
        }
    }
	if(keyVet[(int)('j')] == 1  && posxJogador2-distanciaJogadores >= posxJogador1 && travaJogador2 == 0){
        posxJogador2 -= ac;
        passoJogador2++;
        if(passoJogador2 == 8){
			if(estadoJogador2 == 0){
				estadoJogador2 = 5;
			}else{
				estadoJogador2 = 0;
			}
			passoJogador2 = 0;
		}
        flag = 1;
    }
	if(keyVet[(int)('l')] == 1  && travaJogador2 == 0){
        posxJogador2 += ac;
        passoJogador2++;
        if(passoJogador2 == 8){
			if(estadoJogador2 == 0){
				estadoJogador2 = 5;
			}else{
				estadoJogador2 = 0;
			}
			passoJogador2 = 0;
		}
        flag = 1;
    }
	if(keyVet[(int)('8')] == 1 && travaJogador2 == 0){
        socoJogador2 = 0;
	}
	if(keyVet[(int)('9')] == 1 && travaJogador2 == 0){
        chuteJogador2 = 0;
	}
	if(keyVet[(int)('0')] == 1 && especialJogador2 == 0 && posyJogador2 < 10 && travaJogador2 == 0){
		if(vidaEspecialJogador2 > 0.1){
			vidaEspecialJogador2 -= 0.2;
			estadoJogador2 = 4;
			posxEspecialJogador2 = posxJogador2-distanciaJogadores;
			especialJogador2 = 1;
			alSourcePlay(Sources[LANCA]);
		}
	}
	
	if(ordem == 1){
		acaoJogador1(ac);
		acaoJogador2(ac);
		ordem = 2;
	}else{
		acaoJogador2(ac);
		acaoJogador1(ac);
		ordem = 1;
	}
     
    //não deixar os jogadores fugir da tela
	if(posxJogador1 <= -(xCenario/3)) posxJogador1 = -(xCenario/3);
	if(posxJogador1 >= (xCenario/3)) posxJogador1 = (xCenario/3);
	if(posxJogador2 >= (xCenario/3)) posxJogador2 = (xCenario/3);
	if(posxJogador2 <= -(xCenario/3)) posxJogador2 = -(xCenario/3);
	
	//verificar quem ganhou
	if(vidaJogador1 <= 0){
		vidaJogador1 = 0;
		textoCentro = 1;
		strcpy(texto, "Jogador 2 Venceu!");
		contaVitoria(2);
		alSourcePlay(Sources[APLAUSOS]);
		pause = 1;
		fimJogo = 1;
		flag = 1;
	}
	
	if(vidaJogador2 <= 0){
		vidaJogador2 = 0;
		textoCentro = 1;
		strcpy(texto, "Jogador 1 Venceu!");
		contaVitoria(1);
		alSourcePlay(Sources[APLAUSOS]);
		pause = 1;
		fimJogo = 1;
		flag = 1;
	}
	
	if(tempoJogo >= 99){
		if(vidaJogador1 > vidaJogador2){
			strcpy(texto, "Jogador 1 Venceu!");
			contaVitoria(1);
		}else if(vidaJogador1 < vidaJogador2){
			strcpy(texto, "Jogador 2 Venceu!");
			contaVitoria(2);
		}else if(vidaJogador1 == vidaJogador2){
			strcpy(texto, "Luta Empatou!");
		}
		textoCentro = 1;
		alSourcePlay(Sources[APLAUSOS]);
		pause = 1;
		fimJogo = 1;
		flag = 1;
	}

    //só redesenhar a tela quando tiver algo pra fazer
	if(flag == 1) glutPostRedisplay();
}

void DesenhaTextoStroke(void *font, char *string){  
	// Exibe caractere a caractere
	while(*string) glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);
}
