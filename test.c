#include <stdio.h>
#include <stdlib.h>
#include "ufrn_al5d.h"

#define	TIMEDIST 500

//Posicao inicial para todos os servos
#define HOME_POS "#0P1500STIMEDIST#1P1500STIMEDIST#2P1500STIMEDIST#3P1500STIMEDIST#4P1500STIMEDIST"

void command(int servo,int angle, char* comando,int serial_fd,int *pos);

int main()
{
	int servo, angle;
	int pos[5] = {135,135,135,135,135};
	int serial_fd;
	char *comando;
	int quit = 0;
	serial_fd = abrir_porta();
	if(abrir_porta() < 0)
	{
		printf("[ERROR]:falha em abrir  porta serial /dev/ttyS0\n Finalizando o programa...");
		return -1;
	}
	else
	{

		printf("Porta serial /dev/ttyS0 aberta com sucesso\n");
	
		if(configurar_porta(serial_fd) < 0)
		{
			printf("[ERROR]: falha ao tentar configurar a porta\n");
			close(serial_fd);
			return -1;
		}

		comando = (char*) malloc(sizeof(char)*BUFSIZE);
		memset(comando, 0, BUFSIZE);
		sprintf(comando,"%s",HOME_POS);
		enviar_comando(comando,serial_fd);
		while(!(quit < 0))
		{
			memset(comando, 0, BUFSIZE);
			printf("Insira o canal do servo e o quanto em graus ele deve se mover.\n");

			printf("Ou digite '0 0' para finalizar.\n");
			scanf("%d%d",&servo,&angle);
			if((servo || angle) == 0)
			{
				quit = -1;
			}
			command(servo,angle,comando, serial_fd,&pos);
		}
		fechar_porta(serial_fd);
	}

	return 0;
}
void command(int servo, int angle, char* comando,int serial_fd, int *pos)
{
	
	int realangle;
	realangle = trava(servo,(angle/0.09) + 500);
	switch(servo)
	{
		case 0:
			pos[0] = angle;
			break;
		case 1:
			pos[1] = angle;
			break;
		case 2:
			pos[2] = angle;
			break;
		case 3:
			pos[3] = angle;
			break;
		case 4:
			pos[4] = angle;
			break;
	}
	//Escrevendo com teste de escrita
	sprintf(comando, "#%dP%dS%d",servo,realangle,TIMEDIST);
	if(enviar_comando(comando,serial_fd) > 0)
	{
		printf("Comando enviado.| [%d] | [%d] | [%d] | [%d] | [%d] |\n", pos[0],pos[1],pos[2],pos[3],pos[4]);		
	}
}
