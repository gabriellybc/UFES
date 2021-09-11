#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void soma(float n1, float n2, float *a)
{
	*a=n1+n2;
}
void sub(float n1, float n2, float *a)
{
	*a=n1-n2;
}
void multi(float n1, float n2, float *a)
{
	*a=n1*n2;
}
void divi(float n1, float n2, float *a)
{
	*a=n1/n2;
}
void fatorial(float n1,float *a)
{
	int i,mul=1;
	for(i=1;i<=n1;i++)
	{
		mul=mul*i;
	}
	*a=mul;
	if(n1==0)
	{
		*a=1;
	}
}
void potencia(float n1,float n2, float *a) //tá ruim
{
	int i;
	float multi=1;
	for(i=0;i<n2;i++)
	{
		multi=multi*n1;
		printf("Multiplicação=%f\n",multi);
	}
	*a=multi;
	if(n2==0)
	{
		*a=1;
	}
}
void raiz(int ind, int rad, int *r)
{
	int i,j,s;
	if(ind!=0)
	{
		if(ind>0)
		{
			if(rad>0)
			{
				s=1;
				for(i=1;i<=rad;i++)  //vai aumentar o valor do número que pode ser raiz (i)
				{
					for(j=1;j<=ind;j++) //multiplica o i a quantidade de vezes que for o índice dado
					{
						s=s*i;
					}
					if(s==rad)
					{
						*r=i;
					}
					s=1;
				}
			}
			if(rad<0&&(ind%2)==0)
			{
				printf("Math ERROR\n");
				*r=100000;
			}
			if(rad<0&&(ind%2)!=0)
			{
				s=1;
				rad=-rad;
				for(i=1;i<=rad;i++)  //vai aumentando o valor do número que pode ser raiz (i)
				{
					for(j=1;j<=ind;j++) //multiplica o i a quantidade de vezes que for o índice dado
					{
						s=s*i;
					}
					if(s==rad)
					{
						*r=-i;
					}
					s=1;
				}
			}
		}
		if(ind<0)
		{
			ind=-ind;
			if(rad>0)
			{
				s=1;
				for(i=1;i<=rad;i++)  //vai aumentar o valor do número que pode ser raiz (i)
				{
					for(j=1;j<=ind;j++) //multiplica o i a quantidade de vezes que for o índice dado
					{
						s=s*i;
					}
					if(s==rad)
					{
						*r=-i;
					}
					s=1;
				}
			}
			if(rad<0&&(ind%2)==0)
			{
				printf("Math ERROR\n");
				*r=1000000;
			}
			if(rad<0&&(ind%2)!=0)
			{
				s=1;
				rad=-rad;
				for(i=1;i<=rad;i++)  //vai aumentando o valor do número que pode ser raiz (i)
				{
					for(j=1;j<=ind;j++) //multiplica o i a quantidade de vezes que for o índice dado
					{
						s=s*i;
					}
					if(s==rad)
					{
						*r=i;
					}
					s=1;
				}
			}
		}
	}
	else //índice igual a zero
	{
		printf("Math ERROR\n");
		*r=100000;
	}
}
void divisores(int n1, int i)
{
   for(i=1;i<=n1;i++)
   {
      if((n1%i)==0)
      {
         printf("%d\n", i);
      }
   }
}
float subst(float A, float B, float C)
{
	int i;
	float x;
	printf("\t1 - Escolher um novo número\n");
	printf("\t2 - A(%f)\n",A);
	printf("\t3 - B(%f)\n",B);
	printf("\t4 - C(%f)\n",C);
	scanf("%d",&i);
	printf("\n");
	while(i<1||i>4)
	{
		if(i==0)
		{
			return 0;
		}
		printf("Opção inválida. Escolha uma opção para que não possa ter valor\n");
		printf("\t1 - Escolher um novo número\n");
		printf("\t2 - A(%f)\n",A);
		printf("\t3 - B(%f)\n",B);
		printf("\t4 - C(%f)\n",C);
		scanf("%d",&i);
		printf("\n");
	}
	switch(i)
	{
		case 1:
			printf("n=");
			scanf("%f",&x);
			return x;
			break;
		case 2:
			return A;
			break;
		case 3:
			return B;
			break;
		case 4:
			return C;
			break;
	}
}
//DIVISÓRIA ENTRE FUNÇÕES DE MATRIZES E FUNÇÕES NORMAIS
void trocalinha(float *L1, float *L2, int b)
{
	int i,aux[b];
	for(i=0;i<b;i++) //o for serve para ir trocando os valores de cada coluna
	{
		aux[i]=*L1;
		*L1=*L2;
		*L2=aux[i];
		L1++;
		L2++;
	}
}
void multilinha(float *L1,float c, int b)
{
	int i,j,aux;
	for(i=0;i<b;i++)
	{
		aux=*L1;
		aux=aux*c;
		*L1=aux;
		L1++;
	}
}
void divlinha(float *L1,float c, int b)
{
	int i;
	float aux;
	for(i=0;i<b;i++)
	{
		aux=*L1;
		aux=aux/c;
		*L1=aux;
		L1++;
	}
}
void zerador(float *L1, float *L2,float c, int b) // zera o q ta embaixo da coluna pivo
{   // float c é para saber o valor da col embaixo da pivô
	int i;
	divlinha(L2,c,b);
	for(i=0;i<b;i++)
	{
		*L2=*L2-*L1;
		L1++;
		L2++;
	}
}
void zerador2(float *L1,float *L2, float c, int b) // zera oq ta em cima da coluna pivo
{
	int i;
	multilinha(L1,c,b); // pra zerar oq ta em cima sem mudar os pivos das outras linhas, aí multiplica a linha msm
	for(i=0;i<b;i++)
	{
		*L2=*L2-*L1;
		L1++;
		L2++;
	}
}
void imprimirmatriz(float *mat,int a, int b)
{
	int i,j;
	for(i=0;i<a;i++)
	{
		for(j=0;j<b;j++)
		{
			printf("%.2f\t",*mat);
			mat++;
		}
		printf("\n");
	}
}
void scanmatriz(float *mat, int a, int b)
{
	int i,j;
	for(i=0;i<a;i++)
	{
		printf("Escolha os números da linha %d\n",i+1);
		for(j=0;j<b;j++)
		{
			scanf("%f",mat);
			mat++;
		}
		printf("\n");
	}
}
void somamatriz(float *A1, float *B1,float *C1, int lin, int col)
{
    int i,termos;
    termos=lin*col;
    for(i=0;i<termos;i++)
    {
		*C1=*A1+*B1;
    	A1++;
    	B1++;
    	C1++;
	}
}
void subtrailinhas(float *A1, float *B1, float *C1, int lin, int col)
{
    int i,termos;
    termos=lin*col;
    for(i=0;i<termos;i++)
    {
		*C1=*A1-*B1;
    	A1++;
    	B1++;
    	C1++;
	}
}
void multimatriz(int la, int ca, int lb, int cb)
{
    int i=0,j=0,x=0;
    float A[la][ca],B[lb][cb],C[ca][lb];
    printf("Matriz A:\n");
    scanmatriz(&A[0][0],la,ca);
    printf("Matriz B:\n");
    scanmatriz(&B[0][0],lb,cb);
    for(i=0;i<ca;i++)
    {
        for(j=0;j<lb;j++)
        {
            C[i][j]=0;
        }
    }
    for(i=0;i<la;i++)
    {
        for(j=0;j<cb;j++)
        {
            for(x=0;x<lb;x++)
            {
                C[i][j]+=A[i][x]*B[x][j];
            }
        }
    }
    printf("Resultado:\n");
    for(i=0;i<ca;i++)
    {
        for(j=0;j<lb;j++)
        {
            printf("%6.f", C[i][j]);
        }
        printf("\n\n");
    }
}
void multiescalar(float *A,float *C, float k, int lin, int col)
{
	float x;
	int i,termos;
	termos = lin*col;
	for(i=0;i<termos;i++)
	{
		x=*A;
		x=x*k;
		*C=x;
		A++;
		C++;
	}
}
void salvarmatriz(float *mat, int a, int b)
{
	FILE *pont;
	int i,j;
	pont = fopen("matrizes.txt","w");
	for(i=0;i<a;i++)
	{
		for(j=0;j<b;j++)
		{
			fprintf(pont,"%.2f\t",*mat);
			mat++;
		}
		fprintf(pont,"\n");
	}
	fclose (pont);
	printf("Matriz salva com sucesso!");
}

