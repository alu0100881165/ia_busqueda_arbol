#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

typedef pair<int, int> Pair;

class node_t
{
  private:
    int name_;                  //identificador del nodo
    vector<pair<node_t*,int>> next_nodes_;  //vector de hijos con el coste g
    int coste_heuristico_;    //valor heuristico del nodo
    node_t *padre_;               //nodo padre del actual
    int coste_acumulado_;
    int coste_f_total_;

  public:
    node_t();
    node_t(int nombre, int coste_heuristico);

    int get_name(void);
    int get_name(void) const;
    void set_name(int nombre);

    void set_coste_heuristico(int vector_heuristico);
    int get_coste_heuristico(void);
    int get_coste_heuristico(void) const;

    void set_hijo(node_t *hijo, int value);

    node_t* get_padre(void);
    node_t* get_padre(void) const;
    void set_padre(node_t *padre);

    int get_coste_acumulado(void);
    int get_coste_acumulado(void) const;
    void set_coste_acumulado(int coste);

    int get_coste_f_total(void);
    int get_coste_f_total(void) const;
    void set_coste_f_total(void);

    int get_next_nodes_size(void);
    int get_next_nodes_size(void) const;
    node_t* get_next_node_pos(int pos);
    node_t* get_next_node_pos(int pos) const;
    int get_next_node_cost_pos(int pos);
    int get_next_node_cost_pos(int pos) const;

    ostream& write(ostream& os);

    bool compare_next_nodes(const node_t &to_compare2) const;

    bool operator== (const node_t &to_compare2);
};
