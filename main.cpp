#include "task.hpp"

int main() {
  Node* lista{ nullptr };  //!< Inicia lista encadeada
  char opcao;

  do {
    opcao = obterOpcao();

    switch (opcao) {
    case 'i': {
      Tarefa t = criarTarefa();
      inserirTarefa(lista, t);
      break;
    }
    case 'r':
      removerPorId(lista);
      break;
    case 'p':
      removerPorPrioridade(lista);
      break;
    case 'b':
      buscarPorId(lista);
      break;
    case 'e':
      printOrdenado(lista);
      break;
    case 's':
      deletarLista(lista);  //!< Libera a memória
      return 0;
    }
  } while (true);  //!< Sair do programa com CTRL+C
}
