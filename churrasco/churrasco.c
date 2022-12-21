//ALUNOS: FULVIO, JOAO PEDRO, MARCO ANTONIO

//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//VALOR MAXIMO DE PARTICIPANTES
#define MAX 60

//MAIUSCULA
void maiusculas(char *texto){
	int i; 	
	for(i=0; i<strlen(texto); i++){ 
		texto[i] = toupper(texto[i]);
	}
}

//CALCULAR IDADE
int calculaIdade(int dN, int mN, int aN){
	int idade; 		
	int dA, mA, aA;	
	time_t tempo;	
	
	tempo = time(NULL);			
	struct tm tempoAtual = *localtime(&tempo);
	dA = tempoAtual.tm_mday;	
	mA = tempoAtual.tm_mon + 1;						
	aA = tempoAtual.tm_year + 1900;	
	
	idade = aA - aN;
	if(mA < mN) idade--;
	else if ((mA == mN) && (dA < dN)) idade--;
	
	return idade;
} 

//DECLARACAO DE VARIAVEIS
	typedef struct {
		char nome[50];
		int dN;
		int mN;
		int aN;
	} Participantes;
	Participantes part[MAX];
	
	FILE *ArqPart;
	FILE *ArqPrec;
	
	float precop[9], preco_total = 0, qcarne, qling, qrefri, qsalg, qtom, qceb, qsalf, qlim, qpao, qcarv;
	int dN, mN, aN, cont=0, opcao =-1, i=0;
	char c, aux[50];
	
	
