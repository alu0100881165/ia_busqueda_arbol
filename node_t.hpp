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
    node_t *padre_;               //nodo padre del actual

  public:
    node_t();
    node_t(int nombre);

    int get_name(void);
    void set_name(int nombre);

    void set_hijo(node_t *hijo, int value);
    void set_padre(node_t *padre);

    ostream& write(ostream& os);

};
