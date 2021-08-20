#include <stdio.h>
#include <stdlib.h> 

#define MAX 1000 

typedef struct item
{
    int numero;        
    int peso_aresta;       
    struct item *prox;  
    struct item *baixo;
} item;                

typedef struct
{
    int quantV;
    item *inicio;
} ListaDinamica;  

typedef struct fila
{
    int numero;
    struct fila *prox;
} fila;

typedef struct
{
    int quant;
    fila *inicio; 
    fila *fim;   
} FilaDinamica;

void prisao(ListaDinamica *L); 
void CriaLD(ListaDinamica *L); 
void Free_All(ListaDinamica *L);
void ImprimeGrafoCompleto(ListaDinamica *L);
item *NovaAresta(int value, int peso); 
item *NovoVert(int value); 
int VerificaAresta(ListaDinamica *L, int v1, int v2, int peso);
void InserirArestaOrdenado(ListaDinamica *L, item *C, item *V);
int InserirVertice(ListaDinamica *L, int n);
void InserirPrimeiroVertice(ListaDinamica *L, item *c);
void InserirFimVertice(ListaDinamica *L, item *c);
void InserirVerticeOrdenado(ListaDinamica *L, item *C);
void MatrizAdjacencia(ListaDinamica *L);
int **AlocaMatrizDinamica(int l, int c);
void printaMatriz(int l, int c, int **matriz); 
void FreeMatrizDinamica(int l, int **M); 
int buscaLinha(int valor, int l, int c, int **M);
item *RetornaArestasDadoVertice(ListaDinamica *L, int Vinicio);
int **BuscaEmLargura(ListaDinamica *L, int Vinicio); 
int Verifica_e_BuscaLargura(ListaDinamica *L, int Vinicio); 
int InformaPosicao(ListaDinamica *L, int Vinicio); 
void InsereFila(FilaDinamica *F, int value);
int RemoveFila(FilaDinamica *F);

int tempo = 0; 

int main(void)
{
    int opcao;  
    int retorno; 

    ListaDinamica Grafo;
    CriaLD(&Grafo);      

    prisao(&Grafo); 

    do 
    {
        printf("\n1. Visualizar Grafo\n");
        printf("2. Converter Grafo para matriz de Adjacencia\n");
        printf("3. Caminhamento em Amplitude (Busca em Largura)\n4. sair");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: 
        {
            if (Grafo.quantV == 0)
            {
                printf("Grafo Vazio !!!\n");
            }
            else
            {
                ImprimeGrafoCompleto(&Grafo);
            }
            break;
        }

        case 2: 
        {
            if (Grafo.quantV == 0)
            {
                printf("Grafo Vazio !!!\n");
            }
            else
            {
                MatrizAdjacencia(&Grafo);
            }
            break;
        }

        case 3: 
        {
            int v1;
            printf("Informe o vertice de Origem: ");
            scanf("%d", &v1);

            retorno = Verifica_e_BuscaLargura(&Grafo, v1);

            if (retorno == -1)
            {
                printf("ERRO! Nao existe o Vertice %d no Grafo !!!\n", v1);
            }
            else if (retorno == -2)
            {
                printf("Grafo Vazio !!!\n");
            }
            break;
        }

        case 4: 
        {
            Free_All(&Grafo); 
            break;            
            
        }

        default: 
        {
            printf("Opcao Invalida !!!\n");
            break;
        }
        }
    } while (opcao != 13); 
    return 0;
}


void prisao(ListaDinamica *L) 
{
    InserirVertice(L, 1);
    InserirVertice(L, 2);
    InserirVertice(L, 3);
    InserirVertice(L, 4);
    InserirVertice(L, 5);
    InserirVertice(L, 6);
    InserirVertice(L, 7);
    InserirVertice(L, 8);
    InserirVertice(L, 9);
    InserirVertice(L, 10);
    InserirVertice(L, 11);

    VerificaAresta(L, 1, 6, 1);
    VerificaAresta(L, 1, 11, 4);
    VerificaAresta(L, 2, 11, 4);
    VerificaAresta(L, 2, 4, 1);
    VerificaAresta(L, 2, 5, 1);
    VerificaAresta(L, 2, 6, 1);
    VerificaAresta(L, 3, 11, 4);
    VerificaAresta(L, 3, 4, 1);
    VerificaAresta(L, 4, 2, 1);
    VerificaAresta(L, 4, 5, 1);
    VerificaAresta(L, 4, 10, 1);
    VerificaAresta(L, 5, 2, 1);
    VerificaAresta(L, 5, 4, 1);
    VerificaAresta(L, 5, 7, 1);
    VerificaAresta(L, 5, 9, 1);
    VerificaAresta(L, 5, 10, 1);
    VerificaAresta(L, 6, 1, 1);
    VerificaAresta(L, 6, 2, 1);
    VerificaAresta(L, 6, 7, 1);
    VerificaAresta(L, 7, 5, 1);
    VerificaAresta(L, 7, 6, 1);
    VerificaAresta(L, 7, 8, 1);
    VerificaAresta(L, 7, 9, 1);
    VerificaAresta(L, 8, 11, 4);
    VerificaAresta(L, 8, 7, 1);
    VerificaAresta(L, 9, 11, 4);
    VerificaAresta(L, 9, 5, 1);
    VerificaAresta(L, 9, 7, 1);
    VerificaAresta(L, 9, 10, 1);
    VerificaAresta(L, 10, 11, 4);
    VerificaAresta(L, 10, 4, 1);
    VerificaAresta(L, 10, 5, 1);
    VerificaAresta(L, 10, 9, 1);
}

