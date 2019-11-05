#include "node_t.hpp"

node_t::node_t()
{}

node_t::node_t(int nombre, int coste_heuristico)
{
  // cout << "El nombre es: " << nombre << endl;
  set_coste_acumulado(0);
  set_coste_f_total();
  set_name(nombre);
  set_coste_heuristico(coste_heuristico);
}

int node_t::get_name(void)
{
  return name_;
}

int node_t::get_name(void) const
{
  return name_;
}

void node_t::set_name(int nombre)
{
  // cout << "Entro nodo set_name(1)." << endl;
  name_ = nombre;
}

void node_t::set_coste_heuristico(int vector_heuristico)
{
  coste_heuristico_ = vector_heuristico;
}

int node_t::get_coste_heuristico(void)
{
  return coste_heuristico_;
}

int node_t::get_coste_heuristico(void) const
{
  return coste_heuristico_;
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

node_t* node_t::get_padre(void)
{
  return padre_;
}

node_t* node_t::get_padre(void) const
{
  return padre_;
}

void node_t::set_padre(node_t *padre)
{
  // cout << "El padre es: " << endl;
  padre_ = padre;
  // if(padre_ != NULL)
  //   cout << padre->get_name();
  // else
  //   cout << "Es NULL" << endl;
}

int node_t::get_coste_acumulado(void)
{
  return coste_acumulado_;
}

int node_t::get_coste_acumulado(void) const
{
  return coste_acumulado_;
}

void node_t::set_coste_acumulado(int coste)
{
  coste_acumulado_ += coste;
}

int node_t::get_coste_f_total(void)
{
  return coste_f_total_;
}

int node_t::get_coste_f_total(void) const
{
  return coste_f_total_;
}

void node_t::set_coste_f_total(void)
{
  coste_f_total_ = coste_heuristico_ + coste_acumulado_;
}

int node_t::get_next_nodes_size(void)
{
  return next_nodes_.size();
}

int node_t::get_next_nodes_size(void) const
{
  return next_nodes_.size();
}

node_t* node_t::get_next_node_pos(int pos)
{
  return next_nodes_[pos].first;
}

node_t* node_t::get_next_node_pos(int pos) const
{
  return next_nodes_[pos].first;
}

int node_t::get_next_node_cost_pos(int pos)
{
  return next_nodes_[pos].second;
}

int node_t::get_next_node_cost_pos(int pos) const
{
  return next_nodes_[pos].second;
}

ostream& node_t::write(ostream& os)
{
  cout << "\tNodo llamado: " << name_ << ", puede llegar a: " << endl;
  for(int i = 0; i < next_nodes_.size(); i++)
  {
    cout << "\t\t" << next_nodes_[i].first->get_name() << '|' << next_nodes_[i].second << endl;
  }
  cout << "\tSu valor heuristico es: " << coste_heuristico_ << endl;
  cout << endl;
}

bool node_t::compare_next_nodes(const node_t &to_compare2) const
{
  bool dummy = true;
  for(int i = 0; i < get_next_nodes_size(); i++)
  {
    if(get_next_node_pos(i)->get_name() == to_compare2.get_next_node_pos(i)->get_name() || get_next_node_cost_pos(i) == to_compare2.get_next_node_cost_pos(i))
      dummy = false;
  }
  return dummy;
}

bool node_t::operator== (const node_t &to_compare2)
{
  return (get_name() == to_compare2.get_name() &&
  get_next_nodes_size() == to_compare2.get_next_nodes_size() &&
  compare_next_nodes(to_compare2) &&
  get_coste_heuristico() == to_compare2.get_coste_heuristico() &&
  get_padre()->get_name() == to_compare2.get_padre()->get_name() &&
  get_coste_acumulado() == to_compare2.get_coste_acumulado() &&
  get_coste_f_total() == to_compare2.get_coste_f_total());
}
