#include "a_star_t.hpp"


astar_t::astar_t()
{

}

astar_t::astar_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin)
{
  arbol_busqueda_ = new arbol_t(vector_formateado, vector_heuristico, size, ini, fin);
}

int astar_t::busqueda(void)
{
  int node_coste = 0, nodo_coste_max = numeric_limits<int>::max(), tentative_cost = 0;  //posible valor g
  node_t *current;
  open_list_.push_back(arbol_busqueda_->get_nodo_arbol());    //ponemos el nodo inicial en la openlist
  // cout << "Empezamos en el nodo: " << arbol_busqueda_->get_nodo_arbol()->get_name() << endl;
  int fin = arbol_busqueda_->get_fin();
  // cout << "Buscamos al nodo: " << arbol_busqueda_->get_fin() << endl;

  while(!open_list_.empty())    //hasta que la open lis no este vacía no paramos de iterar
  {
    if(open_list_.size() == 1)
    {
      current = open_list_[0];
      current->set_coste_acumulado(0);
      current->set_coste_f_total();
      open_list_.erase(open_list_.begin() + 0);
      closed_list_.push_back(current);
    }
    else
    {
      // for(int i = 0; i < open_list_.size(); i++)  //recorremos la openlist para elegir el nodo con el menor coste
      // {
      //   node_coste = open_list_[i]->    //el coste se calcula mediante f = g + h del nodo actual
      //   if(nodo_coste_max > nodo_coste)
      //     nodo_coste_max = nodo_coste;
      // }
    }
    if(current->get_name() == fin)  //comprobamos si es el final
    {
      cout << "Encontrado: " << current->get_name() << endl;
      return 0;       //devolvemos 0 para indicar que lo encontramos
    }

    for(int i = 0; i < current->get_next_nodes_size(); i++)
    {
      tentative_cost = current->get_coste_acumulado() + current->get_next_node_cost_pos(i);
      if(find(open_list_.begin(), open_list_.end(), current->get_next_node_pos(i)) != open_list_.end())   //comprobamos que exista el nodo en la open list
      {
        if(current->get_next_node_cost_pos(i) <= tentative_cost)      //si esto se cumple, el camino no es mejor.
          continue;
      }
      else if(find(closed_list_.begin(), closed_list_.end(), current->get_next_node_pos(i)) != closed_list_.end())
      {
        if(current->get_next_node_cost_pos(i) <= tentative_cost)
          continue;
        closed_list_.erase(remove(closed_list_.begin(), closed_list_.end(), current->get_next_node_pos(i)), closed_list_.end());    //eliminar elemento del vector closed
        open_list_.push_back(current->get_next_node_pos(i));        //añadimos el elemento a la open list
      }
      else
      {
        open_list_.push_back(current->get_next_node_pos(i));
      }
      current->get_next_node_pos(i)->set_coste_acumulado(current->get_next_node_cost_pos(i));
      current->get_next_node_pos(i)->set_padre(current);
      actual->get_next_node_pos(i)->set_coste_f_total();
    }
    break;


  }
  return 1;   //significa que no ha encontrado el nodo
}

// void astar_t::generar_hijos(node_t *actual, vector<node_t*> &lista_abierta)
// {
//   for(int i = 0; i < actual->get_next_nodes_size(); i++)
//   {
//     lista_abierta.push_back(actual->get_next_node_pos(i));
//     actual->get_next_node_pos(i)->set_padre(actual);
//     actual->get_next_node_pos(i)->set_coste_acumulado(actual->get_next_node_cost_pos(i));
//     actual->get_next_node_pos(i)->set_coste_f_total();
//     cout << "Nodo hijo: " << actual->get_next_node_pos(i)->get_name() << "\tSu padre es ahora: " << actual->get_next_node_pos(i)->get_padre()->get_name() << endl;
//     cout << "El nodo actual tiene coste heuristico: " << actual->get_next_node_pos(i)->get_coste_heuristico() << " un coste acumulado de: " << actual->get_next_node_pos(i)->get_coste_acumulado() << " y un coste f total de: " << actual->get_next_node_pos(i)->get_coste_f_total() << endl;
//   }
// }

ostream& astar_t::write(ostream& os)
{
  arbol_busqueda_->write(os);
}
