#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "CarregaOBJ.h"
#include "OpenAL.h"
#include "funcoes.h"
#include "rede.h"

GLfloat angle, fAspect;
int largura, altura;

            
void Desenha(void){
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//viewport da barra de sangue e informações
	fAspect = (GLfloat)largura/(GLfloat)(80);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle, fAspect, 0.4, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, altura-80, largura, 80);
	gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0);
	
	glDisable(GL_LIGHTING);
	
	//Tempo
	glPushMatrix();	
		glTranslatef(-50,-30,0);
		glScalef(0.7, 0.7, 0);
		glLineWidth(3);
		glColor3f(1, 1, 1);
		DesenhaTextoStroke(GLUT_STROKE_ROMAN, textoTempo);
	glPopMatrix();
	
	//quadrado onde fica o tempo
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
		glVertex3i(-60, -60, 0);
		glVertex3i(-60, 60, 0);
		glVertex3i(60, 60, 0);
		glVertex3i(60, -60, 0);
	glEnd();
	
	//Texto 1
	glPushMatrix();	
		glTranslatef(-85*fAspect,-60,0);
		glScalef(0.4, 0.4, 0);
		glLineWidth(2);
		glColor3f(1, 1, 0);
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"JOGADOR 1");
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(-55*fAspect,-60,0);
		glScalef(0.4, 0.4, 0);
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DesenhaTextoStroke(GLUT_STROKE_ROMAN, textoVitoria1);
	glPopMatrix();
	
	//Texto 2
	glPushMatrix();	
		glTranslatef(66*fAspect,-60,0);
		glScalef(0.4, 0.4, 0);
		glLineWidth(2);
		glColor3f(1, 1, 0);
		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"JOGADOR 2");
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(55*fAspect,-60,0);
		glScalef(0.4, 0.4, 0);
		glLineWidth(2);
		glColor3f(1, 0, 0);
		DesenhaTextoStroke(GLUT_STROKE_ROMAN, textoVitoria2);
	glPopMatrix();
	
	//barras de sangue
	glColor3f(1-1*vidaJogador1*vidaJogador1, 1*vidaJogador1*vidaJogador1, 0);
	glBegin(GL_QUADS);
		glVertex3i(-(5+80*vidaJogador1)*fAspect, 0, 0);
		glVertex3i(-(5+80*vidaJogador1)*fAspect, 60, 0);
		glVertex3i(-5*fAspect, 60, 0);
		glVertex3i(-5*fAspect, 0, 0);
	glEnd();
	glColor3f(1-1*vidaJogador2*vidaJogador2, 1*vidaJogador2*vidaJogador2, 0);
	glBegin(GL_QUADS);
		glVertex3i(5*fAspect, 0, 0);
		glVertex3i(5*fAspect, 60, 0);
		glVertex3i((5+80*vidaJogador2)*fAspect, 60, 0);
		glVertex3i((5+80*vidaJogador2)*fAspect, 0, 0);
	glEnd();
	
	//barras de especial
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
		glVertex3i(-(5+45*vidaEspecialJogador1)*fAspect, -60, 0);
		glVertex3i(-(5+45*vidaEspecialJogador1)*fAspect, -10, 0);
		glVertex3i(-5*fAspect, -10, 0);
		glVertex3i(-5*fAspect, -60, 0);
	glEnd();
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
		glVertex3i(5*fAspect, -60, 0);
		glVertex3i(5*fAspect,-10, 0);
		glVertex3i((5+45*vidaEspecialJogador2)*fAspect, -10, 0);
		glVertex3i((5+45*vidaEspecialJogador2)*fAspect, -60, 0);
	glEnd();
	
	//fundo
	glBegin(GL_QUADS);
		glColor3f(0.3, 0.3, 0.3);
		glVertex3i(-92*fAspect, -88, 0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3i(-92*fAspect, 88, 0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3i(92*fAspect, 88, 0);
		glColor3f(0.3, 0.3, 0.3);
		glVertex3i(92*fAspect, -88, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	
	//viewport da parte de baixo do jogo
	fAspect = (GLfloat)largura/(GLfloat)(altura-80);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle, fAspect, 0.4, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glViewport(0, 0, largura, altura-80);
	gluLookAt(0, 80, 300, 0, 60, 0, 0, 1, 0);
	
	//Texto de centro
	if(textoCentro == 1){
		glDisable(GL_LIGHTING);
		glPushMatrix();
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_QUADS);
				glVertex3i(-92*fAspect, 80, 0);
				glVertex3i(-92*fAspect, 120, 0);
				glVertex3i(92*fAspect, 120, 0);
				glVertex3i(92*fAspect, 80, 0);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();
		glPushMatrix();	
			glTranslatef(-100, 90, 10);
			glScalef(0.2, 0.2, 0);
			glLineWidth(15);
			glColor3f(1, 1, 0);
			DesenhaTextoStroke(GLUT_STROKE_ROMAN, texto);
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	
	//desenha todo o cenário
	cenario();
	
    //jogador 1
    glPushMatrix();
        glTranslatef(posxJogador1, posyJogador1, 0);
        glScalef(escala, escala, escala);
        glRotatef(rotacaoJogador1, 0, 1, 0);
        if(estadoJogador1 == 0) desenhaVetorTextura(jogadorNormalV, jogadorNormalT, jogadorNormalN, textura1);
        if(estadoJogador1 == 1) desenhaVetorTextura(jogadorAbaixadoV, jogadorAbaixadoT, jogadorAbaixadoN, textura1);
        if(estadoJogador1 == 2) desenhaVetorTextura(jogadorChuteFinalV, jogadorChuteFinalT, jogadorChuteFinalN, textura1);
        if(estadoJogador1 == 3) desenhaVetorTextura(jogadorChuteIntermediarioV, jogadorChuteIntermediarioT, jogadorChuteIntermediarioN, textura1);
        if(estadoJogador1 == 4) desenhaVetorTextura(jogadorSocoFinalV, jogadorSocoFinalT, jogadorSocoFinalN, textura1);
        if(estadoJogador1 == 5) desenhaVetorTextura(jogadorSocoIntermediarioV, jogadorSocoIntermediarioT, jogadorSocoIntermediarioN, textura1);
        if(estadoJogador1 == 6) desenhaVetorTextura(jogadorTomandoChuteV, jogadorTomandoChuteT, jogadorTomandoChuteN, textura1);
        if(estadoJogador1 == 7) desenhaVetorTextura(jogadorTomandoSocoV, jogadorTomandoSocoT, jogadorTomandoSocoN, textura1);
    glPopMatrix();

    //jogador 2
    glPushMatrix();
        glTranslatef(posxJogador2, posyJogador2, 0);
        glScalef(escala, escala, escala);
        glRotatef(rotacaoJogador2, 0, 1, 0);
        if(estadoJogador2 == 0) desenhaVetorTextura(jogadorNormalV, jogadorNormalT, jogadorNormalN, textura2);
        if(estadoJogador2 == 1) desenhaVetorTextura(jogadorAbaixadoV, jogadorAbaixadoT, jogadorAbaixadoN, textura2);
        if(estadoJogador2 == 2) desenhaVetorTextura(jogadorChuteFinalV, jogadorChuteFinalT, jogadorChuteFinalN, textura2);
        if(estadoJogador2 == 3) desenhaVetorTextura(jogadorChuteIntermediarioV, jogadorChuteIntermediarioT, jogadorChuteIntermediarioN, textura2);
        if(estadoJogador2 == 4) desenhaVetorTextura(jogadorSocoFinalV, jogadorSocoFinalT, jogadorSocoFinalN, textura2);
        if(estadoJogador2 == 5) desenhaVetorTextura(jogadorSocoIntermediarioV, jogadorSocoIntermediarioT, jogadorSocoIntermediarioN, textura2);
        if(estadoJogador2 == 6) desenhaVetorTextura(jogadorTomandoChuteV, jogadorTomandoChuteT, jogadorTomandoChuteN, textura2);
        if(estadoJogador2 == 7) desenhaVetorTextura(jogadorTomandoSocoV, jogadorTomandoSocoT, jogadorTomandoSocoN, textura2);
    glPopMatrix();
    
    //especial jogador 1
    if(especialJogador1 == 1){
		glPushMatrix();
			glTranslatef(posxEspecialJogador1, 120*escala, 0);
			glScalef(14*escala, 14*escala, 14*escala);
			glRotatef(-90, 0, 1, 0);
			glRotatef(-90, 1, 0, 0);
			desenhaVetorTextura(espadaV, espadaT, espadaN, espada);
		glPopMatrix();
	}
	
	//especial jogador 2
    if(especialJogador2 == 1){
		glPushMatrix();
			glTranslatef(posxEspecialJogador2, 120*escala, 0);
			glScalef(14*escala, 14*escala, 14*escala);
			glRotatef(-90, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			desenhaVetorTextura(espadaV, espadaT, espadaN, espada);
		glPopMatrix();
	}
	
	glutSwapBuffers();
}


// Inicializa parâmetros de rendering
void Inicializa (void){ 
	GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;
 	// Especifica que a cor de fundo da janela será branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    angle=33;
    carregaInit();
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	largura = w;
	altura = h;
}


void GerenciaMouse(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON)
		if(state == GLUT_DOWN) {  // Zoom-in
			//if(angle >= 10) angle -= 2;
			if(modoRede == 0) ligaRede(1);
		}
	if(button == GLUT_RIGHT_BUTTON)
		if(state == GLUT_DOWN) {  // Zoom-out
			//if(angle <= 130) angle += 2;
			if(modoRede == 0) ligaRede(2);
		}
	if(button == GLUT_MIDDLE_BUTTON)
		if(state == GLUT_DOWN) {
			modoRede = 0;
			printf("\nModo rede desligado.\n");
		}
	//glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y){
	if(modoRede == 1){
		char pos[8];
		if(jogadorSelecionado == 1){
			sprintf(pos, "%d", posxJogador1);
		}else{
			sprintf(pos, "%d", posxJogador2);
		}
		pressiona(pos);
	}
	switch(key){
		case 'd':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('d')] = 1;
					pressiona("ppd");
				}else{
					keyVet[(int)('l')] = 1;
					pressiona("ppl");
				}
			}else{
				keyVet[(int)('d')] = 1;
			}
		break;
        case 'w':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('w')] = 1;
					pressiona("ppw");
				}else{
					keyVet[(int)('i')] = 1;
					pressiona("ppi");
				}
			}else{
				keyVet[(int)('w')] = 1;
			}
		break;
		case 'a':
			if(modoRede == 1){
				char pos[8];
				if(jogadorSelecionado == 1){
					keyVet[(int)('a')] = 1;
					pressiona("ppa");
				}else{
					keyVet[(int)('j')] = 1;
					pressiona("ppj");
				}
			}else{
				keyVet[(int)('a')] = 1;
			}
		break;
		case 's':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('s')] = 1;
					pressiona("pps");
				}else{
					keyVet[(int)('k')] = 1;
					pressiona("ppk");
				}
			}else{
				keyVet[(int)('s')] = 1;
			}
		break;
		case 'j':
			if(modoRede != 1) keyVet[(int)('j')] = 1;
		break;
        case 'i':
			if(modoRede != 1) keyVet[(int)('i')] = 1;
		break;
		case 'l':
			if(modoRede != 1) keyVet[(int)('l')] = 1;
		break;
		case 'k':
			if(modoRede != 1) keyVet[(int)('k')] = 1;
		break;
		case '1':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('1')] = 1;
					pressiona("pp1");
				}else{
					keyVet[(int)('8')] = 1;
					pressiona("pp8");
				}
			}else{
				keyVet[(int)('1')] = 1;
			}
		break;
        case '2':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('2')] = 1;
					pressiona("pp2");
				}else{
					keyVet[(int)('9')] = 1;
					pressiona("pp9");
				}
			}else{
				keyVet[(int)('2')] = 1;
			}
		break;
		case '3':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					keyVet[(int)('3')] = 1;
					pressiona("pp3");
				}else{
					keyVet[(int)('0')] = 1;
					pressiona("pp0");
				}
			}else{
				keyVet[(int)('3')] = 1;
			}
		break;
		case '8': 
			if(modoRede != 1) keyVet[(int)('8')] = 1;
		break;
		case '9': 
			if(modoRede != 1) keyVet[(int)('9')] = 1;
		break;
		case '0': 
			if(modoRede != 1) keyVet[(int)('0')] = 1;
		break;
		case ' ': 
			pausaJogo();
			if(modoRede == 1) pressiona("sto");
		break;
        case 27:
			if(modoRede == 1) pressiona("exi");
			exit(0);
		break;
	}
	glutPostRedisplay();
}


