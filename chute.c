#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 *		 -------------------------- ---
 *       |                                | | | 
 * Força Magnus = 1/2 * Cm * p * A * r * w|x|V| ------> No nosso caso, esse V seria apenas Vy, já que consideramos que a bola só vai para "frente" 
 *		 |                                | | |              
 *		 -------------------------- ---
 *		          |
 *		          |
 *		          ------> Todas variaves desse quadrado podem ser tratados como constantes
 *		          		(1 foi a constante que mais agradou no plot do grafico, podemos nos basear nisso para determinar os valores das variaveis)
 *
 * 			  Sendo a Força Magnus a força resultante no eixo X, Vx varia de acordo com a força magnus e como ela está para esquerda (regra da mao direita)
 * 			      e x cresce para direita, sabemos que vx em algum momento precisa ser negativo para a bola fazer a curva para esquerda
 * 			      (considerando que o V sempre vai ter direção para a direita/diagonal direita, caso o chute fosse no sentido contrário, haveria troca de sinais)
 *
 * 			  Portanto, para sabermos a velocidade instantanea para subtrairmos em Vx, dividimos a Fr pela massa da bola e multiplicamos por dt
 * 			  (F = [m * a] = massa * metro/segundo^2 -> F * dt / massa = [v] = metro/segundo)
 */

#define POSICAO_BARRA_LATERAL -200
#define ALTURA_BARRA 10
#define INICIO_BARRA_LATERAL 65
#define FIM_BARRA_LATERAL 85

void criar_balizas() {
	FILE* fp;
	double ds = 0.1;
	float x = POSICAO_BARRA_LATERAL, y, z;
	
	fp = fopen("baliza1.dat", "w");
	
	y = INICIO_BARRA_LATERAL; z = 0;
	/*!< Criando barra lateral esquerda */
	for(int i = 0; i < 10000; i++) {
		if(z < ALTURA_BARRA)
			z += ds;
		fprintf(fp, "%f %f %f\n", x,y,z);
	}

	fclose(fp);

	fp = fopen("baliza2.dat", "w");

	y = FIM_BARRA_LATERAL; z = 0;
	/*!< Criando barra lateral direita */
	for(int i = 0; i < 10000; i++) {
		if(z < ALTURA_BARRA)
			z += ds;
		fprintf(fp, "%f %f %f\n", x,y,z);
	}

	fclose(fp);

	fp = fopen("baliza3.dat", "w");

	y = INICIO_BARRA_LATERAL; z = ALTURA_BARRA;
	/*!< Criando barra superior */
	for(int i = 0; i < 10000; i++) {
		if(y < FIM_BARRA_LATERAL)
			y += ds;
		fprintf(fp, "%f %f %f\n", x,y,z);
	}

	fclose(fp);
} 

#define gravity	9.81
#define pi 3.141592653589793
#define mass 0.450

void criar_chute() {
	float x = 0, y = 0, z = 0, vx, vy, vz;
	double dt = 10e-3;
	FILE* fp;
	float v, theta, phi;

	printf("Entre com a velocidade do chute: ");
	scanf("%f", &v);

	printf("Entre com o angulo theta: ");
	scanf("%f", &theta);

	printf("Entre com o angulo phi: ");
	scanf("%f", &phi);

	vx = v*cos(pi*theta/180)*cos(pi*phi/180);
	vy = v*sin(pi*theta/180)*cos(pi*phi/180);
	vz = v*sin(pi*phi/180);

	fp = fopen("chute.dat", "w");

	int fezGol = 0;
	for (int i = 0; i<10000; i++){
		/*! A Força Magnus ficou apenas 1 * V considerando tudo constante */
		vx = vx - ((1 * vy) / mass * dt);
		x = vx*dt + x;
		y = vy*dt + y;
		if(z>0)
			vz = vz -gravity*dt;
		z  = vz*dt + z;

		if(x <= POSICAO_BARRA_LATERAL && y >= INICIO_BARRA_LATERAL && y <= FIM_BARRA_LATERAL && z <= ALTURA_BARRA && !fezGol) {
			fezGol = 1;
			printf("\nGOOOOOOOOOOOOOOOOOOOOOOOOL DO ROBERTINHO!\n");
		}

		if(z < 0)
			break;

		fprintf(fp, "%f %f %f\n", x,y,z);
	}

	if(!fezGol) {
		printf("\nVocê errou o chute! O Brasil perdeu de 3 x 0 para Tchecoslováquia.\n");
	}

	fclose(fp);
}

int main(void) {

	criar_chute();
	criar_balizas();
	
	return 0;
}