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

char obterOpcao();           //!< Mostra o menu e obtém a opção do usuário
Tarefa criarTarefa();        //!< Cria uma tarefa a partir do input do usuário
Node* acharUltimo(Node* L);  //!< Função auxiliar para achar o último nó da lista
void inserirTarefa(Node*& L, const Tarefa& tarefa);  //!< Insere uma tarefa no final da LSE
void removerPorId(Node*& L);          //!< Remove uma tarefa específica ao encontrar o ID
void removerPorPrioridade(Node*& L);  //!< Remove as tarefas de uma prioridade
void buscarPorId(const Node* L);      //!< Busca uma tarefa pelo ID e exibe as informações
void printOrdenado(Node* L);          //!< Exibe a lista ordenada por prioridade
void deletarLista(Node*& L);          //!< Libera a memória da LSE

#endif