void CriaLD(ListaDinamica *L) 
{
    L->quantV = 0;    
    L->inicio = NULL; 
}

void Free_All(ListaDinamica *L) 
{
    item *AuxV, *AuxA, *InicioA; 
    while (L->inicio != NULL)    
    {
        AuxV = L->inicio;       
        InicioA = AuxV->prox;   
        while (InicioA != NULL) 
        {
            AuxA = InicioA;
            InicioA = AuxA->prox;
            free(AuxA); 
            AuxA = NULL;
        }
        L->inicio = AuxV->baixo;
        free(AuxV); 
        AuxV = NULL;
    }
    
    
    
}

void ImprimeGrafoCompleto(ListaDinamica *L) 
{
    item *auxV = L->inicio; 
    item *auxA;
    printf("Vertices      Arestas\n");
    while (auxV != NULL) 
    {
        auxA = auxV;                             
        printf("   %2d  ------>", auxV->numero); 
        if (auxA->prox == NULL)                  
        {
            printf("   NULL\n");
        }
        else 
        {
            auxA = auxV->prox;   
            while (auxA != NULL) 
            {
                printf(" %d ->", auxA->numero);
                auxA = auxA->prox; 
            }
            printf(" NULL\n");
        }
        auxV = auxV->baixo; 
    }
}


int VerificaAresta(ListaDinamica *L, int v1, int v2, int peso) 
{
    
    
    
    
    

    
    if (L->quantV == 0 || L->quantV == 1)
    {              
        return -4; 
    }

    if (v1 == v2) 
    {
        return -3; 
    }

    
    item *aux = L->inicio; 
    int cont = 0;          
    while (aux != NULL)
    {
        if (aux->numero == v1 || aux->numero == v2)
        {
            cont++; 
        }
        aux = aux->baixo; 
    }
    if (cont != 2) 
    {
        return -2; 
    }

    
    aux = L->inicio;          
    cont = 0;                 
    while (aux->numero != v1) 
    {                         
        aux = aux->baixo;
    }
    while (aux != NULL) 
    {
        if (aux->numero == v2) 
        {
            cont++; 
        }           
        aux = aux->prox;
    }
    if (cont != 0)
    {
        return -1; 
    }
    

    
    aux = L->inicio;          
    while (aux->numero != v1) 
    {
        aux = aux->baixo;
    }
    item *novo;                  
    novo = NovaAresta(v2, peso); 
    InserirArestaOrdenado(L, novo, aux);

    
    aux = L->inicio;
    while (aux->numero != v2)
    {
        aux = aux->baixo;
    }
    novo = NovaAresta(v1, peso);
    InserirArestaOrdenado(L, novo, aux);
    
    

    return 1; 
}

void InserirArestaOrdenado(ListaDinamica *L, item *C, item *V) 
{
    
    if (V->prox == NULL) 
    {
        V->prox = C;
    }

    else if (C->numero < V->prox->numero) 
    {
        C->prox = V->prox;
        V->prox = C;
    }

    else 
    {
        item *auxa = V->prox; 
        

        while (V->prox != NULL) 
        {
            V = V->prox;
        }

        if (C->numero > V->numero) 
        {
            V->prox = C; 
        }

        else 
        {
            item *auxd;        
            auxd = auxa->prox; 
            while (auxd->numero < C->numero)
            {
                auxa = auxa->prox;
                auxd = auxa->prox;
            }
            C->prox = auxa->prox;
            auxa->prox = C;
        }
    }
}