void teclasEspeciais(int key, int x, int y){
	switch(key){
		case GLUT_KEY_F1:
			aceleracaoJogo -= 0.5;
			printf("Aceleracao do jogo: %f\n", aceleracaoJogo);
			if(modoRede == 1) pressiona("F1");
		break;
		case GLUT_KEY_F2: 
			aceleracaoJogo += 0.5;
			printf("Aceleracao do jogo: %f\n", aceleracaoJogo);
			if(modoRede == 1) pressiona("F2");
		break;
		case GLUT_KEY_F3: 
			escala-=0.1;
			distanciaJogadores /= 1.5;
			printf("Escala do jogo: %f\n", escala);
			if(modoRede == 1) pressiona("F3");
		break;
		case GLUT_KEY_F4: 
			escala+=0.1;
			distanciaJogadores *= 1.5;
			printf("Escala do jogo: %f\n", escala);
			if(modoRede == 1) pressiona("F4");
		break;
		case GLUT_KEY_F5: chao = carregaBMP("textura/chao0.bmp");
		break;
		case GLUT_KEY_F6: chao = carregaBMP("textura/chao1.bmp");
		break;
		case GLUT_KEY_F7: chao = carregaBMP("textura/chao2.bmp");
		break;
		case GLUT_KEY_F8: parede = carregaBMP("textura/parede0.bmp");
		break;
		case GLUT_KEY_F9: parede = carregaBMP("textura/parede1.bmp");
		break;
		case GLUT_KEY_F10: parede = carregaBMP("textura/parede2.bmp");
		break;
		case GLUT_KEY_F11: parede = carregaBMP("textura/parede3.bmp");
		break;
		case GLUT_KEY_F12: parede = carregaBMP("textura/parede4.bmp");
		break;
		case GLUT_KEY_HOME: rotacaoJogador1 += 2;
		break;
		case GLUT_KEY_END: rotacaoJogador2 += 2;
		break;
		case GLUT_KEY_PAGE_UP: mudaTexturaJogador(rand()%8, 10);
		break;
		case GLUT_KEY_PAGE_DOWN: mudaTexturaJogador(10, rand()%8);
		break;
		case GLUT_KEY_INSERT:
			reiniciaJogo();
			if(modoRede == 1) pressiona("IN");				
		break;
	}
	glutPostRedisplay();
}


