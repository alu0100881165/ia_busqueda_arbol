#include "node_t.hpp"

node_t::node_t()
{}

node_t::node_t(int nombre)
{
  // cout << "El nombre es: " << nombre << endl;
  set_name(nombre);
}

int node_t::get_name(void)
{
  return name_;
}

void node_t::set_name(int nombre)
{
  // cout << "Entro nodo set_name(1)." << endl;
  name_ = nombre;
}

void node_t::set_hijo(node_t *hijo, int value)
{
  pair<node_t*,int> aux;
  aux.first = hijo;
  aux.second = value;
  // int pos = next_nodes_.size();
  next_nodes_.push_back(aux);
  // cout << "\t\t set hijo del nodo: " << this->get_name() << "\tCuyo hijo es: " << next_nodes_[pos].first->get_name() << " | " << next_nodes_[pos].second << endl;
}

void node_t::set_padre(node_t *padre)
{
  cout << "El padre es: " << endl;
  padre_ = padre;
  if(padre_ != NULL)
    cout << padre->get_name();
  else
    cout << "Es NULL" << endl;
}


ostream& node_t::write(ostream& os)
{
  cout << "\tNodo llamado: " << name_ << ", puede llegar a: " << endl;
  for(int i = 0; i < next_nodes_.size(); i++)
  {
    cout << "\t\t" << next_nodes_[i].first->get_name() << '|' << next_nodes_[i].second << endl;
  }
  cout << endl;
}
