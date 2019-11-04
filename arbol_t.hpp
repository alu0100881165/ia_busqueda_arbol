#pragma once

#include "node_t.hpp"

class arbol_t
{
  private:
    node_t* nodo_arbol;           //puntero al nodo inicial
    int size_;                    //número de nodos
    int ini_;                     //identificador del nodo inicial
    int fin_;                     //identificador del nodo final

  public:
    arbol_t();
    arbol_t(vector<vector<int>> vector_formateado, int size, int ini, int fin);

    void set_size(int size);
    int get_size(void);

    void set_ini(int ini);
    int get_ini(void);

    void set_fin(int fin);
    int get_fin(void);

    void set_nodo_arbol(node_t *nodo);
    node_t* get_nodo_arbol(void);

    ostream& write(vector<node_t*> prueba, ostream& os);
};