void keyboardUP(unsigned char key, int x, int y){
	if(modoRede == 1){
		char pos[8];
		if(jogadorSelecionado == 1){
			sprintf(pos, "%d", posxJogador1);
		}else{
			sprintf(pos, "%d", posxJogador2);
		}
		pressiona(pos);
	}
	switch(key){
		case 'd':
			if(modoRede == 1){
				char pos[8];
				if(jogadorSelecionado == 1){
					pressiona("lld");
				}else{
					pressiona("lll");
					keyVet[(int)('l')] = 0;	
				}
			}
			keyVet[(int)('d')] = 0;	
		break;
        case 'w':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					pressiona("llw");
				}else{
					pressiona("lli");
					keyVet[(int)('i')] = 0;
				}
			}
			keyVet[(int)('w')] = 0;	
		break;
		case 'a':
			if(modoRede == 1){
				char pos[8];
				if(jogadorSelecionado == 1){
					pressiona("lla");
				}else{
					pressiona("llj");
					keyVet[(int)('j')] = 0;
				}
			}
			keyVet[(int)('a')] = 0;	
		break;
		case 's':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					pressiona("lls");
				}else{
					pressiona("llk");
					keyVet[(int)('k')] = 0;	
				}
			}
			keyVet[(int)('s')] = 0;	
		break;
		case 'j':
			keyVet[(int)('j')] = 0;
			if(modoRede == 1) pressiona("llj");
		break;
        case 'k':
			keyVet[(int)('k')] = 0;
			if(modoRede == 1) pressiona("llk");
		break;
		case 'l':
			keyVet[(int)('l')] = 0;
			if(modoRede == 1) pressiona("lll");
		break;
		case 'i':
			keyVet[(int)('i')] = 0;
			if(modoRede == 1) pressiona("lli");
		break;
		case '3':
			if(modoRede == 1){
				if(jogadorSelecionado == 1){
					pressiona("ll3");
				}else{
					pressiona("ll0");
					keyVet[(int)('0')] = 0;	
				}
			}
			keyVet[(int)('3')] = 0;	
		break;
		case '0':
			keyVet[(int)('0')] = 0;
			if(modoRede == 1) pressiona("ll0");
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[]){
	glutInit( &argc, argv );	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(1, 1);
    glutCreateWindow("CeunesFighter");
	Inicializa();
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(teclasEspeciais);
    glutKeyboardUpFunc(keyboardUP);
    glutIdleFunc(idle);
	glutMainLoop();
}
