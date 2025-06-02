#include "task.hpp"
#include <cctype>
#include <iostream>
#include <string>

/**
 * @brief Exibe o menu principal e retorna a opção escolhida pelo usuário.
 *
 * @return Um caractere representando a opção selecionada:
 *         'i' - Inserir tarefa
 *         'r' - Remover por ID
 *         'p' - Remover por prioridade
 *         'b' - Buscar por ID
 *         'e' - Exibir todas as tarefas ordenadas
 */
char obterOpcao() {
  std::cout << "Bem-vindo ao Sistema de Gerenciamento de tarefas." << '\n'
            << "Opções disponíveis: " << '\n'
            << "Digite \"i\" para inserir uma nova tarefa" << '\n'
            << "Digite \"r\" para remover uma tarefa pelo ID" << '\n'
            << "Digite \"p\" para remover as tarefas de determinada prioridade" << '\n'
            << "Digite \"b\" para buscar uma tarefa pelo ID" << '\n'
            << "Digite \"e\" para exibir as tarefas ordenadas por prioridade" << '\n'
            << "Digite \"s\" para sair.\n";

  char opcao;

  do {
    std::cout << "Digite uma opção válida (i, r, p, b, e, s): ";
    std::cin >> opcao;            //!< Pega a opção que o usuário escolher
    opcao = std::tolower(opcao);  //!< Para aceitar maiúsculas ou minúsculas
  } while (opcao != 'i' && opcao != 'r' && opcao != 'p' && opcao != 'b' && opcao != 'e'
           && opcao != 's');

  return opcao;
}

/**
 * @brief Cria uma tarefa a partir do input do usuário
 *
 * @return Uma estrutura Tarefa com a descrição passada pelo usuário
 */

Tarefa criarTarefa() {
  Tarefa tarefa_atual;
  std::cout << "Digite o ID da tarefa: ";
  std::cin >> tarefa_atual.id;
  std::cin.ignore();
  std::cout << "Qual a tarefa?\n";
  std::getline(std::cin, tarefa_atual.descricao);
  do {
    std::cout << "Qual a prioridade? <1 (alta), 2 (média), 3 (baixa)>\n";
    std::cin >> tarefa_atual.prioridade;
  } while (tarefa_atual.prioridade < 1
           || tarefa_atual.prioridade > 3);  //!< Validar apenas os números 1, 2 e 3
  return tarefa_atual;
}

/**
 * @brief Função auxiliar para encontrar a última tarefa da LSE
 *
 * @param L: aponta pro início da LSE
 *
 * @return O último nó inserido na lista
 */
Node* acharUltimo(Node* L) {
  Node* prev{ nullptr };
  while (L != nullptr) {  //!< Loop para percorrer a lista até encontrar o último nó
    prev = L;
    L = L->next;
  }
  return prev;
}

/**
 * @brief Insere a nova tarefa no final da LSE
 *
 * @param L: aponta pro início da LSE
 * @param tarefa: a nova tarefa a ser inserida
 */
void inserirTarefa(Node*& L, const Tarefa& tarefa) {
  Node* novaTarefa = new Node{ tarefa, nullptr };  //!< Cria um novo nó com a tarefa
  Node* ultimo = acharUltimo(L);                   //!< Busca o último nó da lista
  if (ultimo == nullptr) {
    L = novaTarefa;  //!< Lista estava vazia, novo nó passa a ser o primeiro
  } else {
    ultimo->next = novaTarefa;  //!< Tarefa conectada ao final da lista
  }
}

/**
 * @brief Remove a tarefa de determinado ID
 *
 * @param L: aponta para o início da LSE
 *
 */