void MatrizAdjacencia(ListaDinamica *L) 
{
    int TamanhoMatriz = L->quantV + 1;
    
    int **MatrizAdj = AlocaMatrizDinamica(TamanhoMatriz, TamanhoMatriz); 
    

    item *Aux = L->inicio;
    int i;

    for (i = 1; i < TamanhoMatriz; i++) 
    {                                   
        MatrizAdj[0][i] = Aux->numero;  
        MatrizAdj[i][0] = Aux->numero;  
        Aux = Aux->baixo;               
    }

    item *AuxA;      
    Aux = L->inicio; 
    int linha = 1, coluna;

    while (Aux != NULL) 
    {
        if (Aux->prox != NULL) 
        {
            AuxA = Aux->prox;    
            while (AuxA != NULL) 
            {
                coluna = buscaLinha(AuxA->numero, TamanhoMatriz, TamanhoMatriz, MatrizAdj); 
                MatrizAdj[linha][coluna] = AuxA->peso_aresta;                                  
                AuxA = AuxA->prox;
            }
        }
        Aux = Aux->baixo;
        linha++;
        
    }
    printf("\n  Matriz de Adjacencia\n\n");
    printaMatriz(TamanhoMatriz, TamanhoMatriz, MatrizAdj);
    FreeMatrizDinamica(TamanhoMatriz, MatrizAdj); 
}

int **AlocaMatrizDinamica(int l, int c) 
{
    int i, j;
    int **m = (int **)malloc(l * sizeof(int *)); 

    for (i = 0; i < l; i++)
    {
        m[i] = (int *)malloc(c * sizeof(int)); 
        for (j = 0; j < c; j++)
        {
            m[i][j] = 0; 
        }
    }
    return m; 
}

int buscaLinha(int valor, int l, int c, int **M) 
{
    int i;
    for (i = 1; i < l; i++)
    {
        if (M[i][0] == valor)
        {
            return i; 
        }
    }
    return -1; 
}

void printaMatriz(int l, int c, int **matriz) 
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        printf("  ");
        for (j = 0; j < c; j++)
        {
            printf("%2d ", matriz[i][j]); 
        }
        printf("\n");
    }
}

void FreeMatrizDinamica(int l, int **M) 
{
    int i;
    for (i = 0; i < l; i++)
    {
        free(M[i]); 
    }
    free(M); 
    M = NULL;
}


int Verifica_e_BuscaLargura(ListaDinamica *L, int Vinicio) 
{
    if (L->quantV == 0)
    {
        return -2; 
    }

    item *aux = L->inicio;
    int cont = 0;
    while (aux != NULL)
    {
        if (aux->numero == Vinicio)
        {
            cont++;
            break; 
        }
        aux = aux->baixo; 
    }

    if (cont == 0) 
    {
        return -1; 
    }

    

    int **retorno; 
    retorno = BuscaEmLargura(L, Vinicio);

    FreeMatrizDinamica(3, retorno);
    retorno = NULL;
    return 0;
}

int **BuscaEmLargura(ListaDinamica *L, int Vinicio) 
{
    int arrVerify[10] = {0};
    arrVerify[0] = Vinicio;
    int tamGrafo = L->quantV; 

    int **matriz = AlocaMatrizDinamica(3, tamGrafo); 
    int i;
    for (i = 0; i < tamGrafo; i++) 
    {
        if(i == 10){
            matriz[2][i] = 1;
            continue;
        }

        matriz[1][i] = -1; 
        matriz[0][i] = -1; 
        matriz[2][i] = 0;  
                           
                           
                           
                           
    }

    
    
    
    

    int posicao = InformaPosicao(L, Vinicio); 

    
    matriz[1][posicao] = -1;
    matriz[0][posicao] = 0;
    matriz[2][posicao] = 1;

    FilaDinamica Q; 
    Q.quant = 0;
    Q.inicio = NULL;
    Q.fim = NULL;

    InsereFila(&Q, Vinicio); 

    int u, v;
    int posu, posv; 
    item *aux;
    while (Q.quant != 0) 
    {
        u = RemoveFila(&Q);
        posu = InformaPosicao(L, u);
        aux = RetornaArestasDadoVertice(L, u); 
        while (aux != NULL)                    
        {
            v = aux->numero;
            posv = InformaPosicao(L, v);
            if (matriz[2][posv] == 0 || matriz[2][posv] == 3)
            {
                for(int i = 0; i < 10; i ++){
                    if(arrVerify[i] == 0){
                        arrVerify[i] = aux->numero;
                        break;
                    }
                }
                matriz[2][posv] = 3;
                matriz[0][posu] + 1;
                matriz[0][posv] = matriz[0][posu] + 1;
                matriz[1][posv] = u;
                InsereFila(&Q, v);
            }
            matriz[2][posu] = 2;
            aux = aux->prox;
        }
    }

    aux = L->inicio;
    printf("\n BUSCA EM LARGURA");
    printf("\n Vertice   d   Pai   Cor\n");
    for (i = 0; i < tamGrafo; i++)
    {
        printf("   %2d     %2d   %2d   %2d\n", aux->numero, matriz[0][i], matriz[1][i], matriz[2][i]); 
        aux = aux->baixo;
    }
    int count = 0;
    for(int i = 0; i < 10; i ++){
        if(arrVerify[i] != 0){
            ++count;
        }
    }
    printf("TAMANHO: %d\n", count);
    printf("\nOBS: Se (d) tiver um (-1) quer dizer que o Grafo nao e conexo !!!\n");
    printf("OBS: Se pai tiver mais que um (-1) quer dizer que o Grafo nao e conexo !!!\n");
    printf("OBS: Pai igual (-1) quer dizer que nao existe.\n");

    return matriz;
}

