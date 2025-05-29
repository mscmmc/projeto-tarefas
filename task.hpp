#ifndef TASK_HPP
#define TASK_HPP

#include <string>

struct Tarefa {
  int id;
  std::string descricao;
  int prioridade;  //!< 1 (alta), 2 (média), 3 (baixa)
};

struct Node {
  Tarefa tarefa;
  Node* next;
};

Node* criarNode(Tarefa tarefa_atual);  //!< Cria um nó a partir de uma tarefa
Node* acharUltimo(const Node* L);      //!< Função auxiliar para achar o último nó da lista
void inserirTarefa(Node*& L, const Tarefa& tarefa);  //!< Insere uma tarefa no final da LSE
void removerPorId(int id, Node*& L);  //!< Remove uma tarefa específica ao encontrar o ID
void removerPorPrioridade(int prioridade, Node*& L);  //!< Remove as tarefas de uma prioridade
void buscarPorId(int id, const Node* L);  //!< Busca uma tarefa pelo ID e exibe as informações
void printOrdenado(Node* L);              //!< Exibe a lista ordenada por prioridade
void deletarLista(Node*& L);              //!< Libera a memória da LSE

#endif
