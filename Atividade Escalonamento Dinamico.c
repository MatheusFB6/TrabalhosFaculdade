#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100
#define QUANTUM 2 // quantum para RR

typedef struct {
    int id;
    int chegada;
    int duracao;
    int duracao_restante;
    int prioridade;
    int inicio;
    int termino;
    bool executado;
    bool iniciado;
} Processo;

void reset_processos(Processo *p, Processo *backup, int n) {
    for (int i = 0; i < n; i++) {
        p[i] = backup[i];
        p[i].duracao_restante = p[i].duracao;
        p[i].executado = false;
        p[i].iniciado = false;
        p[i].inicio = -1;
        p[i].termino = -1;
    }
}

void imprimir_tabela(Processo *p, int n, const char *titulo) {
    printf("\n===== %s =====\n", titulo);
    printf("Proc\tTcheg\tTcpu\tPrior\tTresp\tTret\tTesp\n");
    for (int i = 0; i < n; i++) {
        char nome_proc = 'A' + (p[i].id - 1); // P1 → A, P2 → B...
        int tresp = p[i].inicio - p[i].chegada;
        int tret = p[i].termino - p[i].chegada;
        int tesp = tret - p[i].duracao;
        printf("%c\t%d\t%d\t%d\t%d\t%d\t%d\n",
               nome_proc, p[i].chegada, p[i].duracao,
               p[i].prioridade, tresp, tret, tesp);
    }
}


// FCFS
void fcfs(Processo *p, int n) {
    int tempo = 0;
    for (int i = 0; i < n; i++) {
        if (tempo < p[i].chegada)
            tempo = p[i].chegada;
        p[i].inicio = tempo;
        tempo += p[i].duracao;
        p[i].termino = tempo;
    }
    imprimir_tabela(p, n, "FCFS");
}

// HRRN
void hrrn(Processo *p, int n) {
    int tempo = 0, completados = 0;
    while (completados < n) {
        int idx = -1;
        double hrr_max = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].executado && p[i].chegada <= tempo) {
                double r = (double)(tempo - p[i].chegada + p[i].duracao) / p[i].duracao;
                if (r > hrr_max) {
                    hrr_max = r;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            tempo++;
        } else {
            p[idx].inicio = tempo;
            tempo += p[idx].duracao;
            p[idx].termino = tempo;
            p[idx].executado = true;
            completados++;
        }
    }
    imprimir_tabela(p, n, "HRRN");
}

// SRTF
void srtf(Processo *p, int n) {
    int tempo = 0, completados = 0;
    while (completados < n) {
        int menor = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].executado && p[i].chegada <= tempo && p[i].duracao_restante > 0) {
                if (menor == -1 || p[i].duracao_restante < p[menor].duracao_restante)
                    menor = i;
            }
        }
        if (menor == -1) {
            tempo++;
            continue;
        }
        if (!p[menor].iniciado) {
            p[menor].inicio = tempo;
            p[menor].iniciado = true;
        }
        p[menor].duracao_restante--;
        tempo++;
        if (p[menor].duracao_restante == 0) {
            p[menor].termino = tempo;
            p[menor].executado = true;
            completados++;
        }
    }
    imprimir_tabela(p, n, "SRTF");
}

// Round Robin
void round_robin(Processo *p, int n) {
    int tempo = 0, completados = 0;
    int fila[MAX];
    int ini = 0, fim = 0;
    bool na_fila[MAX] = {false};

    while (completados < n) {
        for (int i = 0; i < n; i++) {
            if (!na_fila[i] && p[i].chegada <= tempo && p[i].duracao_restante > 0) {
                fila[fim++] = i;
                na_fila[i] = true;
            }
        }
        if (ini == fim) {
            tempo++;
            continue;
        }
        int idx = fila[ini++];
        if (ini == MAX) ini = 0;

        if (!p[idx].iniciado) {
            p[idx].inicio = tempo;
            p[idx].iniciado = true;
        }

        int exec = (p[idx].duracao_restante > QUANTUM) ? QUANTUM : p[idx].duracao_restante;
        tempo += exec;
        p[idx].duracao_restante -= exec;

        for (int i = 0; i < n; i++) {
            if (!na_fila[i] && p[i].chegada > tempo - exec && p[i].chegada <= tempo) {
                fila[fim++] = i;
                na_fila[i] = true;
            }
        }

        if (p[idx].duracao_restante > 0) {
            fila[fim++] = idx;
        } else {
            p[idx].termino = tempo;
            p[idx].executado = true;
            completados++;
        }
    }

    imprimir_tabela(p, n, "Round Robin");
}

// Prioridade Preemptiva
void prioridade_preemptiva(Processo *p, int n) {
    int tempo = 0, completados = 0;
    while (completados < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].executado && p[i].chegada <= tempo) {
                if (idx == -1 || p[i].prioridade < p[idx].prioridade)
                    idx = i;
            }
        }
        if (idx == -1) {
            tempo++;
            continue;
        }
        if (!p[idx].iniciado) {
            p[idx].inicio = tempo;
            p[idx].iniciado = true;
        }

        p[idx].duracao_restante--;
        tempo++;

        if (p[idx].duracao_restante == 0) {
            p[idx].termino = tempo;
            p[idx].executado = true;
            completados++;
        }
    }

    imprimir_tabela(p, n, "Prioridade com Preempçao");
}

// Menu
void menu() {
    printf("\nEscolha o algoritmo de escalonamento:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. HRRN (Highest Response Ratio Next)\n");
    printf("3. SRTF (Shortest Remaining Time First)\n");
    printf("4. Round Robin\n");
    printf("5. Prioridade com Preempção\n");
    printf("0. Sair\n");
    printf("Opção: ");
}

int main() {
    int n = 5;
    Processo processos[] = {
        {1, 12, 7, 7, 4, -1, -1, false, false}, // A
        {2, 5, 3, 3, 3, -1, -1, false, false},  // B
        {3, 2, 2, 2, 1, -1, -1, false, false},  // C
        {4, 13, 4, 4, 2, -1, -1, false, false}, // D
        {5, 14, 1, 1, 5, -1, -1, false, false}  // E
    };
    Processo backup[5];
    memcpy(backup, processos, sizeof(processos));

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);

        reset_processos(processos, backup, n);

        switch (opcao) {
            case 1: fcfs(processos, n); break;
            case 2: hrrn(processos, n); break;
            case 3: srtf(processos, n); break;
            case 4: round_robin(processos, n); break;
            case 5: prioridade_preemptiva(processos, n); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

