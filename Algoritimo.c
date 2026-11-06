#include <stdio.h>

#define MAX 10

void salvar(char nome[], int v[], int n) {
    FILE *f = fopen(nome, "w");
    if (f == NULL) return;
    for (int i = 0; i < n; i++)
        fprintf(f, "%d\n", v[i]);
    fclose(f);
}

int ler(int v[]) {
    FILE *f = fopen("dados.txt", "r");
    int n = 0;
    if (f == NULL) return 0;
    while (n < MAX && fscanf(f, "%d", &v[n]) == 1)
        n++;
    fclose(f);
    return n;
}

void bubbleSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (v[j] > v[j + 1]) {
                int t = v[j];
                v[j] = v[j + 1];
                v[j + 1] = t;
            }
}

void mostrar(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int main() {
    int v[MAX], n, op, p, valor, resposta;

    do {
        printf("\n1-Criar arquivo\n2-Ler dados\n");
        printf("3-Ordenar (Bubble Sort)\n4-Alterar valor\n5-Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Digite os 10 numeros:\n");
                for (int i = 0; i < MAX; i++) {
                    printf("Numero %d: ", i + 1);
                    scanf("%d", &v[i]);
                }
                salvar("dados.txt", v, MAX);
                printf("Arquivo criado com sucesso!\n");
                break;

            case 2:
                n = ler(v);
                if (n > 0) mostrar(v, n);
                else printf("Arquivo vazio ou inexistente.\n");
                break;

            case 3:
                n = ler(v);
                if (n <= 0) {
                    printf("Sem dados para ordenar.\n");
                    break;
                }
                bubbleSort(v, n);
                mostrar(v, n);
                salvar("ordenado.txt", v, n);
                printf("Ordenacao salva com sucesso!\n");
                break;

            case 4:
                n = ler(v);
                if (n <= 0) break;
                mostrar(v, n);
                printf("Posicao (1 a %d): ", n);
                scanf("%d", &p);
                if (p < 1 || p > n) {
                    printf("Posicao invalida.\n");
                    break;
                }
                printf("Novo valor: ");
                scanf("%d", &valor);
                v[p - 1] = valor;
                salvar("dados.txt", v, n);
                printf("Ordenar novamente? 1-Sim / 0-Nao: ");
                scanf("%d", &resposta);
                if (resposta == 1) {
                    bubbleSort(v, n);
                    salvar("ordenado.txt", v, n);
                    mostrar(v, n);
                }
                break;

            case 5:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (op != 5);

    return 0;
}