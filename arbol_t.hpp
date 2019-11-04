#pragma once

#include "node_t.hpp"

class arbol_t
{
  private:
    node_t* nodo_arbol_;           //puntero al nodo inicial
    vector<node_t*> vector_dummy;
    int size_;                    //número de nodos
    int ini_;                     //identificador del nodo inicial
    int fin_;                     //identificador del nodo final

  public:
    arbol_t();
    arbol_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin);

    void set_size(int size);
    int get_size(void);
    int get_size(void) const;

    void set_ini(int ini);
    int get_ini(void);
    int get_ini(void) const;

    void set_fin(int fin);
    int get_fin(void);
    int get_fin(void) const;

    void set_nodo_arbol(node_t *nodo);
    node_t* get_nodo_arbol(void);
    node_t* get_nodo_arbol(void) const;

    // ostream& write(vector<node_t*> prueba, ostream& os);
    ostream& write(ostream& os);

    arbol_t& operator= (const arbol_t &to_assing);
};