item *RetornaArestasDadoVertice(ListaDinamica *L, int Vinicio) 
{
    item *Aux = L->inicio;
    while (Aux->numero != Vinicio) 
    {
        Aux = Aux->baixo;
    }
    return Aux->prox; 
}

int InformaPosicao(ListaDinamica *L, int Vinicio) 
{
    item *aux = L->inicio;
    int cont = 0;
    
    while (aux->numero != Vinicio)
    { 
        cont++;
        aux = aux->baixo;
    }
    return cont; 
}

void InsereFila(FilaDinamica *F, int value)
{
    
    fila *aux;
    aux = malloc(sizeof(fila)); 
    aux->numero = value;        
    aux->prox = NULL;           

    if (F->quant == 0) 
    {
        F->inicio = aux;
        F->fim = aux;
    }
    else 
    {
        F->fim->prox = aux; 
        F->fim = aux;       
    }
    F->quant++;
}

int RemoveFila(FilaDinamica *F)
{
    int valor;         
    if (F->quant != 0) 
    {
        valor = F->inicio->numero; 
        fila *aux;
        if (F->quant == 1) 
        {
            aux = F->inicio;
            free(aux);
            aux = NULL;
            
            F->quant = 0;
            F->inicio = NULL;
            F->fim = NULL;
        }
        else 
        {
            aux = F->inicio;       
            F->inicio = aux->prox; 
            free(aux);
            aux = NULL;
            F->quant--;
        }
    }
    return valor; 
}


int InserirVertice(ListaDinamica *L, int n) 
{                                           
    
    

    
    item *aux;          
    if (L->quantV != 0) 
    {                   
        int i;
        aux = L->inicio;                
        for (i = 0; i < L->quantV; i++) 
        {
            if (aux->numero == n) 
            {
                return -1;
            }
            aux = aux->baixo; 
        }
    }
    

    aux = NovoVert(n);              
    InserirVerticeOrdenado(L, aux); 
    return 1;                       
}

void InserirPrimeiroVertice(ListaDinamica *L, item *c) 
{
    L->quantV++; 
    c->baixo = L->inicio;
    L->inicio = c; 
}

void InserirFimVertice(ListaDinamica *L, item *c) 
{
    
    int pos = L->quantV; 
    int cont = 0;
    item *aux = L->inicio;   
    while (cont < (pos - 1)) 
    {
        aux = aux->baixo;
        cont++;
    }
    c->baixo = aux->baixo;
    aux->baixo = c;
    L->quantV++;
}

void InserirVerticeOrdenado(ListaDinamica *L, item *C) 
{
    item *aux = L->inicio; 
    if (L->quantV != 0)    
    {
        while (aux->baixo != NULL) 
        {
            aux = aux->baixo;
        }
    } 

    if (L->inicio == NULL) 
    {
        InserirPrimeiroVertice(L, C);
    }

    else if (C->numero < L->inicio->numero) 
    {
        InserirPrimeiroVertice(L, C);
    }

    else if (C->numero > aux->numero) 
    {
        InserirFimVertice(L, C);
    }

    else 
    {
        item *auxa, *auxd; 
        auxa = L->inicio;
        auxd = auxa->baixo;
        while (auxd->numero < C->numero)
        {
            auxa = auxa->baixo;
            auxd = auxa->baixo;
        }
        C->baixo = auxa->baixo;
        auxa->baixo = C;
        L->quantV++;
    }
}

item *NovoVert(int value) 
{
    item *aux;
    aux = malloc(sizeof(item)); 
    aux->numero = value;        
    aux->peso_aresta = -1;         
    aux->prox = NULL;           
    aux->baixo = NULL;          
    return aux;
}

item *NovaAresta(int value, int peso) 
{
    item *aux;
    aux = malloc(sizeof(item)); 
    aux->numero = value;        
    aux->peso_aresta = peso;      
    aux->prox = NULL;           
    aux->baixo = NULL;          
    return aux;
}
