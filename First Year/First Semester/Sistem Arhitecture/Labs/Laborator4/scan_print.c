#include <stdio.h>
#include <string.h>

long grupa;
int nota;
char nume[100];

int main()
{
	scanf("%ld %d",&grupa,&nota);
	scanf("%s",nume);
	//gets(nume);
	//fgets(nume,100,stdin);
	//nume[strlen(nume)-1]=0;
	printf("Studentul %s de la grupa %ld a obtinut nota %d\n",nume,grupa,nota);
	return 0;
}
