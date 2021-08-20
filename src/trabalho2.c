
#include <stdio.h>
#include <stdlib.h> // biblioteca Responsavel por incluir switch case e malloc

// SETAR AQUI um numero maior que o Peso Das Arestas
#define MAX 1000 // MAX é para o valor infinito que vai nas funções!!

// ============================ ESTRUTURA PARA O GRAFO =======================
typedef struct item
{
    int numero;         // valor vertice (ID)
    int P_Aresta;       // Valor do Peso da Aresta (ID ARESTA)
    struct item *prox;  // arestas
    struct item *baixo; // vertices
} item;                 // estrutura que corresponde a cada Vertice/Aresta do Grafo

typedef struct
{
    int quantV;   // Quantidade de Vertices
    item *inicio; // Inicio --> Onde começa o 1 vertice
} ListaDinamica;  // Grafo --> ListaDinamica

// ============================ ESTRUTURA PARA FILA =======================
typedef struct fila
{
    int numero;
    struct fila *prox;
} fila;

typedef struct
{
    int quant;
    fila *inicio; // Remove no INICIO
    fila *fim;    // Insere no FIM
} FilaDinamica;

// ===========================CABEÇALHOS========================================
void prisao(ListaDinamica *L);
void CriaLD(ListaDinamica *L);
void Free_All(ListaDinamica *L);
void ImprimeGrafoCompleto(ListaDinamica *L);
item *NovaAresta(int value, int peso);
item *NovoVert(int value);
item *RetornaItemAnterior(ListaDinamica *L, int v1);
int VerificaRemoveVertices(ListaDinamica *L, int v1);
int VerificaRemoveArestas(ListaDinamica *L, int v1, int v2);
int VerificaAresta(ListaDinamica *L, int v1, int v2, int peso);
void InserirArestaOrdenado(ListaDinamica *L, item *C, item *V);
int InserirVertice(ListaDinamica *L, int n);
void InserirPrimeiroVertice(ListaDinamica *L, item *c);
void InserirFimVertice(ListaDinamica *L, item *c);
void InserirVerticeOrdenado(ListaDinamica *L, item *C);
void RemoveAresta(ListaDinamica *Lista, item *V, int n);
int InformaGrauVertice(ListaDinamica *L, int V);
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
int VerificaGrafoConexo(ListaDinamica *L);
int BuscaEmProfundidade(ListaDinamica *L);
void DFS_VISIT(int **M, int u, ListaDinamica *L);
int AlgoritmoPrim(ListaDinamica *L, int Vinicio);
int Extract_MIN(FilaDinamica *F, int **Key);
int Informa_Numero_Esta_Fila(FilaDinamica *F, int numero);
void printaFila(FilaDinamica *F); // teste
int Dijkstra(ListaDinamica *L, int Vinicio);
int **Initialize_Single_Source(ListaDinamica *L, int Vinicio);
void Relax(ListaDinamica *L, int u, int v, int **Matriz);
int Extract_MIN_Dijkstra(FilaDinamica *F, int **Matriz);
// =============================================================================

int tempo = 0; // usada na função "DFS_VISIT"

int main(void)
{
    int opcao;   // Variavel para escolher opcoes do MENU
    int retorno; // Variavel usada para receber retorno das funcoes

    ListaDinamica Grafo; // Criando uma Lista Dinamica com o Nome GRAFO
    CriaLD(&Grafo);      // Setando Quantidade e Ponteiro Inicio para NULL

    // ====================================== TIRAR DEPOIS ===========================================

    prisao(&Grafo); //<<-- DESCOMENTAR AQUI !!!!
                         // OBS: v = malloc (100 * sizeof (int)); == int v[100];

    do // Responsavel por deixar o MENU em LOOP até o usuario informar "SAIR"
    {
        printf("\n1.  Inserir Vertices\n2.  Inserir Arestas\n3.  Visualizar Grafo\n");
        printf("4.  Remover Vertices\n5.  Remover Arestas\n6.  Informar grau de um vertice\n");
        printf("7.  Informar se o Grafo e conexo\n8.  Converter Grafo para matriz de Adjacencia\n");
        printf("9.  Caminhamento em Amplitude (Busca em Largura)\n10. Caminhamento em Profundidade\n");
        printf("11. Caminho Minimo (Algoritmo de Dijkstra)\n");
        printf("12. Arvore Geradora Minima (Algoritmo de Prim)\n13. Sair\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Inserir Vertices
        {
            // * PARA VERTICE ... NÃO PODE TER VALOR DE VERTICE REPETIDO ...

            int v; // Variavel para pegar o numero do vertice
            printf("Insira um numero para o Vertice maior que zero: ");
            scanf("%d", &v);

            retorno = InserirVertice(&Grafo, v); // chamando funcao para Inserir Vertice
            if (retorno == (-1))                 // Validando return ... (-1) para Vertice ja existente (repetido)
            {
                printf("Vertice Repetido !!!\n");
            }
            else // Validando return ... se != (-1) vertice adicionado com sucesso
            {
                printf("Vertice Criado com sucesso !!!\n");
            }
            break;
        }

        case 2: // Inserir Arestas
        {
            // * PARA ARESTAS ... NÃO PODE TER MULTIPLAS ARESTAS ... VERIFICAR SE OS PONTOS INFORMADOS TEM NO GRAFO

            int v1, v2, peso; // Variavel para pegar o vertice 1 e 2 informada pelo usuario
            printf("Informe o Vertice de Origem: ");
            scanf("%d", &v1);
            printf("Informe o Vertice de Destino: ");
            scanf("%d", &v2);

            do // Validando entrada para peso Aresta somente POSITIVO (como descrito no Trabalho)
            {
                printf("Informe o Peso da Aresta: ");
                scanf("%d", &peso);
            } while (peso <= -1);

            retorno = VerificaAresta(&Grafo, v1, v2, peso); // chamando função responsavel por Inserir e Verificar Arestas
            if (retorno == -1)
            {
                printf("ERRO! Já existe Aresta ligando os pontos %d e %d.\n", v1, v2);
            }
            else if (retorno == -2)
            {
                printf("ERRO! Nao existe os vertices %d ou %d ou ambos.\n", v1, v2);
            }
            else if (retorno == -3)
            {
                printf("ERRO! No Grafo nao pode ter laco (V1 = V2).\n");
            }
            else if (retorno == -4)
            {
                printf("ERRO! Quantidade de vertices insuficientes para criar aresta.\n");
            }
            else
            {
                printf("Aresta Criada com sucesso !!!\n");
            }
            break;
        }

        case 3: // Visualizar Grafo
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

        case 4: // Remover Vertices
        {
            int v1;
            printf("Informe o Vertice que deseja tirar: ");
            scanf("%d", &v1);

            retorno = VerificaRemoveVertices(&Grafo, v1);
            if (retorno == (-1))
            {
                printf("ERRO! O Vertice informado nao existe no Grafo !!!\n");
            }

            else
            {
                printf("Vertice Removido com sucesso !!!\n");
            }
            break;
        }

        case 5: // Remover Arestas
        {
            int v1, v2; // Variavel para pegar o vertice 1 e 2 informada pelo usuario
            printf("Informe o Vertice de Origem da Aresta a ser removido: ");
            scanf("%d", &v1);
            printf("Informe o Vertice de Destino da Aresta a ser removido: ");
            scanf("%d", &v2);

            retorno = VerificaRemoveArestas(&Grafo, v1, v2);
            if (retorno == -3)
            {
                printf("ERRO! V1 e V2 são iguais !!!\n");
            }

            else if (retorno == -2)
            {
                printf("ERRO! Nao existe os vertices %d ou %d ou ambos.\n", v1, v2);
            }

            else if (retorno == -1)
            {
                printf("ERRO! Nao existe aresta entre os vertices %d e %d.\n", v1, v2);
            }

            else
            {
                printf("Aresta removida com sucesso !!!\n");
            }
            break;
        }

        case 6: // Informar grau de um vertice
        {
            int v1;
            printf("Informe o Numero do Vertice para consultar seu grau: ");
            scanf("%d", &v1);
            retorno = InformaGrauVertice(&Grafo, v1);

            if (retorno == -1)
            {
                printf("ERRO! Não existe esse vertice no Grafo.\n");
            }

            else
            {
                printf("O grau do Vertice %d e: %d\n", v1, retorno);
            }
            break;
        }

        case 7: // Informar se o grafo e conexo
        {
            retorno = VerificaGrafoConexo(&Grafo);

            if (retorno == -2)
            {
                printf("Grafo Vazio !!!\n");
            }

            else if (retorno == -1)
            {
                printf("\n Usando a Busca em Largura para determinar: Grafo NAO conexo !!!\n");
            }

            else
            {
                printf("\n Usando a Busca em Largura para determinar: Grafo Conexo !!!\n");
            }
            break;
        }

        case 8: // Converter grafo para Matriz de Adjacencia
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

        case 9: // Caminhamento em Amplitude (Busca em Largura)
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

        case 10: // Caminhamento em Profundidade
        {
            retorno = BuscaEmProfundidade(&Grafo);

            if (retorno == -1)
            {
                printf("Grafo Vazio !!!\n");
            }
            break;
        }

        case 11: // Caminho Minimo (Algoritmo de Dijkstra)
        {
            int v1;
            printf("Informe o vertice de Origem: ");
            scanf("%d", &v1);

            retorno = Dijkstra(&Grafo, v1);

            if (retorno == -3)
            {
                printf("ERRO! Nao existe o vertice %d no Grafo !!!\n", v1);
            }
            else if (retorno == -2)
            {
                printf("Grafo Vazio !!!\n");
            }
            break;
        }

        case 12: // Arvore Geradora Minima (Algoritmo de Prim)
        {
            int v1;
            printf("Informe o vertice de Origem: ");
            scanf("%d", &v1);

            retorno = AlgoritmoPrim(&Grafo, v1);

            if (retorno == -1) // Grafo não conexo ...
            {
                printf("\n\nUsando a Busca em Largura para determinar: Grafo NAO conexo !!!\n");
                printf("Como o Grafo e NAO conexo .... Nao tem sentido encontrar a MST (Arvore Geradora Minima).\n");
            }

            else if (retorno == -2) // Grafo Vazio ...
            {
                printf("\nGrafo Vazio !!!\n");
            }

            else if (retorno == -3) // Não existe vertice inicio no Grafo ...
            {
                printf("\n\nERRO! Nao existe o Vertice %d no Grafo !!!\n", v1);
            }
            break;
        }

        case 13: // Sair
        {
            Free_All(&Grafo); // Antes de sair ele vai dar free no Grafo inteiro (Vertices e Arestas)
            break;            // eu poderia chamar o retira vertice e tirar todos os vertices do grafo mas eu queria fazer
            // a função free all para "treinar"
        }

        default: // Se Usuario informou numero != de [1-13] ~~ Opção Invalida
        {
            printf("Opcao Invalida !!!\n");
            break;
        }
        }
    } while (opcao != 13); // Se Opção for 13 ele sai do laço e "fecha" o programa
    return 0;
}

