#include "a_star_t.hpp"


astar_t::astar_t()
{

}

astar_t::astar_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin)
{
  arbol_busqueda_ = new arbol_t(vector_formateado, vector_heuristico, size, ini, fin);
  nodos_generados_ = 1;
  nodos_inspeccionados_ = 0;
}

int astar_t::busqueda(void)
{
  int tentative_cost = 0;  //posible valor g
  node_t *current;
  open_list_.push_back(arbol_busqueda_->get_nodo_arbol());    //ponemos el nodo inicial en la openlist
  // cout << "Empezamos en el nodo: " << arbol_busqueda_->get_nodo_arbol()->get_name() << endl;
  int fin = arbol_busqueda_->get_fin();
  // cout << "Buscamos al nodo: " << arbol_busqueda_->get_fin() << endl;

  while(!open_list_.empty())    //hasta que la open lis no este vacía no paramos de iterar
  {
    // cout << "Iterando." << endl;
    if(open_list_.size() == 1)
    {
      current = open_list_[0];
      current->set_coste_acumulado(0);
      current->set_coste_f_total();
    }
    else
    {
      current = get_lowest_f();
    }
    nodos_inspeccionados_++;
    cout << "El nodo seleccionado es: " << current->get_name() << endl;
    cout << "Contenido de la open list: " << endl;
    for(int i = 0; i < open_list_.size(); i++)
    {
      cout << '\t' << open_list_[i]->get_name() << ' ' << open_list_[i]->get_coste_acumulado() << endl;
    }
    cout << endl;

    open_list_.erase(open_list_.begin() + get_open_list_pos(current));
    closed_list_.push_back(current);

    if(current->get_name() == fin)  //comprobamos si es el final
    {
      write_resultado(current);
      return 0;       //devolvemos 0 para indicar que lo encontramos
    }

    // generar_hijos(current, open_list_);

    for(int i = 0; i < current->get_next_nodes_size(); i++)
    {
      nodos_generados_++;
      cout << "Iteramos sus hijos." << endl;
      cout << "hijo: " << current->get_next_node_pos(i)->get_name() << endl;
      tentative_cost = current->get_coste_acumulado() + current->get_next_node_cost_pos(i);
      cout << "Coste tentativo: " << tentative_cost << endl;
      cout << "Coste movimiento del nodo: " << current->get_next_node_cost_pos(i) << endl;
      if(find(open_list_.begin(), open_list_.end(), current->get_next_node_pos(i)) != open_list_.end())   //comprobamos si existe el nodo en la open list
      {
        // cout << "holi1" << endl;
        if(current->get_next_node_cost_pos(i) <= tentative_cost)      //si esto se cumple, el camino no es mejor.
        {
          if(current->get_next_node_pos(i)->get_coste_acumulado() > tentative_cost)
          {
            current->get_next_node_pos(i)->set_coste_acumulado_to_value(tentative_cost);
            current->get_next_node_pos(i)->set_padre(current);
          }
          continue;
        }
      }
      else if(find(closed_list_.begin(), closed_list_.end(), current->get_next_node_pos(i)) != closed_list_.end()) //comprobamos si existe el nodo en la closed list
      {
        // cout << "holi2" << endl;
        if(current->get_next_node_cost_pos(i) <= tentative_cost)
        {
          // cout << "holi2.2" << endl;
          continue;
        }
        // cout << "holi2.3" << endl;
        closed_list_.erase(remove(closed_list_.begin(), closed_list_.end(), current->get_next_node_pos(i)), closed_list_.end());    //eliminar elemento del vector closed
        open_list_.push_back(current->get_next_node_pos(i));        //añadimos el elemento a la open list
      }
      else
      {
        // cout << "holi3" << endl;
        open_list_.push_back(current->get_next_node_pos(i));

      }
      // cout << "holi4" << endl;
      current->get_next_node_pos(i)->set_coste_acumulado(tentative_cost);
      current->get_next_node_pos(i)->set_padre(current);
      current->get_next_node_pos(i)->set_coste_f_total();
      cout << "El padre es: " << current->get_next_node_pos(i)->get_padre()->get_name() << endl;
      cout << "Coste de actual a hijo: " << current->get_next_node_cost_pos(i) << endl;
      cout << "Coste heurístico: " << current->get_next_node_pos(i)->get_coste_heuristico() << endl;
      cout << "Valor f: " << current->get_next_node_pos(i)->get_coste_f_total() << endl;
      getchar();
    }
  }
  // cout << "Estoy acabando." << endl;
  if(current->get_name() != fin)
    return 1;   //significa que no ha encontrado el nodo
}

// void astar_t::generar_hijos(node_t *actual, vector<node_t*> &lista_abierta)
// {
//   for(int i = 0; i < actual->get_next_nodes_size(); i++)
//   {
//     lista_abierta.push_back(actual->get_next_node_pos(i));
//     // cout << "Nodo hijo: " << actual->get_next_node_pos(i)->get_name() << "\tSu padre es ahora: " << actual->get_next_node_pos(i)->get_padre()->get_name() << endl;
//     // cout << "El nodo actual tiene coste heuristico: " << actual->get_next_node_pos(i)->get_coste_heuristico() << " un coste acumulado de: " << actual->get_next_node_pos(i)->get_coste_acumulado() << " y un coste f total de: " << actual->get_next_node_pos(i)->get_coste_f_total() << endl;
//   }
// }

node_t* astar_t::get_lowest_f(void)
{
  int nodo_coste = numeric_limits<int>::max();
  node_t* to_return;

  for(int i = 0; i < open_list_.size(); i++)
  {
    if(open_list_[i]->get_coste_f_total() < nodo_coste)
    {
      nodo_coste = open_list_[i]->get_coste_f_total();
      to_return = open_list_[i];
    }
  }

  return to_return;
}

int astar_t::get_open_list_pos(node_t* to_find)
{
  int to_return = 0;

  for(int i = 0; i < open_list_.size(); i++)
  {
    if(open_list_[i] == to_find)
    {
      to_return = i;
      break;
    }
  }

  return to_return;
}

void astar_t::write_resultado(node_t *final)
{
  vector<int> to_print;

  cout << "Hemos encontrado el nodo: " << arbol_busqueda_->get_fin() << endl;
  cout << "Se han generado: " << nodos_generados_ << " nodos." << endl;
  cout << "Se han inspeccionado: " << nodos_inspeccionados_ << " nodos." << endl;
  cout << "El coste total es de: " << final->get_coste_f_total() << endl;

  do
  {
    to_print.push_back(final->get_name());
    final = final->get_padre();
  }
  while(final->get_padre() != NULL);

  to_print.push_back(final->get_name());

  cout << "La ruta a seguir es la siguiente: " << endl << '\t';
  for(int i = (to_print.size() - 1); i >= 0; i--)
  {
    cout << to_print[i] << ' ';
  }
  cout << endl;
}

ostream& astar_t::write(ostream& os)
{
  arbol_busqueda_->write(os);
}