void salvar(float *mat, int a, int b)
{
	int k;
	printf ("Deseja salvar a matriz em um arquivo para usar depois ou ver ela?\nDigite: \n");
	printf ("1- Salvar em arquivo. Obs: apenas uma matriz ficara salva por vez.\n");
	printf ("2- Não\n");
	scanf ("%d", &k);
	if (k==1)
	{
		salvarmatriz(mat, a, b);
	}
}
// calculadora rapida aqui.
float poten(int o, int p) // outra função de potencia pq essa é de inteiro
{
	int i=0;
	float resul=1;
	while(i<p)
	{
		resul=resul*o;
		i++;
	}
	return resul;
}
float calculadora(char *hehe,int *ativa)
{
	int i=0,op,ta=0,tb=0,count=0;
	int a[100],b[100];
	float n1=0, n2=0;
	float resul;
	for(i=0;hehe[i]<58 && hehe[i]>47;i++)
	{
		a[i]=hehe[i]-48;
		ta++;
	}
	if(hehe[i]=='+') op=0;
	else if(hehe[i]=='-') op=1;
	else if(hehe[i]=='*') op=2;
	else if(hehe[i]=='/') op=3;
	i++;
	while(hehe[i]<58 && hehe[i]>47)
	{
		b[count]=hehe[i]-48;
		tb++;
		i++;
		count++;
	}
	ta--;
	tb--;
	i=0;
	while(ta>=0) // transformando em numero
	{
		n1=n1+(a[i]*poten(10,ta));
		ta--;
		i++;
	}
	i=0;
	while(tb>=0) // transformando em numero
	{
		n2=n2+(b[i]*poten(10,tb));
		tb--;
		i++;
	}
	if (op==0) resul=n1+n2;
	else if(op==1) resul= n1-n2;
	else if(op==2) resul= n1*n2;
	else if(op==3)
	{
		if(n2==0)
		{
			*ativa=0;
			return 0;
		}
		resul= n1/n2;
	}
	return resul;
}
void feedback(char *coment)
{
	FILE *pont;
	pont = fopen("feedback.txt","a");
	fprintf (pont,"%s",coment);
	fclose (pont);
	printf("\nFeedback registrado com sucesso!\n");
}


