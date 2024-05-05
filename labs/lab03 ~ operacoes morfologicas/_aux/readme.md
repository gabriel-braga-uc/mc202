# lab 03 ~ Operações Morfológicas em imagens binárias pelo conceito de adjacência.
Adjacência de 3x3.

Operações:
- Dilatação;
- Erosão;
- Abertura;
- Fechamento;
    
    # Dilatação:
    Para cada P sendo um pixel da imagem binária, **P toma o valor do maior elemento em sua área de adjacência** (3x3).
    
    # Erosão:
    Para cada P sendo um pixel da imagem binária, **P toma o valor do menor elemento em sua área de adjacência** (3x3).
    
    # Abertura:
    Combinação de Dilatação e Erosão:  **Erosão → Dilatação**.
    
    # Fechamento:
    Combinação de Dilatação e Erosão:  **Dilatação → Erosão**.
    

## Implementações necessárias no código auxiliar (12):
```c
/*1*/  bool ListaSimplesVazia(ListaSimples *inicio){}
/*2*/  bool BuscaUltimoElementoListaSimples(ListaSimples *inicio, NoListaSimples **pos, NoListaSimples **ant){}
/*3*/  NoListaSimples *CriaNoSimples(int elem){}
/*4*/  void InserirElementoNoFimLista(ListaSimples **inicio, int valor){}
/*5*/  bool RemoveInicioListaSimples(ListaSimples **inicio, int *elem){}
/*6*/  void DestroiListaLigada(ListaSimples **inicio){}
/*7*/  NoListaSimples *ObterNo(NoListaSimples *noAtual, int indice){}
/*8*/  Pixel *ObterAdjacentes(Pixel P){}
/*9*/  void Dilatacao(NoListaSimples **noAtual, int n, int m){}
/*10*/ void Erosao(NoListaSimples **noAtual, int n, int m) {}
/*11*/ void Abertura(NoListaSimples **noAtual, int n, int m){}
/*12*/ void Fechamento(NoListaSimples **noAtual, int n, int m){}
```
