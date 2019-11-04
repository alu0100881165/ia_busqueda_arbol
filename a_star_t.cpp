#include "a_star_t.hpp"


astar_t::astar_t()
{

}

astar_t::astar_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin)
{
  arbol_busqueda_ = new arbol_t(vector_formateado, vector_heuristico, size, ini, fin);
}

void astar_t::busqueda(void)
{
  int node_coste = 0;
  open_list_.push_back(arbol_busqueda_->get_nodo_arbol());

  while(!open_list_.empty())
  {
    for(int i = 0; i < open_list_.size(); i++)
    {
      node_coste = open_list_[i]->
    }
  }
}

ostream& astar_t::write(ostream& os)
{
  arbol_busqueda_->write(os);
}