// ============================================ FUNÇOES DIVERSAS ===========================================
void prisao(ListaDinamica *L) // Função usada na "main"
{
    // TESTE DO TRABALHO 2 ...
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

    VerificaAresta(L, 1, 2, 7);
    VerificaAresta(L, 1, 4, 9);
    VerificaAresta(L, 1, 5, 10);
    VerificaAresta(L, 1, 6, 8);
    VerificaAresta(L, 1, 8, 9);
    VerificaAresta(L, 1, 10, 8);

    VerificaAresta(L, 2, 3, 4);
    VerificaAresta(L, 2, 4, 5);
    VerificaAresta(L, 2, 9, 9);
    VerificaAresta(L, 2, 10, 9);

    VerificaAresta(L, 3, 4, 1);
    VerificaAresta(L, 3, 5, 4);

    VerificaAresta(L, 4, 5, 3);

    VerificaAresta(L, 5, 6, 18);

    VerificaAresta(L, 6, 7, 9);
    VerificaAresta(L, 6, 8, 9);

    VerificaAresta(L, 7, 8, 3);
    VerificaAresta(L, 7, 9, 6);

    VerificaAresta(L, 8, 9, 4);
    VerificaAresta(L, 8, 10, 2);

    VerificaAresta(L, 9, 10, 2);
}

void CriaLD(ListaDinamica *L) // Função usada na "main"
{
    L->quantV = 0;    // Setando Quantidade de Vertices do Grafo em zero
    L->inicio = NULL; // atualizando ponteiro Inicio para NULL
}

void Free_All(ListaDinamica *L) // Função usada na "main"
{
    item *AuxV, *AuxA, *InicioA; // Ponteiro inicioA é para criar um Inicio para Arestas
    while (L->inicio != NULL)    // Loop responsavel por dar free em todos os vertices do grafo
    {
        AuxV = L->inicio;       // Enquanto L->inicio é != de NULL então tem item para dar free
        InicioA = AuxV->prox;   // Inicio de Aresta sempre começa no AuxV->prox;
        while (InicioA != NULL) // começa aqui para dar free nas arestas
        {
            AuxA = InicioA;
            InicioA = AuxA->prox;
            free(AuxA); // free na aresta
            AuxA = NULL;
        }
        L->inicio = AuxV->baixo;
        free(AuxV); // free no vertice
        AuxV = NULL;
    }
    // \/ NÂO PRECISA FAZER ISSO PORQUE MEU GRAFO NÃO É CRIADO COM MALLOC E SIM POR TIPO
    //free(L); // dando free na estrutura grafo
    //L = NULL;
}

void ImprimeGrafoCompleto(ListaDinamica *L) // Função usada na "main" case 3
{
    item *auxV = L->inicio; // Criando tipo item V para vertice e itemA para aresta.
    item *auxA;
    printf("Vertices      Arestas\n");
    while (auxV != NULL) // Vai terminar de printar o grafo quando chegar no ultimo vertice
    {
        auxA = auxV;                             // auxA precisa receber auxV para o auxA sempre printar os itens da sua linha
        printf("   %2d  ------>", auxV->numero); // Printando o Vertice
        if (auxA->prox == NULL)                  // Se o proximo item de Vertice for NULL ele vai printar um NULL
        {
            printf("   NULL\n");
        }
        else // Se não for NULL quer dizer que tem itens prox de Vertice ...
        {
            auxA = auxV->prox;   // Precisa fazer isso porque senão ele vai printar o Vertice de novo ... A aresta sempre começa do V->prox; e não de V.
            while (auxA != NULL) // Imprimir todos da Lista (Aresta)
            {
                printf(" %d ->", auxA->numero);
                auxA = auxA->prox; // Percorrendo Lista na Horizontal (Printando todas as Arestas) do vertice V
            }
            printf(" NULL\n");
        }
        auxV = auxV->baixo; // Para Percorrer até o ultimo Vertice da lista
    }
}

item *NovoVert(int value) // Usada na função "Inserir Vertice"
{
    item *aux;
    aux = malloc(sizeof(item)); // Alocando dinamicamente
    aux->numero = value;        // atribuindo o numero do Vertice para aux->numero
    aux->P_Aresta = -1;         // -1 para (não existe)
    aux->prox = NULL;           // Atualizando ponteiro para NULL (Arestas)
    aux->baixo = NULL;          // Atualizando ponteiro para NULL (vertices)
    return aux;
}

item *NovaAresta(int value, int peso) // Usada na Função "VerificaAresta"
{
    item *aux;
    aux = malloc(sizeof(item)); // Alocando dinamicamente
    aux->numero = value;        // Atribuindo o numero do Vertice para aux->numero
    aux->P_Aresta = peso;       // Atribuindo o peso da aresta
    aux->prox = NULL;           // Atualizando ponteiro para NULL (Arestas)
    aux->baixo = NULL;          // Atualizando ponteiro para NULL (Vertices)
    return aux;
}

item *RetornaItemAnterior(ListaDinamica *L, int v1) // Funcao usada em "VerificaRemoveVertices"
{
    item *C = L->inicio;
    while (C->baixo->numero != v1)
    {
        C = C->baixo;
    }
    return C;
    // Para ligar os ponteiros em LD Simplesmente Encadeada voce precisa parar um item antes do qual vc deseja remover
}
void printaFila(FilaDinamica *F) // Função teste ... Tirar depois nao é usada !!!
{
    if (F->quant != 0)
    {
        fila *aux = F->inicio;
        while (aux != NULL)
        {
            printf("%d ", aux->numero);
            aux = aux->prox;
        }
    }
}