void mainmenu()
{
	printf("Escolha o número da opção que deseja realizar:\n");
	printf("1 - Calculadora de Escalares\n");
	printf("2 - Calculadora de Matriz\n");
	printf("3 - Calculadora rápida\n");
	printf("4 - Dar feedback\n");
	printf("0 - Fechar\n");
}
void menu1()
{
	printf("Escolha a função da calculadora que desejar:\n");
	printf("1 - Soma\n");
	printf("2 - Subtração\n");
	printf("3 - Multiplicação\n");
	printf("4 - Divisão\n");
	printf("5 - Fatorial\n");
	printf("6 - Potêcia\n");
	printf("7 - Radiciação (somente números inteiros)\n");
	printf("8 - Divisores\n");
	printf("0 - Voltar para o menu principal\n");
}
void menu2()
{
	printf("Escolha a função da calculadora que desejar:\n");
	printf("1 - Soma de matrizes\n");
	printf("2 - Subtração de matrizes\n");
	printf("3 - Multiplicação de matrizes\n");
	printf("4 - Multiplicação por escalar\n");
	printf("5 - Achar determinante\n");
	printf("6 - Escalonamento reduzido\n");
	printf("0 - Voltar para o menu principal\n");
}
void menu3() //(menu escrever o que você quer por extenso)
{
	printf("Somente operações básicas(adição, subtração, multiplicação e divisão) com números inteiros podem ser realizadas.\n");
	printf("Para adição escreva numero1+numero2 \n");
	printf("Para subtração escreva numero1-numero2 \n");
	printf("Para multiplicação escreva numero1*numero2 \n");
	printf("Para divisão escreva numero1/numero2 \n");
	printf("Para voltar para o menu principal divida qualquer numero por zero.\n");
}
void menu4() //(menu feedback)
{
	printf("Digite seu feedback:\n");
}
int main()
{
	int i,j,m=777,m1=777,m2=777,m3=777;
	float A=0,B=0,C=0,D=0,E=0;
	start:
	mainmenu();
	scanf("%d",&m);
	while(m<0||m>4)
	{
		printf("Opção inválida. Tente novamente\n");
		mainmenu();
		scanf("%d",&m);
	}
	switch(m)
	{
		case 1:
		{
			int dec;
			float n1,n2,x;
			while(m1!=0)
			{
				menu1();
				scanf("%d",&m1);
				if(m1==0)
				{
					goto start;
				}
				while(m1<0 || m1>7)
				{
					printf("Opção inválida. Tente novamente\n");
					menu1();
					scanf("%d",&m1);
					if(m1==0)
					{
						goto start;
					}
				}
				printf("\n");
				switch(m1) //menu que abre quando escolhe a opção 1 no menu principal
				{
					case 1:
						printf("Soma: n1+n2=x\n");
						printf("Escolha n1\n");
						n1=subst(A,B,C);
						printf("Escolha n2:\n");
						n2=subst(A,B,C);
						soma(n1,n2,&x);
						break;
					case 2:
						printf("Subtração: n1-n2=x\n");
						printf("Escolha n1\n");
						n1=subst(A,B,C);
						printf("Escolha n2:\n");
						n2=subst(A,B,C);
						sub(n1,n2,&x);
						break;
					case 3:
						printf("Multiplicação: n1*n2=x\n");
						printf("Escolha n1\n");
						n1=subst(A,B,C);
						printf("Escolha n2:\n");
						n2=subst(A,B,C);
						multi(n1,n2,&x);
						break;
					case 4:
						printf("Divisão: n1/n2=x\n");
						printf("Escolha n1\n");
						n1=subst(A,B,C);
						printf("Escolha n2:\n");
						n2=subst(A,B,C);
						divi(n1,n2,&x);
						break;
					case 5:
						printf("Fatorial: n1!=x\n\n");
						printf("Escolha n1:\n");
						n1=subst(A,B,C);
						fatorial(n1,&x);
						break;
					case 6:
						printf("Potenciação: n1^n2=x\n");
						printf("n1= ");
						scanf("%d",&n1);
						printf("\nn2= ");
						scanf("%d",&n2);
						potencia(n1,n2,&x);
						break;
					case 7:
						printf("Radiciação: n1^(1/n2)=x\n");
						printf("Escolha n1\n");
						n1=subst(A,B,C);
						printf("Escolha n2:\n");
						n2=subst(A,B,C);
						potencia(n1,n2,&x);
						break;
					case 8:
					{
					    int n1=0;
						printf("Divisores de n1:\n");
						printf("Escolha n1\n");
						scanf("%d", &n1);
						divisores(n1,1);
						break;
					}
				}
				printf("x= %.2f\n",x);
				printf("Salve a resposta em uma das variáveis para ser usada no futuro\n");
				printf("Digite 1 se quer salvar\n");
				printf("Digite um caractere diferente de 1 se não quer salvar\n");
				scanf("%d",&dec); //decisao
				if(dec==1)
				{
					printf("Escolha a letra onde a resposta estará salva\n");
					printf("1 - A\n");
					printf("2 - B\n");
					printf("3 - C\n");
					scanf("%d",&dec);
					switch (dec)
					{
						case 1:
							A=x;
							printf("A tem o valor de %f\n",A);
							break;
						case 2:
							B=x;
							printf("B tem o valor de %f\n",B);
							break;
						case 3:
							C=x;
							printf("C tem o valor de %f\n",C);
							break;
					}
				}
			}
			break;
		}
		case 2:
		{
			while(m2!=0)
			{
				menu2();
				scanf("%d",&m2);
				if(m2==0)
				{
					goto start;
				}
				while(m2<0 || m2>6)
				{
					printf("Opção inválida. Tente novamente\n");
					menu2();
					scanf("%d",&m2);
					if(m2==0)
					{
						goto start;
					}
				}
				switch(m2) //menu que abre quando escolhe opção 2 no menu principal
				{
					case 1:
					{
						printf("Soma de matrizes\n");
						printf("Será feita a operação [A]+[B]=[C]\n");
						int m,n;
						printf ("Digite o número de linhas de [A] e [B]:\n");
						scanf ("%d",&m);
						printf ("\nDigite o número de colunas de [A] e [B]:\n");
						scanf ("%d",&n);
						float A[m][n],B[m][n],C[m][n];
						printf("Digite os valores de [A]\n");
						scanmatriz(&A[0][0],m,n);
						printf("\nDigite os valores de [B]\n");
						scanmatriz(&B[0][0],m,n);
						somamatriz(&A[0][0],&B[0][0],&C[0][0],m,n);
						imprimirmatriz(&C[0][0],m,n);
						salvar(&C[0][0], m, n);
						break;
					}
					case 2:
					{
						printf("Subtração de matrizes\n");
						printf("Será feita a operação [A]-[B]=[C]\n");
						int m,n;
		                printf("Digite o número de linhas de [A] e [B]:\n");
		                scanf("%d",&m);
						printf ("\nDigite o número de colunas de [A] e [B]:\n");
		                scanf("%d",&n);
		            	float A[m][n],B[m][n],C[m][n];
						printf("Digite os valores de [A]\n");
						scanmatriz(&A[0][0],m,n);
		                printf("\nDigite os valores de [B]\n");
						scanmatriz(&B[0][0],m,n);
		                subtrailinhas(&A[0][0],&B[0][0],&C[0][0],m,n);
		                imprimirmatriz(&C[0][0],m,n);
		                salvar(&C[0][0], m, n);
						break;
					}
					case 3:
					{
						int la,ca,lb,cb;
	                    printf("Multiplicação de matrizes\n");
	                    printf("Quantidade de linhas da matriz A:\n");
	                    scanf("%d",&la);
	                    printf("Quantidade de colunas da matriz A:\n");
	                    scanf("%d",&ca);
	                    printf("Quantidade de linhas da matriz B:\n");
	                    scanf("%d",&lb);
	                    printf("Quantidade de colunas da matriz B:\n");
	                    scanf("%d",&cb);
	                    if(ca==lb)
	                    {
	                        multimatriz(la,ca,lb,cb);
	                    }
	                    else
	                    {
	                        printf("Não há como multiplicar as matrizes dadas. Tente novamente.\n");
	                    }
						break;
					}
					case 4:
					{
						printf("Multiplicação por escalar\n");
						printf("Será feita a operação [A]*k=[C]\n");
						int m,n;
		                printf("Digite o número de linhas de [A]:\n");
		                scanf("%d",&m);
						printf ("\nDigite o número de colunas de [A]:\n");
		                scanf("%d",&n);
		               float A[m][n],C[m][n],k;
						printf("Digite os valores de [A]\n");
						scanmatriz(&A[0][0],m,n);
		                printf("Digite o numero que vai multiplicar a matriz: ");
		                scanf("%f",&k);
		                multiescalar(&A[0][0],&C[0][0],k,m,n);
		                imprimirmatriz(&C[0][0],m,n);
		                salvar(&C[0][0], m, n);
						break;
					}
					case 5:
					{
						printf("Achar determinante\n");
						int i,a,b,xa,li,co,h,d=0,t=1;
	                    float aux,determinante=1,det[1000];
	                    printf("Digite o número de linhas da matriz:\n");
	                    scanf("%d",&a);
	                    printf("Digite o número de colunas da matriz:\n");
	                    scanf("%d",&b);
	                    float A[a][b];
	                    printf("\nDigite os números da matriz:\n");
	                    scanmatriz(&A[0][0],a,b);
	                    co=0;
	                    printf("\n");
	                    for(li=0;li<a;li++)
	                    {
		                    while(co<b && li<a)
		                    {
			                    h=0;
			                    xa=a-1;
			                    for(i=li;i<xa;i++) //trocando linhas da matriz
			                    {
				                    if(A[i][co]==0) //colocando 0 embaixo
				                    {
					                    //printf("entrei no trocador\n");
					                    trocalinha(&A[i][0],&A[xa][0],b);
				                        //imprimirmatriz(&A[0][0],a,b);
					                    t=-1*t;
					                    xa--;
					                    i--;
				                    }
			                    }
			                    if(A[li][co]!=0) //condição necessária para q não divida por 0.
	                 			{ //NÃO chega aqui sempre q uma coluna NÃO tiver pivô
				                    det[d]=A[li][co];
				                    d++;
				                    divlinha(&A[li][0],A[li][co],b);//divide a linha q tem col pivô para q o pivô fique 1
				                    h=1;
			                    }

			                    for(i=li+1;i<a && A[li][co]!=0;i++) //sem coluna pivô só passa reto man.
			                    {
				                    if(A[i][co]!=0) //não precisa zerar se ja ta zerado né. caso tente zerar irá dividir por 0, gerando um erro
				                    {
					                    //printf("entrei no zerador1\n");
					                    det[d]=A[i][co];
					                    d++;
					                    zerador(&A[li][0],&A[i][0],A[i][co],b); //zera o q ta embaixo do pivô
					                    //imprimirmatriz(&A[0][0],a,b);
				                    }
			                    }
			                    for(i=li-1;i>=0 && A[li][co]!=0;i--)
			                    {
				                    if(A[i][co]!=0) //não precisa zerar se ja ta zerado né. caso tente zerar ira multiplicar uma linha por 0, perdendo o progresso feito.
				                    {
					                    aux=A[i][co];
					                    zerador2(&A[li][0],&A[i][0],aux,b);
					                    divlinha(&A[li][0],aux,b);
				                    }
			                    }
			                    if(h==1) //se tem coluna pivô(h=1), nessa linha n pode ter mais pivô.
			                    {
				                    li++;
			                    }
			                    co++;
		                    }
	                    }
	                    for(i=0;i<d;i++)
	                    {
		                    determinante=determinante*det[i];
	                    }
	                    printf("\nDeterminante=%.2f\n",determinante*t);
						break;
					}
					case 6:
					{
						printf("Escalonamento reduzido\n");
						int i,a,b,xa,li,co,h;
		                float aux;
		                printf("Digite o número de linhas da matriz:\n");
		                scanf("%d",&a);
		                printf("Digite o número de colunas da matriz:\n");
		                scanf("%d",&b);
		                float A[a][b];
		                printf("\nDigite os números da matriz:\n");
		                scanmatriz(&A[0][0],a,b);
		                co=0;
		                printf("\n");
		                for(li=0;li<a;li++)
		                {
			                while(co<b && li<a)
			                {
				                h=0;
				                xa=a-1;
				                for(i=li;i<xa;i++)
				                {
					                if(A[i][co]==0)
					                {
						                trocalinha(&A[i][0],&A[xa][0],b);
						                xa--;
						                i--;
					                }
				                }
				                if(A[li][co]!=0)
	                 			{
					                divlinha(&A[li][0],A[li][co],b);
					                h=1;
				                }

				                for(i=li+1;i<a && A[li][co]!=0;i++)
				                {
					                if(A[i][co]!=0)
					                {
						                zerador(&A[li][0],&A[i][0],A[i][co],b);
					                }
				                }
				                for(i=li-1;i>=0 && A[li][co]!=0;i--)
				                {
					                if(A[i][co]!=0)
					                {
						                aux=A[i][co];
						                zerador2(&A[li][0],&A[i][0],aux,b);
						                divlinha(&A[li][0],aux,b);
					                }
				                }
				                if(h==1)
				                {
					                li++;
				                }
				                co++;
			                }
		                }
		                printf("\nResultado:\n");
		                imprimirmatriz(&A[0][0],a,b);
						break;
					}
				}
			}
			break;
		}
		case 3:
		{
			int ativador=1;
			char conta[40]="oi";
			float resultado=3;
			menu3();
			while(ativador==1)
			{
				scanf("%s",conta);
				resultado=calculadora(conta,&ativador);
				if(ativador==0)
				{
					goto start;
				}
				printf("%.2f\n",resultado);
			}
			break;
		}
		case 4:
		{
			char comentario[10000];
			menu4();
			scanf("%s", comentario);//o gets nao tava dando certo, ai tem que usar o fgets com o stdin que significa que ta pegando do teclado
			feedback(&comentario[0]);
			printf ("\nObrigado pelo comentario.\n");
			goto start;
			break;
		}
	}
}
