#include "arbol_t.hpp"

arbol_t::arbol_t()
{

}

arbol_t::arbol_t(vector<vector<int>> &vector_formateado, vector<int> &vector_heuristico, int size, int ini, int fin)
{
  cout << "Entro arbol constructor." << endl;

  if(size > 0)        //comprobar que hay nodos que leer
    set_size(size);

  set_ini(ini);       //nombre del nodo inicial
  set_fin(fin);       //nombre del nodo a buscar

  int cont = 0;       //variable auxiliar, que permite recorrer el vector de nodos con el formato del vector_formateado.
  node_t *dummy;      //nodo auxiliar
  // vector<node_t*> vector_dummy(size);   //vector de nodos auxiliar para almacenar el set de nodos
  for(int i = 0; i < size; i++)     //for para crear todos los nodos con su nombre correspondiente
  {
    dummy = new node_t((i + 1), vector_heuristico[i]);
    if((i + 1) == ini)
    {
      cout << "Nombre nodo: " << dummy->get_name() << endl;
      set_nodo_arbol(dummy);
      dummy->set_padre(NULL);
    }
    vector_dummy.push_back(dummy);
  }

  for(int i = 0; i < vector_formateado.size(); i++)           //recorremos el vetor_formateado para almacenar sus valores en los nodos correspondientes
  {
    for(int j = 0; j < vector_formateado[i].size(); j++)
    {
      if(i == j)      // con esta comprobación, nos aseguramos de escoger el nodo correcto, ya que para la pos vector_formateado[0], el segundo vector tiene almacenados los nodos 2, 3, 4, 5, etc. pero no el uno, con esto saltamos ese nodo
        cont++;
      if(vector_formateado[i][j] != numeric_limits<int>::max()) //comprobamos que al nodo hijo se pueda llegar
      {
        vector_dummy[i]->set_hijo(vector_dummy[cont], vector_formateado[i][j]);
      }
      cont++;
    }
    cont = 0;
  }

  // write(vector_dummy, cout);
}

void arbol_t::set_size(int size)
{
  size_ = size;
}

int arbol_t::get_size(void)
{
  return size_;
}

int arbol_t::get_size(void) const
{
  return size_;
}

void arbol_t::set_ini(int ini)
{
  ini_ = ini;
}

int arbol_t::get_ini(void)
{
  return ini_;
}

int arbol_t::get_ini(void) const
{
  return ini_;
}

void arbol_t::set_fin(int fin)
{
  fin_ = fin;
}

int arbol_t::get_fin(void)
{
  return fin_;
}

int arbol_t::get_fin(void) const
{
  return fin_;
}

void arbol_t::set_nodo_arbol(node_t *nodo)
{
  nodo_arbol_ = nodo;
}

node_t* arbol_t::get_nodo_arbol(void)
{
  return nodo_arbol_;
}

node_t* arbol_t::get_nodo_arbol(void) const
{
  return nodo_arbol_;
}

// ostream& arbol_t::write(vector<node_t*> prueba, ostream& os)
// {
//   cout << "Nodo inicial: " << get_ini() << endl;
//   cout << "Nodo final: " << get_fin() << endl;
//   cout << "Nodos: " << endl;
//   for(int i = 0; i < prueba.size(); i++)
//     prueba[i]->write(os);
//   return os;
// }

ostream& arbol_t::write(ostream& os)
{
  cout << "Nodo inicial: " << get_ini() << endl;
  cout << "Nodo final: " << get_fin() << endl;
  cout << "Nodos: " << endl;
  for(int i = 0; i < vector_dummy.size(); i++)
    vector_dummy[i]->write(os);
  return os;
}

arbol_t& arbol_t::operator= (const arbol_t &to_assing)
{
  nodo_arbol_ = to_assing.get_nodo_arbol();
  size_ = to_assing.get_size();
  ini_ = to_assing.get_ini();
  fin_ = to_assing.get_fin();

  return *this;
}