void removerPorId(Node*& L) {
  if (L == nullptr)
    return;  //!< Lista vazia
  std::cout << "Inserir o ID da tarefa a ser deletada: ";
  int id;
  std::cin >> id;

  Node* atual = L;
  Node* anterior = nullptr;

  while (atual != nullptr) {
    if (atual->tarefa.id == id) {
      if (anterior == nullptr) {  //!< Nó a ser removido é o primeiro da lista
        L = atual->next;
      } else {
        anterior->next = atual->next;  //!< Desconecta o nó target da lista
      }
      delete atual;  //!< Libera memória
      std::cout << "Tarefa removida!\n";
      return;
    }

    anterior = atual;
    atual = atual->next;
  }

  std::cout << "Tarefa com id " << id << " não encontrada\n";
}

/**
 * @brief Remove as tarefas de determinada prioridade
 *
 * @param L: aponta para o início da LSE
 *
 * */
void removerPorPrioridade(Node*& L) {
  if (L == nullptr)
    return;  //!< Lista vazia
  std::cout << "Inserir a prioridade a ser deletada <(1) alta, (2) média, (3) baixa>: ";
  int prioridade;
  std::cin >> prioridade;

  Node* atual = L;
  Node* anterior = nullptr;

  while (atual != nullptr) {
    if (atual->tarefa.prioridade == prioridade) {
      Node* proximo = atual->next;  //!< Salva o próximo nó antes de deletar

      if (anterior == nullptr) {  //!< Nó a ser removido é o primeiro
        L = proximo;              //!< Lista começa no nó seguinte
      } else {
        anterior->next = proximo;  //!< Desconecta o nó target da lista
      }

      delete atual;
      atual = proximo;  //!< Avança usando o ponteiro salvo
    } else {            //!< Segue percorrendo a lista
      anterior = atual;
      atual = atual->next;
    }
  }

  std::cout << "Tarefas de prioridade " << prioridade << " deletadas com sucesso!\n";
}

/**
 * @brief Busca a tarefa de determinado id e exibe as informações
 *
 * @param L: aponta para o início da LSE
 *
 * */
void buscarPorId(const Node* L) {
  if (L == nullptr) {  //!< Lista vazia
    std::cout << "A lista de tarefas está vazia!";
    return;
  }
  std::cout << "Inserir o ID da tarefa a ser buscada: ";
  int id;
  std::cin >> id;

  while (L != nullptr) {
    if (L->tarefa.id == id) {
      std::cout << "Seguem as informações da tarefa de id " << id << ":\n"
                << "Descrição da tarefa: " << L->tarefa.descricao << "\n"
                << "Prioridade: " << L->tarefa.prioridade << "\n";
      return;
    }
    L = L->next;
  }

  std::cout << "ERRO: Não há tarefa com o ID escolhido!";
}

/**
 * @brief Exibe a lista das tarefas ordenadas por prioridade
 *
 * @param L: ponteiro para o início da LSE
 *
 */
void printOrdenado(Node* L) {
  if (L == nullptr) {  //!< Lista vazia
    std::cout << "Lista vazia\n";
    return;
  }
  std::cout << "Tarefas de prioridade ALTA: \n";
  for (Node* p = L; p != nullptr; p = p->next) {
    if (p->tarefa.prioridade == 1) {
      std::cout << p->tarefa.id << ": " << p->tarefa.descricao << "\n";
    }
  }
  std::cout << "Tarefas de prioridade MEDIA: \n";
  for (Node* p = L; p != nullptr; p = p->next) {
    if (p->tarefa.prioridade == 2) {
      std::cout << p->tarefa.id << ": " << p->tarefa.descricao << "\n";
    }
  }
  std::cout << "Tarefas de prioridade BAIXA: \n";
  for (Node* p = L; p != nullptr; p = p->next) {
    if (p->tarefa.prioridade == 3) {
      std::cout << p->tarefa.id << ": " << p->tarefa.descricao << "\n";
    }
  }
}

/**
 * @brief: Deleta a lista ao fim do programa para evitar vazamentos de memória
 */
void deletarLista(Node*& L) {
  while (L != nullptr) {
    Node* temp = L;
    L = L->next;
    delete temp;
  }
}
