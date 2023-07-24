/*
 +=============================================================
        UNIFAL = Universidade Federal de Alfenas .
            BACHARELADO EM CIENCIA DA COMPUTACAO.
 Trabalho.....: Sistema de Biblioteca
 Disciplina...: AEDs1
 Professor....: Iago Augusto de Carvalho
 Alunos.......: Gustavo Fidelis Camilo e Bárbara Silveira Rodriguês
 Data.........: 11/08/2022
 +=============================================================*
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int listar();
void inserir(char *titulo, char *autor, int num_paginas);
void remover(char *titulos);
int buscar(char *titulo);
int contarlinha();

int main()
{
    char titulo[100];
    char autor[100];
    char nume[25];  //receber numero 
    int num_paginas;

    printf("-----------------------\n"); 
    printf("-------Biblioteca------\n");
    printf("-----------------------\n");
    printf("\n");

    char opc[25];
    int flag =1;
    int num;
    
    while(flag){
        printf("\nEscolha a funcao desejada: \n");
        puts("(1) Inserir\n");
        puts("(2) Remover\n");
        puts("(3) Buscar\n");
        puts("(4) Listar\n");
        puts("(5) Sair\n");
        scanf("%s", opc);
        num = atoi(opc); //input da função do usuario

        // Switch Case para as funções do programa

        switch(num){

            case 1 :
                printf("Digite o nome do livro:\n");
                scanf("%s", titulo);
                printf("Digite o nome do autor:\n");
                scanf("%s", autor);
                printf("Digite o numero de paginas\n");
                scanf("%s", nume);
                num_paginas= atoi(nume);
                if(num_paginas < 0){
                  while(num_paginas < 0){
                    printf("Numero nao pode ser menor que 0.\nDigite um número valido:  ");
                    scanf("%s", nume);
                    num_paginas = atoi(nume);
                  }
                }
                inserir(titulo, autor, num_paginas);
                break;

            case 2 :
                printf("Digite o nome do livro a ser excluido:\n");
                scanf("%s", titulo);
                remover(titulo);
                break;

            case 3 :
                printf("Digite o nome do livro que deseja buscar:\n");
                scanf("%s", titulo);
                buscar(titulo);
                break;

            case 4 :
                listar();
                break;

            case 5 :
                printf("Volte sempre!\n");
                flag = 0;
                break;
            default :
                printf("Invalido. Tente novamente\n"); //usuario digita um input para opc invalido
        }
    }  
  return 0;
}

void remover(char *titulos)
{
    // checa se o titulo existe
    if (buscar(titulos) == -1)
    {
        printf("O titulo nao existe\n");
        return;
    } 

    // remove o titulo
    FILE *arquivo = fopen("livros.txt", "r");
    FILE *arquivo_temp = fopen("livros_temp.txt", "w"); //arquivo temporario que não terá o titulo removido
    char linha[100];
    while (fgets(linha, 100, arquivo)) //percorre o arquivo
    {
        if (strstr(linha, titulos) == NULL) //strstr para achar a primeira ocorrencia
        {
            fprintf(arquivo_temp, "%s", linha); //escreve no arquivo temporario sem o titulo escolhido
        }
    }
    fclose(arquivo);
    fclose(arquivo_temp);
    remove("livros.txt"); //exclui o arquivo antigo
    rename("livros_temp.txt", "livros.txt"); // arquivo temporario vira o arquivo principal
    printf("O titulo foi removido\n");
}

int buscar(char *titulo)
{
    FILE *arquivo;
    arquivo = fopen("livros.txt", "r"); //abre o arquivo para leitura
    if (arquivo == NULL) //arquivo não pode ser lido ou não foi criado
    {
        return -1;
    }
    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL) //percorre as linhas do arquivo
    {
        if (strstr(linha, titulo) != NULL) //strstr devolve um ponteiro para a primeira ocorrencia da string
        {
            printf("%s", linha); //escreve o nome do livro buscado
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo); //nenhum livro foi encontrado
    return -1;
}

void inserir(char *titulo, char *autor, int num_paginas)
{
    if (buscar(titulo) == -1) //se o titulo escolhido não está gravado no arquivo
    {
        FILE *arquivo;
        arquivo = fopen("livros.txt", "a"); //abri um arquivo para acrescentar algo no final
      
        //pega o input do usuario        
        fprintf(arquivo, "%s - ", titulo);
        fprintf(arquivo, "%s - ", autor);
        fprintf(arquivo, "%d \n", num_paginas);
        fclose(arquivo);
    }
    else
    {
        printf("Titulo ja existe\n"); //buscar retornou 0
    }
}

int listar() 
{
    FILE *arquivo;
    arquivo = fopen("livros.txt", "r");
    if(arquivo == NULL){
        printf("Arquivo não existe ou não foi possivel abrir\n");
        return -1;
    }
    
    char linha[100];
    char *titulo;
    char *autor;
    int num_paginas;
    int i, a=0;
    i = contarlinha();
    char dinTitulo[i][100]; // a matriz no mesmo tamanho da qtd de titulos
    char dinAutor[i][100];  // mesma coisa, sendo elas para fazer a ordenação
    int  dinNum[i];
    char aux[i][100];   //auxiliares para fazer a ordenação
    char aux2[i][100];
    int aux3[i];
    int b,c;

    while (fgets(linha, 100, arquivo) != NULL)
    {
        titulo = strtok(linha, "-");  //separa titulo da string, uso de token
        strcpy(dinTitulo[a], titulo); //aloca o token em uma matriz
        autor = strtok(NULL, "-"); 
        strcpy(dinAutor[a], autor); 
        num_paginas = atoi(strtok(NULL, " \n")); 
        dinNum[a] = num_paginas; 
        a++;   
    }
    fclose(arquivo);
    //ordenação
    for(b=0; b < i -1; b++){ //passar em todas as linhas
        for(c=0; c < i-1-b;c++){ //verificar linha a linha
            if(strcmp(dinTitulo[c], dinTitulo[c+1]) > 0) //condição se a primeria string é maior q a outra.
            {
                // trocando posições dos titulos, autores e numero de paginas
                strcpy(aux[c], dinTitulo[c+1]);
                strcpy(dinTitulo[c+1], dinTitulo[c]);
                strcpy(dinTitulo[c], aux[c]);

                strcpy(aux2[c], dinAutor[c+1]);
                strcpy(dinAutor[c+1], dinAutor[c]);
                strcpy(dinAutor[c], aux2[c]);

                aux3[c] = dinNum[c+1];
                dinNum[c+1]=dinNum[c];
                dinNum[c]=aux3[c];
            }
        }
    }
    for(int l=0;l<i;l++){ //printar todos os livros
        printf(" Titulo: %s - Autor: %s - Numero de paginas: %d   \n", dinTitulo[l], dinAutor[l], dinNum[l]);
    }
    return -1;
}

int contarlinha(){
    FILE *arquivo;
    arquivo = fopen("livros.txt", "r"); //abre o arquivo para leitura
    char linha[100];
    int i = 0; //quantidade de linhas
    while (fgets(linha, 100, arquivo) != NULL) //percorre o arquivo
    {
      i++; //acrescenta uma linha cada vez que faz o loop
    }
    return i; //retorna a quantidade de linhas para o usuario
}