main(){
	
	//ABERTURA DOS ARQUIVOS PARA LEITURA
	ArqPart = fopen("participantes.dat", "rb");
	ArqPrec = fopen("precos.dat", "rb");
	
	if(ArqPart == NULL || ArqPrec == NULL){
		printf("\n Houve um erro ao abrir o arquivo.");
	} else{
		//ATRIBUINDO VALORES DO ARQUIVO PARA O STRUCT DOS PARTICIPANTES
		while(!feof(ArqPart)){
			fgets(aux, sizeof aux, ArqPart);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			strcpy(part[cont].nome, aux);	
			fgets(aux, sizeof aux, ArqPart);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			part[cont].dN = atoi(aux);
			fgets(aux, sizeof aux, ArqPart);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			part[cont].mN = atoi(aux);
			fgets(aux, sizeof aux, ArqPart);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			part[cont].aN = atoi(aux);
			cont++;
		}
		cont--;
		//ATRIBUINDO VALORES DO ARQUIVO PARA O VETOR DOS PRECOS DOS PRODUTOS
		while(!feof(ArqPrec)){
			fgets(aux, sizeof aux, ArqPrec);
			aux[strlen(aux)-1] = aux[strlen(aux)];
			precop[i] = atoi(aux);
			i++;
		}
		//FECHANDO OS ARQUIVOS
		fclose(ArqPart);
		fclose(ArqPrec);
	}
	
	//CRIACAO DO MENU PARA NAVEGACAO NO PROGRAMA
	while (opcao !=0){
		system ("cls");
		printf ("\n     ----->  GERENCIADOR DE CHURRASCO  <-----");
		printf("\n\n\n");
		printf (" Opcoes:");
		printf ("\n\n 1 - Cadastrar participante");
		printf ("\n 2 - Quantidade de participantes cadastrados");
		printf ("\n 3 - Lista de participantes do churrasco");
		printf ("\n 4 - Remover participante");
		printf ("\n 5 - Cadastrar preco dos produtos");
		printf ("\n 6 - Lista de produtos necessarios para o churrasco e precos");
		printf ("\n 7 - Calcular preco total do churrasco");
		printf ("\n 8 - Salvar o programa");
		printf ("\n 0 - Fechar o programa e salvar");
		printf ("\n\n Digite a opcao desejada: ");
		scanf (" %i", &opcao);
		
		switch(opcao){
			
			//CADASTRAR PARTICIPANTE
			case 1 :
				system("cls");
				fflush(stdin);
				printf("\n		- Cadrastro de participante -");
				printf("\n\n\n");
				if(cont == MAX){
					printf("Cadastro negado, lista lotada!");
				}
				else{
					printf(" Nome: ");
					gets(part[cont].nome);
					printf(" Dia de nascimento: ");
					scanf("%d", &part[cont].dN);
					printf(" Mes de nascimento: ");
					scanf("%d", &part[cont].mN);
					printf(" Ano de nascimento: ");
					scanf("%d", &part[cont].aN);
					cont++;
					printf("\n Cadastro realizado com sucesso!\n");
				}
					printf("\n\n\n");
					system ("pause");
			break;
			
			//NUMERO DE PARTICIPANTES
			case 2 :
				system("cls");
				fflush(stdin);
				printf("\n		- Numero de Participantes -");
				printf("\n\n\n");
				printf (" O numero de participantes cadastrados eh: %i", cont);
				printf("\n\n\n");
				system ("pause");
			break;
			
			//LISTAR PARTCIPIPANTES
			case 3 :
				system("cls");
				fflush(stdin);
				printf("\n		- Lista de participantes -");
				printf("\n\n\n");
				if(cont==0){
					printf(" Nenhum participante cadastrado");
				}else{
					for(i=0; i<cont; i++){
						maiusculas(part[i].nome);
						printf("\n %i -> Nome: %s - Idade: %d", i+1, part[i].nome, calculaIdade(part[i].dN, part[i].mN, part[i].aN) );
					}
				}
				printf("\n\n\n");
				system ("pause");
			break;
			
			//EXLUIR PARTICIPANTE
			case 4 :
				system("cls");
				fflush(stdin);
				i = 0;
				int posicao;
				printf("\n		- Excluir participante -");
				printf("\n\n\n");
				printf ("\n Numero do participante : ");
				scanf ("%d", &posicao);
				for(i=posicao; i<cont ; i++){
					part[i-1] = part[i];
				}
				cont--;
				printf("\n\n\n");
				system ("pause");
			break;
			
			//PRECO PRODUTOS
			case 5 :
				system("cls");
				fflush(stdin);
				printf("\n		- Cadastro preco dos produtos -");
				printf("\n\n\n");
				printf("Carne (kg):");			scanf("%f", &precop[0]);
				printf("Linguica (kg):");		scanf("%f", &precop[1]);
				printf("Refrigerante (2L):");	scanf("%f", &precop[2]);
				printf("Salgrosso (saco):");	scanf("%f", &precop[3]);
				printf("Tomate (kg):");			scanf("%f", &precop[4]);
				printf("Cebola (kg):");			scanf("%f", &precop[5]);
				printf("Salfino (saco):");		scanf("%f", &precop[6]);
				printf("Limao (kg):");			scanf("%f", &precop[7]);
				printf("Pao (kg):");			scanf("%f", &precop[8]);
				printf("Carvao (saco):");		scanf("%f", &precop[9]);
				printf("\n\n\n");	
				system("pause");
			break;
			
			//MOSTRAR PRECOS E QUANTIDADE
			case 6 :
				system("cls");
				fflush(stdin);
				printf("\n		- Preco cadastrado e quantidade necessaria -");
				printf("\n\n\n");
					//DEFININDO QUANTIDADE DE CADA PRODUTO
					qcarne=(0.3*cont) ; qling=(0.1*cont) ; qrefri=ceil(0.5*cont) ; qsalg=ceil(0.02*cont) ; qtom=(0.05*cont);
					qceb=0.015*cont; qsalf=ceil(0.002*cont) ; qlim=(0.05*cont) ; qpao=(0.075*cont) ; qcarv=ceil(0.1*cont);
					
				printf("\n Carne: R$ %.2f 			|  Quantidade : %.3f kg", precop[0], qcarne);//Utilizando os dados enviados para calcular a quantidade total de cada produto
				printf("\n Linguica: R$ %.2f  			|  Quantidade : %.3f kg", precop[0], qling);
				printf("\n Refrigerante: R$ %.2f	 		|  Quantidade : %1.f unid(2L)", precop[0], qrefri );
				printf("\n Salgrosso: R$ %.2f  			|  Quantidade : %1.f unid", precop[0], qsalg);
				printf("\n Tomate: R$ %.2f  			|  Quantidade : %.3f kg", precop[0], qtom);
				printf("\n Cebola: R$ %.2f  			|  Quantidade : %.3f kg", precop[0], qceb);
				printf("\n Salfino: R$ %.2f  			|  Quantidade : %1.f unid ", precop[0], qsalf);
				printf("\n Limao: R$ %.2f  			|  Quantidade : %.3f kg", precop[0], qlim);
				printf("\n Pao: R$ %.2f   			|  Quantidade : %.3f kg ", precop[0], qpao);
				printf("\n Carvao: R$ %.2f  			|  Quantidade : %1.f unid", precop[0], qcarv);
				printf("\n\n\n");
				system("pause");
			break;
			
			//CUSTO TOTAL E POR PARTICIPANTE
			case 7 :
				system("cls");
				fflush(stdin);
				printf("\n		- Custo total e individual -");
				printf("\n\n\n");
					//DEFININDO O VALOR TOTAL
					preco_total = (precop[0]*qcarne) + (precop[1]*qling) + (precop[2]*qrefri) + 
					(precop[3]*qsalg) + (precop[4]*qtom) + (precop[5]*qceb)+ (precop[6]*qsalf) + 
					(precop[7]*qlim) + (precop[8]*qpao) + (precop[9]*qcarv);
					preco_total = preco_total*1.08;
				
				printf("\n Valor total: R$ %.2f \n", preco_total);
				printf("\n Valor individual: R$ %.2f", preco_total/cont);
				printf("\n\n\n");
				system("pause");
			break;
			
			//SALVAR
			case 8 :
				system("cls");
				fflush(stdin);
				printf("\n		- Salvar o arquivo -");
				printf("\n\n\n");
				printf(" Arquivo salvo!");
				ArqPart = fopen("participantes.dat", "wb");
				ArqPrec = fopen("precos.dat", "wb");
				i=0;
					for(i=0; i<cont; i++){
                        fwrite(part[i].nome, sizeof(char), 10, ArqPart);
					}
				i=0;
					for(i=0; i<10; i++){
						fprintf(ArqPrec, "%.2f\n", precop[i]);
					}
				fclose(ArqPrec);
				fclose(ArqPart);
				printf("\n\n\n");
				system("pause");
			break;
			
			//FECHAR E SALVAR	
			case 0:
				system("cls");
				fflush(stdin);
				printf("\n		- Fechar o programa -");
				printf("\n\n\n");
				ArqPart = fopen("participantes.dat", "wb");
				ArqPrec = fopen("precos.dat", "wb");
				i=0;
					for(i=0; i<cont; i++){
                        fwrite(part[i].nome, sizeof(char), 10, ArqPart);
					}
				i=0;
					for(i=0; i<10; i++){
						fprintf(ArqPrec, "%.2f\n", precop[i]);
					}
				fclose(ArqPrec);
				fclose(ArqPart);
				printf(" Programa encerrado!");
				printf("\n\n\n");
				system("pause");
			break;
			
			//OPCAO INVALIDA
			default:
				system("cls");
				printf("Opcao invalida!\n");
				system("pause");
				system("cls");
			break;
		}
	}
	return 0;
}
