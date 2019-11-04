#pragma once

#include "arbol_t.hpp"

class astar_t
{
  private:
    arbol_t *arbol_busqueda_;
    vector<node_t*> open_list_;
    vector<node_t*> closed_list_;

  public:
    astar_t();
    astar_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin);

    void busqueda(void);

    ostream& write(ostream& os);
};
