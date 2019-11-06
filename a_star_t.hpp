#pragma once

#include "arbol_t.hpp"

#include <algorithm>

class astar_t
{
  private:
    arbol_t *arbol_busqueda_;
    vector<node_t*> open_list_;
    vector<node_t*> closed_list_;
    int nodos_generados_;
    int nodos_inspeccionados_;

  public:
    astar_t();
    astar_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin);

    int busqueda(void);

    // void generar_hijos(node_t *actual, vector<node_t*> &lista_abierta);
    node_t* get_lowest_f(void);
    int get_open_list_pos(node_t* to_find);
    void write_resultado(node_t *final);

    ostream& write(ostream& os);
};