// ===================================== FUNÇOES PARA VERTICE ===============================================
int InserirVertice(ListaDinamica *L, int n) // Função usada na "main"
{                                           // CHECKLIST DE VERIFICAÇÃO DE VERTICES    STATUS     RETURN
    //      * NÃO PODE TER VERTICES IGUAIS                                               OK!       (-1)
    //      * PODE TER VERTICE NEGATIVO || Resp: Sim mas n precisa validar               OK!       (--)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    item *aux;          // Criando variavel aux para percorrer o Grafo
    if (L->quantV != 0) // Se QuantV for 0 ... certamente o numero que o usuario informou não tem no grafo então não precisa validar e pode adicionar ele direto.
    {                   // Se QuantV != 0 ... então precisa validar se n tem no grafo ou não.
        int i;
        aux = L->inicio;                // Setando aux para o Ponteiro inicio do Vertice
        for (i = 0; i < L->quantV; i++) // Vai percorrer a Lista inteira para ver se acha um vertice igual o informado
        {
            if (aux->numero == n) // Se ele achar um n ja existente no grafo vai retornar -1 (ERRO)
            {
                return -1;
            }
            aux = aux->baixo; // Atualizando o aux para baixo (vertice) para ele conseguir percorrer o grafo
        }
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    aux = NovoVert(n);              // chamando função que cria um item e seta valor e atualiza ponteiros para NULL
    InserirVerticeOrdenado(L, aux); // Chamando função que insere Vertice
    return 1;                       // Se chegou até aqui é porque deu tudo CERTO !!!
}

void InserirPrimeiroVertice(ListaDinamica *L, item *c) // Usada na função "InserirVerticeOrdenado"
{
    L->quantV++; // Acrescentando quantidade relativo aos Vertices
    c->baixo = L->inicio;
    L->inicio = c; // Atualizando ponteiro L->inicio para o Vertice C
}

void InserirFimVertice(ListaDinamica *L, item *c) // Usada na função "InserirVerticeOrdenado"
{
    //OBS: NÃO VALIDEI POS=0 POIS O CODIGO INTEIRO JA ESTA FAZENDO ESSA VALIDACAO ... MAS SE FOR USAR ESSA FUNCAO COLOQUE
    int pos = L->quantV; // Como vai adicionar no fim da lista ... Só pegar a ultima posição da lista pelo QuantV
    int cont = 0;
    item *aux = L->inicio;   // atualizando aux para inicio da lista
    while (cont < (pos - 1)) // percorrendo a lista até o ultimo item
    {
        aux = aux->baixo;
        cont++;
    }
    c->baixo = aux->baixo;
    aux->baixo = c;
    L->quantV++;
}

void InserirVerticeOrdenado(ListaDinamica *L, item *C) // Usada na função "Inserir Vertice" (cima)
{
    item *aux = L->inicio; // criando o aux pois ele vai fazer o papel de um L->fim
    if (L->quantV != 0)    // se a lista esta vazia não precisa percorrer ela
    {
        while (aux->baixo != NULL) // loop responsavel por pegar o ultimo item da lista vertice
        {
            aux = aux->baixo;
        }
    } // para inserir no fim isso ...

    if (L->inicio == NULL) // Se tiver vazia a lista
    {
        InserirPrimeiroVertice(L, C);
    }

    else if (C->numero < L->inicio->numero) // Só tem numero grande e o numero dado é pequeno ... insere no inicio da lista
    {
        InserirPrimeiroVertice(L, C);
    }

    else if (C->numero > aux->numero) // Se o numero que vc quer inserir é maior que todos da lista .. insere no fim.
    {
        InserirFimVertice(L, C);
    }

    else // numero está entre o inicio e fim da lista.
    {
        item *auxa, *auxd; // Aux_Antes e Aux_Depois para comparar
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

// ===================================== FUNÇOES PARA ARESTAS ===============================================
int VerificaAresta(ListaDinamica *L, int v1, int v2, int peso) // Função usada na "main"
{
    // CHECKLIST DE VERIFICAÇÃO DE ARESTAS                                          STATUS     RETURN
    //      * V1 E V2 PRECISA SER DIFERENTE --> NÃO PODE TER LAÇO                    OK!        (-3)
    //      * PRECISA TER NO MINIMO 2 VERTICES NO GRAFO --> NÃO PODE TER LAÇO        OK!        (-4)
    //      * VERIFICAR SE V1 E V2 PERTENCEM AO GRAFO                                OK!        (-2)
    //      * VERIFICAR SE JA EXISTE ARESTA LIGANDO V1 E V2                          OK!        (-1)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    if (L->quantV == 0 || L->quantV == 1)
    {              // Não tem como juntar 2 pontos sem ter dois pontos (trabalho não aceita laço)
        return -4; // Saida (-4) quer dizer que tem vertices insuficientes para criar aresta
    }

    if (v1 == v2) // Não pode ter laço
    {
        return -3; // Saida (-3) quer dizer que V1 é igual a V2.
    }

    // Verificar se existe no Grafo os Vertices V1 e V2 ...
    item *aux = L->inicio; // Criando tipo item e setando para começo do Grafo
    int cont = 0;          // Inicializando uma variavel contadora = 0 ... vai ser responsavel por contar se tem os V1 e V2
    while (aux != NULL)
    {
        if (aux->numero == v1 || aux->numero == v2)
        {
            cont++; // Se cair aqui 2x é porque o V1 e V2 existe na lista se cair 1 ou nenhuma vez é pq n tem
        }
        aux = aux->baixo; // Percorrendo grafo na vertical até Aux ser NULL
    }
    if (cont != 2) // Se for igual a 2 é porque o V1^V2 existe no Grafo, se for diferente não existe.
    {
        return -2; // Saida (-2) quer dizer que não tem V1 ou V2 no Grafo ou nenhum deles.
    }

    // Verificar Se já existe essa aresta no Grafo
    aux = L->inicio;          // Setando novamente Aux para inicio do Grafo
    cont = 0;                 // Setando novamente contador = 0 para validar return
    while (aux->numero != v1) // ele vai percorrer o gravo na Vertical(vertice) até achar o v1
    {                         // Ele vai achar o v1 pois ja foi verificado que v1 e v2 pertencem ao grafo
        aux = aux->baixo;
    }
    while (aux != NULL) // Agora o aux vai percorrer o gravo na Horizontal (Arestas).
    {
        if (aux->numero == v2) // Se ele achar o v2 é porque ja tem aresta ligando os pontos v1 e v2
        {
            cont++; // Se cair aqui é porque ja tem arestas ligando, então para validar uma saida o cont recebe 1;
        }           // Se cont=0 --> Não existe aresta ligando v1 e v2 | Se cont != 0 é porque existe aresta ligando V1 e V2
        aux = aux->prox;
    }
    if (cont != 0)
    {
        return -1; // Saida (-1) quer dizer que já existe aresta ligando os pontos V1 e V2
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    // ~~~~~~~~~~~~~~       &*&*    PARTE QUE VAI ADICIONAR ARESTAS    &*&*         ~~~~~~~~~~~~~
    aux = L->inicio;          // setando novamente aux para inicio do Grafo
    while (aux->numero != v1) // Vai percorrer a lista até achar o Vertice V1
    {
        aux = aux->baixo;
    }
    item *novo;                  // declarando tipo item para inserir no v1 a aresta v2
    novo = NovaAresta(v2, peso); // Chamando função para criar nova aresta
    InserirArestaOrdenado(L, novo, aux);

    // Precisamos fazer isso 2x ... um para inserir no v1 a aresta v2 e no outro inserir no v2 a aresta v1.
    aux = L->inicio;
    while (aux->numero != v2)
    {
        aux = aux->baixo;
    }
    novo = NovaAresta(v1, peso);
    InserirArestaOrdenado(L, novo, aux);
    // Chamando função para inserir ... onde novo é o elemento a ser inserido e aux é onde a lista começa
    // horizontalmente (aresta) em v1

    return 1; // Se chegou aqui porque não parou em nenhum return e conseguiu analisar e inserir com sucesso !!!
}

void InserirArestaOrdenado(ListaDinamica *L, item *C, item *V) // Função usada em "VerificaAresta
{
    // Item C --> item que vc quer inserir || Item V é o Vertice Atual, isto é, o vertice que tu quer inserir a aresta
    if (V->prox == NULL) // Se não tem arestas ... Basta atualizar ponteiro prox para o item novo
    {
        V->prox = C;
    }

    else if (C->numero < V->prox->numero) // Se o numero que vc vai inserir é menor que o primeiro numero da aresta
    {
        C->prox = V->prox;
        V->prox = C;
    }

    else // Inserir no FIM da lista (aresta) e no meio
    {
        item *auxa = V->prox; // só vai precisar disso se cair no else, mas como eu vou percorrer o V
        //vou perder referencia, então fiz uma "copia" dele aqui.

        while (V->prox != NULL) // Estou percorrendo a lista até o ultimo item para verificar a condição abaixo
        {
            V = V->prox;
        }

        if (C->numero > V->numero) // Se o ultimo item da lista é MENOR que o C ... INSERIR NO FIM da lista
        {
            V->prox = C; // Inserir FIM basta atualizar o ponteiro prox do ultimo elemento para C
        }

        else // CASO DO MEIO ... vou precisar usar o auxa (aux antes)
        {
            item *auxd;        // auxiliar depois
            auxd = auxa->prox; // aux depois vai receber o prox de antes ... para comparar.
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

// =================================== FUNÇOES PARA TIRAR VERTICES =========================================
int VerificaRemoveVertices(ListaDinamica *L, int v1) // Funcao usada na "main" (cima)
{
    // CHECKLIST DE VERIFICAÇÃO DE REMOÇÃO DE VERTICES                              STATUS     RETURN
    //      * VERIFICAR SE V1 EXISTE NO GRAFO                                         OK!       (-1)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    item *aux = L->inicio;
    int cont = 0, i;

    for (i = 0; i < L->quantV; i++) // percorrer o grafo inteiro para achar um vertice
    {
        if (aux->numero == v1)
        {
            cont++; // se caiu aqui pq tem v1 no grafo
            break;  // para não fazer o for ir até o fim ... se achou um não precisa percorrer o resto.
        }
        aux = aux->baixo;
    }
    if (cont == 0)
    {
        return -1; // se cont for 0 não tem vertice para remover ... então retorna (-1)
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÃO ...

    // ~~~~~~~~~~~~~~       &*&*    PARTE QUE VAI REMOVER VERTICE    &*&*         ~~~~~~~~~~~~~
    if (aux->prox != NULL) // Se não for NULL é porque tem arestas ... precisa tirar uma por uma e depois exclui o V
    {
        int Aresta;               // variavel responsavel por pegar as arestas do vertice e passar como parametro para a funcao Remove Arestas
        while (aux->prox != NULL) // vai percorrer as arestas até não
        {
            Aresta = aux->prox->numero;
            VerificaRemoveArestas(L, v1, Aresta);
        }
    }
    if (aux->prox == NULL) // se não tiver aresta é so ligar os vertices
    {
        if (L->quantV == 1) // se tiver só 1V é só dar free e criar outro Grafo
        {
            free(aux); // dando free no aux
            aux = NULL;
            CriaLD(L); // Criando outro Grafo, isto é, setando quantV=0 | Inicio/Fim == NULL
            return 1;  // não precisa fazer mais nada então return 1
        }

        else if (L->quantV == 2)         // Se tiver 2V ou tira do INICIO ou FIM
        {                                // OBS: VERTICE É BAIXO E ARESTA É PROXIMO
            if (L->inicio->numero == v1) // Se for tirar do INICIO
            {
                L->inicio = aux->baixo;
                aux->baixo = NULL;
            }
            else // Se v1 é o Ultimo Item
            {
                L->inicio->baixo = NULL;
            }
        }

        else if (aux->numero == L->inicio->numero) // Se o Vertice que for tirar é o primeiro da lista
        {
            L->inicio = aux->baixo;
            aux->baixo = NULL;
        }

        else // Se o Vertice tiver Entre outros Vertices ...
        {
            item *aux_Ant = RetornaItemAnterior(L, v1);
            aux_Ant->baixo = aux->baixo;
            aux->baixo = NULL;
        }

        free(aux);
        aux = NULL;
        L->quantV--;
        return 1;
    }
    return -1;
}

// =================================== FUNÇOES PARA TIRAR ARESTAS ===========================================
int VerificaRemoveArestas(ListaDinamica *L, int v1, int v2) // Função usada na "main"
{
    // CHECKLIST DE VERIFICAÇÃO DE REMOCÃO DE ARESTAS                                STATUS    RETURN
    //      * VERIFICAR SE V1 É IGUAL V2                                              OK!       (-3)
    //      * VERIFICAR SE V1 E V2 EXISTE NO GRAFO                                    OK!       (-2)
    //      * VERIFICAR SE V1 E V2 FAZEM CONEXÃO                                      OK!       (-1)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...

    // verificar se v1 = v2 ... não da para tirar laço pois o grafo não permite laço
    if (v1 == v2)
    {
        return -3; // Saida (-3) quer dizer que V1 == V2 ... não da para tirar laço se não tem laço
    }

    // Verificar se existe no Grafo os Vertices V1 e V2 ...
    item *aux = L->inicio; // Criando tipo item e setando para começo do Grafo
    int cont = 0;          // Inicializando uma variavel contadora = 0 ... vai ser responsavel por contar se tem os V1 e V2
    while (aux != NULL)
    {
        if (aux->numero == v1 || aux->numero == v2)
        {
            cont++; // Se cair aqui 2x é porque o V1 e V2 existe na lista se cair 1 ou nenhuma vez é pq n tem
        }
        aux = aux->baixo; // Percorrendo grafo na vertical até Aux ser NULL
    }
    if (cont != 2) // Se for igual a 2 é porque o V1^V2 existe no Grafo, se for diferente não existe.
    {
        return -2; // Saida (-2) quer dizer que não tem V1 ou V2 no Grafo ou nenhum deles.
    }

    // Verificar Se existe essa aresta no Grafo
    aux = L->inicio;          // Setando novamente Aux para inicio do Grafo
    cont = 0;                 // Setando novamente contador = 0 para validar return
    while (aux->numero != v1) // ele vai percorrer o gravo na Vertical(vertice) até achar o v1
    {                         // Ele vai achar o v1 pois ja foi verificado que v1 e v2 pertencem ao grafo
        aux = aux->baixo;
    }
    while (aux != NULL) // Agora o aux vai percorrer o gravo na Horizontal (Arestas).
    {
        if (aux->numero == v2) // Se ele achar o v2 é porque tem aresta ligando os pontos v1 e v2
        {
            cont++; // Se cair aqui é porque tem arestas ligando, então para validar uma saida o cont recebe 1;
        }           // Se cont=0 --> Não existe aresta ligando v1 e v2 | Se cont != 0 é porque existe aresta ligando V1 e V2
        aux = aux->prox;
    }
    if (cont != 1)
    {
        return -1; // Saida (-1) quer dizer que não existe aresta ligando os pontos V1 e V2
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    // ~~~~~~~~~~~~~~       &*&*    PARTE QUE VAI REMOVER ARESTAS    &*&*         ~~~~~~~~~~~~~
    aux = L->inicio;          // setando novamente aux para Inicio do Grafo
    while (aux->numero != v1) // loop para achar o vertice 1 e passar como parametro para função RemoverAresta
    {                         // Não precisa validar com NULL pois já verifiquei que existe o vertice 1
        aux = aux->baixo;     // percorrendo para baixo pois quero descobrir o vertice
    }
    RemoveAresta(L, aux, v2); // Função que vai remover a aresta ... passando Grafo, aux que seria o vertice v1 e o numero v2 para ele tirar de v1

    // Precisamos fazer isso 2x pois voce precisa tirar v1 de v2 e v2 de v1.
    aux = L->inicio;          // setando novamente aux para inicio do grafo
    while (aux->numero != v2) // loop para achar o vertice 2
    {
        aux = aux->baixo; // percorrendo para baixo pois quero descobrir o vertice
    }
    RemoveAresta(L, aux, v1); // agora ele vai tirar o v1 do vertice 2.

    return 1; // Se chegou até aqui porque não caiu em nenhum return e a verificação/remoção foi um success
}

void RemoveAresta(ListaDinamica *Lista, item *V, int n) // Função usada na "VerificaRemoveArestas"
{
    // item V corresponde ao Vertice ... e n é o numero que vc quer tirar da aresta
    item *aux, *temp;
    aux = V; // aux recebendo o começo do vertice que foi passada como parametro

    while (aux->prox->numero != n) // vai percorrer a até achar n
    {
        aux = aux->prox;
    }
    temp = aux->prox; // para não perder referencia
    aux->prox = temp->prox;
    temp->prox = NULL;
    free(temp); // dando free no item temp que foi adicionado com malloc.
    temp = NULL;
}

// =================================== FUNÇOES PARA GRAU VERTICE ============================================
int InformaGrauVertice(ListaDinamica *L, int V) // Função usada na "Main"
{
    // CHECKLIST DE GRAU VERTICE                                                     STATUS    RETURN
    // 		* VERIFICAR SE EXISTE V1              	                                  OK!       (-1)
    //      * VERIFICAR SE V1->PROX É NULL		                                      OK!       ( 0)
    //      * VERIFICAR SE V1->PROX É != NULL                                         OK!       ( X) onde X qtde de V

    // COMEÇA AQUI A PARTE DE VERIFICAÇÃO
    item *aux = L->inicio; // aux recebendo inicio da lista de vertices
    int cont = 0;          // variavel contadora para validar se tem ou não o Vertice no Grafo

    while (aux != NULL) // vai percorrer até o final do grafo ... se n parar no break
    {
        if (aux->numero == V) // se achou um vertice igual v1 .. cont vai ser != 0 ... break para n percorrer até o final
        {
            cont++;
            break;
        }
        aux = aux->baixo;
    }

    if (cont == 0) // se for == 0 é porque nao caiu no if ... se n caiu no if é porque não encontrou o vertice v1
    {
        return -1; // Retornando (-1) --> Vertice Não existe no Grafo
    }

    if (aux->prox == NULL) // validando NULL como 0 ..
    {
        return 0; // se não tem aresta ligando o Vertice (Prox for NULL) o grau do vertice é ZERO
    }

    cont = 0;                 // setando cont novamente para usar como contadora de grau do vertice
    while (aux->prox != NULL) // cada item corresponde a um grau ... então é so percorrer e cont++
    {
        cont++;
        aux = aux->prox; // percorrendo na vertical para buscar só as arestas
    }
    return cont; // retornando a quantidade de arestas que achou
}

// =================================== FUNÇOES PARA MATRIZ ADJ ===============================================
void MatrizAdjacencia(ListaDinamica *L) // Função usada na "Main"
{
    int TamanhoMatriz = L->quantV + 1;
    // mais um por causa Dos Indices que vão ficar em cima/lado da matriz
    int **MatrizAdj = AlocaMatrizDinamica(TamanhoMatriz, TamanhoMatriz); // Criando matriz Adjacencia
    // Chamando função que cria e zera a matriz dinamica

    item *Aux = L->inicio;
    int i;

    for (i = 1; i < TamanhoMatriz; i++) // começa em 1 porque em 0 é os indices que ficam FIXO
    {                                   // For para inserir os Vertices da Matriz ...
        MatrizAdj[0][i] = Aux->numero;  // Preenchendo as colunas com os vertices do Grafo
        MatrizAdj[i][0] = Aux->numero;  // Preenchendo as linhas com os vertices do Grafo
        Aux = Aux->baixo;               // Percorrendo até o ultimo Vertice ... Não precisa validar pq o tam_Matriz = Grafo
    }

    // ========= AGORA É A PARTE QUE INSERE NA MATRIZ

    // LEMBRETE: A MATRIZ COMEÇA DO 1,1 POIS O 0 e 0 É RESERVADO PARA OS INDICES (VERTICES)

    item *AuxA;      // Para o Aux não perder referencia, vou criar AuxA (Aresta) para percorrer as arestas no Vertice indicado
    Aux = L->inicio; // Setando novamente
    int linha = 1, coluna;

    //  EXPLICAÇÃO DA FUNÇÃO BUSCA LINHA ...
    // 	 A entrada X da matriz não necessariamente é igual ao Y Vertice ... por isso preciso passar o numero
    //   Y do vertice e pesquisar ele na matriz ... ai o retorno da matriz vai ser o indice X da Matriz.
    // 	 Não precisa fazer isso para os vertices, porque estou sempre pegando eles sequencialmente então o vertice
    //   Y sempre vai bater com a posição X da matriz.

    while (Aux != NULL) // Pegando Todos Vertices do Grafo até NULL (Percorrendo na Vertical)
    {
        if (Aux->prox != NULL) // So interessa quem tem aresta ... se não tiver não precisa fazer nada
        {
            AuxA = Aux->prox;    // AuxA vai ser o responsavel por percorrer na horizontal ... para Aux não perder referencia
            while (AuxA != NULL) // Enquanto não achar NULL na horizontal (arestas) percorre ...
            {
                coluna = buscaLinha(AuxA->numero, TamanhoMatriz, TamanhoMatriz, MatrizAdj); // Explicado la em cima
                MatrizAdj[linha][coluna] = AuxA->P_Aresta;                                  // Imprimindo o peso da aresta na matriz de adj
                AuxA = AuxA->prox;
            }
        }
        Aux = Aux->baixo;
        linha++;
        // Como estou fazendo sequencialmente os Vertices Do grafo, não preciso fazer uma função BuscaColuna.
    }
    printf("\n  Matriz de Adjacencia\n\n");
    printaMatriz(TamanhoMatriz, TamanhoMatriz, MatrizAdj);
    FreeMatrizDinamica(TamanhoMatriz, MatrizAdj); // dar free na matriz
}

int **AlocaMatrizDinamica(int l, int c) // Função usada em "MatrizAdjacencia"
{
    int i, j;
    int **m = (int **)malloc(l * sizeof(int *)); //Aloca um Vetor de Ponteiros

    for (i = 0; i < l; i++)
    {
        m[i] = (int *)malloc(c * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (j = 0; j < c; j++)
        {
            m[i][j] = 0; //Inicializa com 0.
        }
    }
    return m; // Retornando o Ponteiro para a Matriz Alocada
}

int buscaLinha(int valor, int l, int c, int **M) // Função usada em "MatrizAdjacencia"
{
    int i;
    for (i = 1; i < l; i++)
    {
        if (M[i][0] == valor)
        {
            return i; // retorna o indice da matriz baseado no valor informado ...
        }
    }
    return -1; // coloquei para n dar warning ... mas n precisa .. nunca vai cair aqui
}

void printaMatriz(int l, int c, int **matriz) // Função usada em "MatrizAdjacencia"
{
    int i, j;
    for (i = 0; i < l; i++)
    {
        printf("  ");
        for (j = 0; j < c; j++)
        {
            printf("%2d ", matriz[i][j]); // %2d para alinhar 2 a esquerda
        }
        printf("\n");
    }
}

void FreeMatrizDinamica(int l, int **M) // Função usada em "MatrizAdjacencia"
{
    int i;
    for (i = 0; i < l; i++)
    {
        free(M[i]); // como fiz uma matriz dinamica ... estou dando free nas linhas AQUI
    }
    free(M); // Dando free na Coluna AQUI
    M = NULL;
}

// =================================== FUNÇOES PARA BUSCA EM LARGURA ==========================================
int Verifica_e_BuscaLargura(ListaDinamica *L, int Vinicio) // Função usada na "main" (cima)
{
    // CHECKLIST DE VERIFICAÇÃO DA BUSCA EM LARGURA                                 STATUS     RETURN
    //      * VERIFICAR SE Vinicio EXISTE NO GRAFO                                    OK!       (-1)
    //      * VERIFICAR SE O TAMANHO DO GRAFO É != O                                  OK!       (-2)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    if (L->quantV == 0)
    {
        return -2; // Return (-2) quer dizer que o grafo está vazio !!!
    }

    item *aux = L->inicio;
    int cont = 0;
    while (aux != NULL)
    {
        if (aux->numero == Vinicio)
        {
            cont++;
            break; // Se achou não precisa continuar porque só pode ter um vertice igual para cada Grafo ...
        }
        aux = aux->baixo; // Verificando na vertical (Vertices)
    }

    if (cont == 0) // Se for igual a zero quer dizer que não achou o Vertice no Grafo ...
    {
        return -1; // Return (-1) quer dizer que não achou o vertice Vinicio no Grafo L
    }

    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    int **retorno; // retorno vai receber uma matriz ... onde tem o D/pi/cor
    retorno = BuscaEmLargura(L, Vinicio);

    FreeMatrizDinamica(3, retorno);
    retorno = NULL;
    return 0;
}

int **BuscaEmLargura(ListaDinamica *L, int Vinicio) // Função usada em "Verifica_e_BuscaLargura"
{
    int tamGrafo = L->quantV; // TamGrafo é a quantidade de vertices que tem no grafo

    int **matriz = AlocaMatrizDinamica(3, tamGrafo); // ONDE 0 --> D || 1 --> PI || 2 --> COR
    int i;
    for (i = 0; i < tamGrafo; i++) // Inicializando os vetores com:
    {
        matriz[1][i] = -1; // todos pais recebendo -1 ...
        matriz[0][i] = -1; // todas as distancias recebendo -1 ...
        matriz[2][i] = 0;  // todos recebendo cor BRANCA ...
                           // BRANCO == 0
                           // CINZA  == 1
                           // PRETO  == 2
    }

    //  EXPLICAÇÃO DA FUNÇÃO INFORMA POSIÇÃO ...
    // 	O vetor pi/d/cor começa no indice 0 e vai até Quantidade de Vertices do Grafo -1 ...
    // 	Sabemos que o vetor dinamico e o Grafo tem o mesmo tamanho ... então estou procurando o indice do vertice do grafo no vetor dinamico ...
    // 	Tambem preciso fazer isso pois não necessariamente meu Grafo tem vertices consecutivos (1,2,3,4,...), então preciso achar o indice X do Vertice.

    int posicao = InformaPosicao(L, Vinicio); // Explicado acima ...

    // Estou setando o pi/d/cor do Vertice inicio que o usuario informou ...
    matriz[1][posicao] = -1;
    matriz[0][posicao] = 0;
    matriz[2][posicao] = 1;

    FilaDinamica Q; // Declarando FilaDinamica e setando os seus ponteiros para NULL e quant para 0
    Q.quant = 0;
    Q.inicio = NULL;
    Q.fim = NULL;

    InsereFila(&Q, Vinicio); // colocando o vertice raiz (inicio) na Fila ...

    int u, v;
    int posu, posv; // Explicado la em cima ...
    item *aux;
    while (Q.quant != 0) // Enquanto a Fila não estiver vazia .... faça:
    {
        u = RemoveFila(&Q);
        posu = InformaPosicao(L, u);
        aux = RetornaArestasDadoVertice(L, u); // Essa função vai receber o Vertice e buscar no grafo ele e retornar as arestas ...
        while (aux != NULL)                    // Vai percorrer na horizontal até não achar mais arestas ...
        {
            v = aux->numero;
            posv = InformaPosicao(L, v);
            if (matriz[2][posv] == 0)
            {
                matriz[2][posv] = 1;
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
    printf("\n Vertice   d   Pai\n");
    for (i = 0; i < tamGrafo; i++)
    {
        printf("   %2d     %2d   %2d\n", aux->numero, matriz[0][i], matriz[1][i]); // Cor não precisa ser printada ...
        aux = aux->baixo;
    }
    printf("\nOBS: Se (d) tiver um (-1) quer dizer que o Grafo nao e conexo !!!\n");
    printf("OBS: Se pai tiver mais que um (-1) quer dizer que o Grafo nao e conexo !!!\n");
    printf("OBS: Pai igual (-1) quer dizer que nao existe.\n");

    return matriz;
}

item *RetornaArestasDadoVertice(ListaDinamica *L, int Vinicio) // Função usada em "BuscaEmLargura"
{
    item *Aux = L->inicio;
    while (Aux->numero != Vinicio) // forneço um vertice e ele vai dar as arestas desse vertice.
    {
        Aux = Aux->baixo;
    }
    return Aux->prox; // prox pois quero que ele retorne somente as arestas ...
}

int InformaPosicao(ListaDinamica *L, int Vinicio) // Função usada em "BuscaEmLargura"
{
    item *aux = L->inicio;
    int cont = 0;
    // assumindo que Vinicio exista no grafo.
    while (aux->numero != Vinicio)
    { // não precisa validar se Vinicio existe no grafo pois ja estou validando isso antes de chamar essa função
        cont++;
        aux = aux->baixo;
    }
    return cont; // basicamente vou fornecer um vertice e ele vai contar a posição dele do 0 até ele.
}

void InsereFila(FilaDinamica *F, int value)
{
    // FILA: INSERE NO ULTIMO E RETIRA DO PRIMEIRO ... portanto ... INSERE NO ->FIM && RETIRA NO ->INICIO
    fila *aux;
    aux = malloc(sizeof(fila)); // Alocando dinamicamente
    aux->numero = value;        // atribuindo o numero do Vertice para aux->numero
    aux->prox = NULL;           // Atualizando ponteiro para NULL (Arestas)

    if (F->quant == 0) // se a lista tiver vazia ... ponteiros inicio e fim vão ter o mesmo elemento ...
    {
        F->inicio = aux;
        F->fim = aux;
    }
    else // se a lista não tiver vazia ... só inserir no ponteiro fim e atualizar ele depois
    {
        F->fim->prox = aux; // inserindo aux no final da fila
        F->fim = aux;       // atualizando ponteiro fim para o aux (ultimo elemento da fila)
    }
    F->quant++;
}

int RemoveFila(FilaDinamica *F)
{
    int valor;         // vou retornar o ->numero removido ...
    if (F->quant != 0) // Se a fila estiver vazia não faz sentido tirar algo dela
    {
        valor = F->inicio->numero; // retornar numero
        fila *aux;
        if (F->quant == 1) // se tiver só um elemento vou dar free nele e depois criar uma nova lista ...
        {
            aux = F->inicio;
            free(aux);
            aux = NULL;
            // Setando parametros pois estou criando uma "nova" lista
            F->quant = 0;
            F->inicio = NULL;
            F->fim = NULL;
        }
        else // se não tiver só um elemento é so vc retirar do ->inicio
        {
            aux = F->inicio;       // preciso fazer isso para dar free nele
            F->inicio = aux->prox; // atualizando ponteiro inicio.
            free(aux);
            aux = NULL;
            F->quant--;
        }
    }
    return valor; // retornando o valor do item retirado ... estou usando isso na função "BuscaEmLargura"
}

// ===================================== FUNÇOES PARA GRAFO CONEXO ============================================
int VerificaGrafoConexo(ListaDinamica *L) // Função usada na "main" (cima)
{
    // CHECKLIST DE VERIFICAÇÃO DO GRAFO CONEXO OU NÃO                               STATUS    RETURN
    //      * VERIFICAR SE O GRAFO ESTÁ VAZIO OU NÃO                                  OK!       (-2)
    //      * PARA GRAFO CONEXO                                                       OK!       ( 0)
    //      * PARA GRAFO NÃO CONEXO                                                   OK!       (-1)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    if (L->quantV == 0) // Preciso validar isso aqui pois vou atribuir first = numero do 1 vertice do grafo
    {
        return -2; // Return -2 quer dizer que o grafo está VAZIO !!!
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    // SE TIVER UM (-1) NA DISTANCIA QUER DIZER QUE É DESCONEXO ...
    // SE TIVER MAIS QUE UM (-1) NO PAI QUER DIZER QUE É DESCONEXO ...
    // SE TIVER 0 (COR BRANCA) EM COR QUER DIZER QUE O GRAFO É DESCONEXO ...

    int **retorno, first, i;
    first = L->inicio->numero; // first vai ser meu vertice raiz ... pode se qualquer um ... vou escolher o 1 vertice

    retorno = BuscaEmLargura(L, first);

    for (i = 0; i < L->quantV; i++)
    {                           // vou usar o cor para validar se é conexo ou não
        if (retorno[2][i] == 0) // 2 porque é cor ... ONDE 0 --> D || 1 --> PI || 2 --> COR
        {                       // ...      ONDE 0 --> BRANCO || 1 --> CINZA || 2 --> PRETO
            FreeMatrizDinamica(3, retorno);
            return -1; // return -1 para Grafo NÂO conexo ...
        }
    }
    FreeMatrizDinamica(3, retorno);
    return 0; // return 0 para Grafo Conexo ...
}

// ===================================== FUNÇOES PARA BUSCA PROFUNDIDADE ======================================
int BuscaEmProfundidade(ListaDinamica *L) // Função usada na "main"
{
    tempo = 0;          // variavel global ... setando ela ....
    if (L->quantV == 0) // Se o grafo estiver vazio ...
    {
        return -1; // Return (-1) quer dizer que o grafo está Vazio
    }

    int tamGrafo = L->quantV;

    int **Matriz;

    Matriz = AlocaMatrizDinamica(4, tamGrafo); // onde linha 0 é os indices e linha 1 seria o proprio key
    // 0 --> COR || 1 --> PAI || 2 --> DISTANCIA || 3 --> FINALIZAÇÕES
    int i;
    for (i = 0; i < tamGrafo; i++) // Inicializando cor e pi com BRANCO e -1
    {
        Matriz[0][i] = 0; // COR BRANCA
        Matriz[1][i] = -1;
    }

    int u, posu; // posu seria a posição de u ... vai ser usado para indice de vetores ex: cor[posu]
    item *aux = L->inicio;
    while (aux != NULL) // para percorrer todos os vertices do Grafo ...
    {
        u = aux->numero;
        posu = InformaPosicao(L, u);

        if (Matriz[0][posu] == 0) // DENTRO É O DFS-VISIT(u)
        {
            DFS_VISIT(Matriz, u, L);
        }
        aux = aux->baixo;
    }

    aux = L->inicio;
    printf("\n   BUSCA EM PROFUNDIDADE");
    printf("\n Vertice   d     f    pai\n");
    for (i = 0; i < tamGrafo; i++)
    {
        printf("   %2d     %2d    %2d    %2d\n", aux->numero, Matriz[2][i], Matriz[3][i], Matriz[1][i]); // Cor não precisa ser printada ...
        aux = aux->baixo;
    }
    printf("\nOBS: Pai igual (-1) quer dizer que nao existe.\n");

    FreeMatrizDinamica(4, Matriz);
    return 0;
}

void DFS_VISIT(int **M, int u, ListaDinamica *L) // Função usada em "BuscaEmProfundidade"
{
    // Matriz[0] --> COR
    // Matriz[1] --> PAI
    // Matriz[2] --> DISTANCIA
    // Matriz[3] --> FINALIZAÇÕES

    int posu = InformaPosicao(L, u);
    int v, posv;

    M[0][posu] = 1; // COR CINZA
    tempo = tempo + 1;
    M[2][posu] = tempo;

    item *auxA = RetornaArestasDadoVertice(L, u);
    while (auxA != NULL) // enquanto tiver arestas no vertice ... vai fazer isso:
    {
        v = auxA->numero;
        posv = InformaPosicao(L, v);
        if (M[0][posv] == 0)
        {
            M[1][posv] = u;
            DFS_VISIT(M, v, L); // a variavel tempo está global ...
        }
        auxA = auxA->prox;
    }
    M[0][posu] = 2; // COR PRETA
    tempo = tempo + 1;
    M[3][posu] = tempo;
}

// ===================================== FUNÇOES PARA ALGORITMO DE PRIM ========================================
int AlgoritmoPrim(ListaDinamica *L, int Vinicio) // Função usada na "main"
{
    // CHECKLIST DE VERIFICAÇÃO DO GRAFO CONEXO OU NÃO                               STATUS    RETURN
    //      * VERIFICAR SE O GRAFO ESTÁ VAZIO OU NÃO                                  OK!       (-2)
    //      * VERIFICAR SE VINICIO EXISTE NO GRAFO                                    OK!       (-3)
    //      * VERIFICAR SE O GRAFO É CONEXO ANTES DE EXECUTAR O PRIM                  OK!       (-1)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    int retorno = VerificaGrafoConexo(L); // se vc quer Gerar uma Arvore minima o grafo precisa ser conexo...
    // para fazer sentido ... então vamos chamar a função para validar se o grafo é conexo ou não ...
    // Parametro dele vai ser a busca em largura ...

    if (retorno == -2)
    {
        return -2; // GRAFO VAZIO ....
    }

    if (retorno == -1)
    {
        return -1; // Grafo não conexo
    }
    printf("\n\nUsando a Busca em Largura para determinar: Grafo Conexo !!!\n");
    printf("Como o Grafo e CONEXO o ALGORITMO DE PRIM DO GRAFO E:\n");

    int cont = 0;
    item *aux = L->inicio;
    while (aux != NULL)
    {
        if (aux->numero == Vinicio)
        {
            cont++;
            break; // se achou n precisa percorer o grafo inteiro, pois só existe um vertice
        }
        aux = aux->baixo;
    }

    if (cont == 0)
    {
        return -3; // retorno (-3) quer dizer que não existe o Vinicio no Grafo.
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    int tamGrafo = L->quantV;
    int **key, i;

    key = AlocaMatrizDinamica(3, tamGrafo); // onde linha 0 é os indices e linha 1 seria o proprio key 2 para pai

    aux = L->inicio;
    for (i = 0; i < tamGrafo; i++)
    {
        key[0][i] = aux->numero; // indice dos vertices
        key[1][i] = MAX;         // MAX é um define ... mais facil para modificar ...
        key[2][i] = -1;          // NIL
        aux = aux->baixo;
    } // 0 para indice || 1 para key || 2 para pai

    int posicao; // seria a posicao do indice do Vertice Inicio no vetor ...
    posicao = InformaPosicao(L, Vinicio);
    key[1][posicao] = 0; // setando o key dele para 0

    FilaDinamica Q; // Criando e setando a Fila Dinamica ...
    Q.quant = 0;
    Q.inicio = NULL;
    Q.fim = NULL;

    aux = L->inicio;
    while (aux != NULL) // Inserindo todos os vertices na Fila
    {
        i = aux->numero;
        InsereFila(&Q, i);
        aux = aux->baixo;
    }

    int u;
    int v, posv;

    while (Q.quant != 0) // copia do pseudo codigo do slide ...
    {
        u = Extract_MIN(&Q, key);

        aux = RetornaArestasDadoVertice(L, u); // vai pegar o vertice u e retornar as arestas dele ...
        while (aux != NULL)                    // enquanto tiver arestas ...
        {
            v = aux->numero;             // V seria o numero do vertice da aresta de u
            posv = InformaPosicao(L, v); // Posicao do V em relação ao vetor

            if ((Informa_Numero_Esta_Fila(&Q, v) == 1) && aux->P_Aresta < key[1][posv])
            {
                key[2][posv] = u;
                key[1][posv] = aux->P_Aresta;
            }
            aux = aux->prox;
        }
    }

    printf("\n  ALGORITMO DE PRIM");
    printf("\n Vertice   Pai   Key\n");
    for (i = 0; i < tamGrafo; i++)
    {
        printf("   %2d      %2d    %2d\n", key[0][i], key[2][i], key[1][i]);
    }
    printf("\nOBS: Pai igual (-1) quer dizer que nao existe.\n");
    FreeMatrizDinamica(3, key);

    return 1;
}

int Extract_MIN(FilaDinamica *F, int **Key) // Função usada em "AlgoritmoPrim"
{
    int valor; // vou retornar o ->numero removido ...

    if (F->quant != 0) // Se a fila estiver vazia não faz sentido tirar algo dela
    {
        fila *aux;
        if (F->quant == 1) // se tiver só um elemento vou dar free nele e depois criar uma nova lista ...
        {
            valor = F->inicio->numero; // retornar numero
            aux = F->inicio;
            free(aux);
            aux = NULL;

            // Setando parametros pois estou criando uma "nova" lista
            F->quant = 0;
            F->inicio = NULL;
            F->fim = NULL;
            return valor;
        }

        else
        {
            int menorV = -1, menorK, numero; // MENOR VERTICE && MENOR KEY
            int i;

            aux = F->inicio;
            do
            {
                numero = aux->numero;

                i = 0;
                while (Key[0][i] != numero)
                {
                    i++;
                }

                if (Key[1][i] != MAX)
                {
                    menorV = Key[0][i]; // vertice e n key
                    menorK = Key[1][i]; // key
                }
                else
                {
                    aux = aux->prox;
                }
            } while (menorV == (-1)); // setei o numero como (-1) ... só vai sair do loop se ele achou um numero !=
            //  tudo isso para pegar o key de menor valor para comparar depois

            aux = F->inicio;
            while (aux != NULL)
            {
                numero = aux->numero;

                i = 0;
                while (Key[0][i] != numero)
                {
                    i++;
                }

                if (Key[1][i] < menorK) // tanto faz < e <= a arvore minima sera a mesma
                {
                    menorK = Key[1][i]; // armazenando o key menor
                    menorV = Key[0][i]; // armazenando o vertice menor
                }
                aux = aux->prox;
            }
            // Esse Loop é para pegar o menor KEY definitivo ... isto é, ele vai comparar os numeros da fila com o
            // menorK que pegamos no começo da função ...

            if (F->inicio->numero == menorV) // Se o menorV está no inicio da Fila
            {
                valor = F->inicio->numero;
                aux = F->inicio;
                F->inicio = aux->prox;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }

            else if (F->fim->numero == menorV) // Se o menorV está no final da Fila
            {
                valor = F->fim->numero;
                aux = F->fim;

                fila *anterior = F->inicio;
                while (anterior->prox->numero != F->fim->numero)
                {
                    anterior = anterior->prox;
                }

                F->fim = anterior;
                anterior->prox = NULL;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }

            else // Se menorV está entre o Inicio e Final da Fila
            {
                aux = F->inicio->prox;
                fila *auxA = F->inicio;
                while (aux->numero != menorV)
                {
                    auxA = auxA->prox; // auxA de anterior
                    aux = aux->prox;
                }
                valor = aux->numero;
                auxA->prox = aux->prox;
                aux->prox = NULL;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }
        }
        return -1;
    }
    return -1; // pois quant é == 0
}

int Informa_Numero_Esta_Fila(FilaDinamica *F, int numero) // Função usada em "AlgoritmoPrim"
{
    // RETORNA 1 SE ACHOU O NUMERO NA FILA && RETORNA (-1) SE NÃÃO ACHOU O NUMERO
    if (F->quant != 0)
    {
        fila *aux = F->inicio;
        while (aux != NULL)
        {
            if (aux->numero == numero)
            {
                return 1;
            }
            aux = aux->prox;
        }
        return -1;
    }
    return -1;
}

// ===================================== FUNÇOES PARA ALGORITMO DE DIJKSTRA =====================================
int Dijkstra(ListaDinamica *L, int Vinicio)
{ // CHECKLIST DE VERIFICAÇÃO DO GRAFO CONEXO OU NÃO                                 STATUS    RETURN
    //      * VERIFICAR SE O GRAFO ESTÁ VAZIO OU NÃO                                  OK!       (-2)
    //      * VINICIO NÃO PERTECE AO GRAFO                                            OK!       (-3)

    // --> COMEÇA AQUI A PARTE DE VERIFICAÇÂO ...
    if (L->quantV == 0) // verificando se grafo está vazio
    {
        return -2; // retorno para Grafo Vazio
    }

    int cont = 0;
    item *aux = L->inicio;

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
        return -3; // Retorno (-1) para Vinicio não pertence ao Grafo
    }
    // --> TERMINA AQUI A PARTE DE VERIFICAÇÂO ...

    int tamGrafo = L->quantV;
    int **Matriz_Dijkstra = Initialize_Single_Source(L, Vinicio);
    // 0 --> INDICE || 1 --> DISTANCIA || 2 --> PAI

    FilaDinamica Q;
    Q.quant = 0;
    Q.inicio = NULL;
    Q.fim = NULL;

    aux = L->inicio;
    int vertice;

    while (aux != NULL) // colocando todos os vertices do grafo na fila dinamica ...
    {
        vertice = aux->numero;
        InsereFila(&Q, vertice);
        aux = aux->baixo;
    }

    int u, v;
    while (Q.quant != 0) // copia do pseudo codigo slide ...
    {
        u = Extract_MIN_Dijkstra(&Q, Matriz_Dijkstra);

        aux = RetornaArestasDadoVertice(L, u);
        while (aux != NULL)
        {
            v = aux->numero;

            Relax(L, u, v, Matriz_Dijkstra);
            aux = aux->prox;
        }
    }

    printf("\nALGORITMO DE DIJKSTRA");
    printf("\n Vertice   pai    d\n");
    int i;
    for (i = 0; i < tamGrafo; i++)
    {
        printf("   %2d      %2d    %2d\n", Matriz_Dijkstra[0][i], Matriz_Dijkstra[2][i], Matriz_Dijkstra[1][i]);
    }

    FreeMatrizDinamica(3, Matriz_Dijkstra);
    return 1;
}

int **Initialize_Single_Source(ListaDinamica *L, int Vinicio) // Usado na Função "Dijkstra"
{
    int i, tamanho = L->quantV;
    item *aux = L->inicio;

    int **Matriz = AlocaMatrizDinamica(3, tamanho);

    for (i = 0; i < tamanho; i++)
    {
        Matriz[0][i] = aux->numero;
        Matriz[1][i] = MAX; // para distancia
        Matriz[2][i] = -1;  // para pai
        aux = aux->baixo;
    } // 0 --> INDICE || 1 --> DISTANCIA || 2 --> PAI

    int posicao = InformaPosicao(L, Vinicio);

    Matriz[1][posicao] = 0;
    return Matriz;
}

void Relax(ListaDinamica *L, int u, int v, int **Matriz) // Usado na Função "Dijkstra"
{
    int posu, posv;

    posu = InformaPosicao(L, u);
    posv = InformaPosicao(L, v);

    item *aux = L->inicio;

    while (aux->numero != u)
    {
        aux = aux->baixo;
    }

    aux = aux->prox;

    while (aux->numero != v)
    {
        aux = aux->prox;
    }

    if (Matriz[1][posv] > (Matriz[1][posu] + aux->P_Aresta))
    {
        Matriz[1][posv] = Matriz[1][posu] + aux->P_Aresta;
        Matriz[2][posv] = u;
    }
}

int Extract_MIN_Dijkstra(FilaDinamica *F, int **Matriz) // Usado na Função "Dijkstra"
{
    int valor; // vou retornar o ->numero removido ...

    if (F->quant != 0) // Se a fila estiver vazia não faz sentido tirar algo dela
    {
        fila *aux;
        if (F->quant == 1) // se tiver só um elemento vou dar free nele e depois criar uma nova lista ...
        {
            valor = F->inicio->numero; // retornar numero
            aux = F->inicio;
            free(aux);
            aux = NULL;

            // Setando parametros pois estou criando uma "nova" lista
            F->quant = 0;
            F->inicio = NULL;
            F->fim = NULL;
            return valor;
        }

        else
        {
            int menorV = -1, menorD, numero; // MENOR VERTICE && MENOR DISTANCIA
            int i;

            aux = F->inicio;
            do
            { // 0 --> INDICE || 1 --> DISTANCIA || 2 --> PAI
                numero = aux->numero;

                i = 0;
                while (Matriz[0][i] != numero)
                {
                    i++;
                }

                if (Matriz[1][i] != MAX)
                {
                    menorV = Matriz[0][i]; // vertice
                    menorD = Matriz[1][i]; // distancia
                }
                else
                {
                    aux = aux->prox;
                }
            } while (menorV == (-1)); // setei o numero como (-1) ... só vai sair do loop se ele achou um numero !=
            // tudo isso para pegar a distancia de menor valor para comparar depois

            aux = F->inicio;
            while (aux != NULL)
            {
                numero = aux->numero;

                i = 0;
                while (Matriz[0][i] != numero)
                {
                    i++;
                }

                if (Matriz[1][i] < menorD)
                {
                    menorD = Matriz[1][i]; // armazenando a menor distancia
                    menorV = Matriz[0][i]; // armazenando o vertice menor
                }
                aux = aux->prox;
            }
            // Loop responsavel por pegar a menor distancia da fila ... ele vai comparar os numeros da fila com o MenorD
            // Lembrando que o menorD pegamos no começo da função ...

            if (F->inicio->numero == menorV) // Se o menorV está no inicio da Fila ...
            {
                valor = F->inicio->numero;
                aux = F->inicio;
                F->inicio = aux->prox;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }

            else if (F->fim->numero == menorV) // Se o menorV está no final da Fila ...
            {
                valor = F->fim->numero;
                aux = F->fim;

                fila *anterior = F->inicio;
                while (anterior->prox->numero != F->fim->numero)
                {
                    anterior = anterior->prox;
                }

                F->fim = anterior;
                anterior->prox = NULL;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }

            else // Se o menorV esta entre o Inicio e Final da Fila
            {
                aux = F->inicio->prox;
                fila *auxA = F->inicio;
                while (aux->numero != menorV)
                {
                    auxA = auxA->prox; // auxA para anterior
                    aux = aux->prox;
                }
                valor = aux->numero;
                auxA->prox = aux->prox;
                aux->prox = NULL;
                free(aux);
                aux = NULL;

                F->quant--;
                return valor;
            }
        }
        return -1;
    }
    return -1; // pois quant é igual zero
}
