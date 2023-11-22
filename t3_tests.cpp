#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <ranges>
#include <numeric>
#include <thread>
#include <unordered_map>
#include <limits>
#include <set>
#include <cstring>
#include "lib/FlowGraph.h"

int ITERATIONS; //Variável que define quantidade de execuções para serem realizadas
int GENERATE_FLOW_ALLOCATION_OUTPUT; //Variável que define se deverá ou não escrever as alocações de fluxo em um arquivo


using namespace std;

void parse_arguments(int argc, char *argv[])
{
  // Set default values
  ITERATIONS = 10;
  GENERATE_FLOW_ALLOCATION_OUTPUT = 0; // 0 Para não gerar, 1 para gerar

  for (int i = 1; i < argc; i++)
  {
    if (!strcmp(argv[i], "--iterations") || !strcmp(argv[i], "-i"))
    {
      if ((i + 1 < argc) && (atoi(argv[i + 1]) >= 0)) {
            ITERATIONS = atoi(argv[i + 1]);
            i++;
        } else {
            printf("Erro: A flag -i requer um valor positivo.\n");
            exit(1);
        }
    }
    else if (!strcmp(argv[i], "--flowoutput") || !strcmp(argv[i], "-f"))
    {
      if ((i + 1 < argc) && ((atoi(argv[i + 1]) == 0) || (atoi(argv[i + 1]) == 1))) {
            GENERATE_FLOW_ALLOCATION_OUTPUT = atoi(argv[i + 1]);
            i++;
        } else {
            printf("Erro: A flag -f requer 1 ou 0.\n");
            exit(1);
        }
    }
    else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
    {
      printf("\n");
      printf("Usage: ./t3_tests.o [OPTIONS]\n\n");
      printf("Options:\n");
      printf("  -h  --help               Exibe essa mensagem\n");
      printf("  -i  --iterations         Define o número máximo de iterações\n");
      printf("  -f  --flowoutput         Define se será gerado um arquivo com as alocações de fluxo (1 para gerar, 0 para não gerar) (para esse caso, é recomendado 1 igual a 1\n");
      printf("\n");
      exit(0);
    }
    else
    {
      printf("Unrecognized argument '%s' (try '--help')\n", argv[i]);
      exit(1);
    }
  }
}


void test(FlowGraph& graph, int graph_number=0, int iterations=10, const string& output_filename="") {
    // Essa função é utilizada para executar o estudo de caso de acordo com o número recebido
    float max_flow;
    int source = 1;
    int sink = 2;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i <= iterations; ++i) {        

        max_flow = graph.ford_fulkerson(source, sink, output_filename).first;
        
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = duration_cast<chrono::microseconds>(stop - start);
    auto duration_ms = duration.count() / 1000.0;
    
    cout << "Fluxo máximo para o grafo " + to_string(graph_number) + " " + to_string(max_flow) << endl;
    cout << "Tempo de execução médio " + to_string(duration_ms/iterations) + " ms" << endl;

};





int main(int argc, char *argv[]) {
    try {
        string filename = "";

        parse_arguments(argc, argv);
        
        for (int i = 1; i <= 6; ++i) {
            FlowGraph g("./graphs/grafo_rf_" + to_string(i) + ".txt");

            if (GENERATE_FLOW_ALLOCATION_OUTPUT == 1) {
                string filename = "flow_allocation_graph_" + to_string(i) + ".txt";
            }

            cout << "Iniciando teste para o grafo: " + to_string(i) << endl;
            test(g, i, ITERATIONS, filename);
            cout << "---------------------" << endl;
            
        }
                

    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
