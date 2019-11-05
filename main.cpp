#include "a_star_t.hpp"
#include <fstream>
#include <locale>

using namespace std;

//método que recibe el vector que se lee desde fichero, y lo formatea para la contrucción de nodos.
void formatear_vector(vector<int> vector_formatear, vector<vector<int>> &vector_return, int size)
{
  int cont = 0, int_aux = 0, int_dummy = 0;
  // vector<vector<int>> vector_return(size, vector<int>(size - 1));

  for(int i = 0; i < (vector_formatear.size() + 1); i++)
  {
    if(cont == (size - 1))
    {
      cont = 0;
      int_dummy = 0;
      int_aux++;
    }
    while(int_dummy < int_aux)
    {
      vector_return[int_aux][cont] = vector_return[int_dummy][(int_aux - 1)];
      int_dummy++;
      cont++;
    }
    if(i < vector_formatear.size())
    {
      vector_return[int_aux][cont] = vector_formatear[i];
      // cout << "Pos i: " << int_aux << "    Pos j: " << cont << "\t Valor a introducir: " << vector_formatear[i] << "       Valor introducido: " << vector_return[int_aux][cont] << endl;
      cont++;
    }
  }
}

int leer_ficheros(ifstream& graph_file, ifstream& heuristic_file, int& tam, vector<int>& vector_int_aux, vector<int>& vector_heuristica)
{
  string graph_line, graph_line_fixed, heuristic_line, heuristic_line_fixed, string_aux;    //Variables para almacenar contenido fichero y formatearlo
  int int_aux = 0, int_dummy = 0, cont = 0, tam_heur = 0;                  //Variables de tamaño, y auxiliares

  graph_file >> tam;
  heuristic_file >> tam_heur;

  if(tam == tam_heur)
  {
    int int_max = numeric_limits<int>::max();

    int_aux = tam;

    while(int_aux > 0)        //Con esto creo un vector con el tamaño para almacenar los datos del fichero.
    {
      int_aux--;
      int_dummy += int_aux;
    }

    vector_int_aux.resize(int_dummy);    //Vector que almacena los datos del fichero de datos
    vector_heuristica.resize(tam);

    while(!graph_file.eof())
    {
      getline(graph_file, graph_line);       //Solo cogemos los datos hasta un espacio
      if(graph_line.size() > 0)
      {
        if(graph_line[0] == '\n')
          graph_line = graph_line.erase(0, 1);        //Eliminanmos el retorno de carro

        for(int i = 0; i < graph_line.size(); i++)
        {
          if(i == 0 && (graph_line[i] == '-' || isdigit(graph_line[i])))
            graph_line_fixed.push_back(graph_line[i]);
          else if(isdigit(graph_line[i]))                //Comprobamos si el valor es numerico para eliminar cualquier otro valor que no sea un número
          {
            graph_line_fixed.push_back(graph_line[i]);
          }
        }

        if(isdigit(graph_line[0]))
        {
          int_aux = stoi(graph_line_fixed);         //Convertimos el valor del string a un entero
        }
        else
        {
          int_aux = int_max;     //Si es infinito, asignamos el núm más grande representable
        }

        vector_int_aux[cont] = int_aux;         //Insertamos al vector el valor numérico.
        cont++;                                 //Aumentamos el contador del vector

        // cout << "Valor en entero: " << int_aux << endl;

        // getline(graph_file, graph_line);      //Desechamos el resto de datos de la linea.
        graph_line_fixed.clear();             //Vaciamos el string para la siguiente ejecución, ya que usamos push back
      }
    }

    graph_file.close();

    cont = 0;

    while(!heuristic_file.eof())
    {
      getline(heuristic_file, heuristic_line);       //Solo cogemos los datos hasta un espacio
      if(heuristic_line.size() > 0)
      {
        if(heuristic_line[0] == '\n')
          heuristic_line = heuristic_line.erase(0, 1);        //Eliminanmos el retorno de carro

        for(int i = 0; i < heuristic_line.size(); i++)
        {
          if(isdigit(heuristic_line[i]))                //Comprobamos si el valor es numerico para eliminar cualquier otro valor que no sea un número
          {
            heuristic_line_fixed.push_back(heuristic_line[i]);
          }
        }

        int_aux = stoi(heuristic_line_fixed);         //Convertimos el valor del string a un entero

        vector_heuristica[cont] = int_aux;         //Insertamos al vector el valor numérico.
        cont++;                                   //Aumentamos el contador del vector

        heuristic_line_fixed.clear();             //Vaciamos el string para la siguiente ejecución, ya que usamos push back
      }
    }

    heuristic_file.close();

    return 0;
  }
  else
  {
    cout << "Los tamaños entre los ficheros no coinciden" << endl;
    return 1;
  }
}

int main (int argc, char** argv)      //pongo char** para que almacene los nombres correctamente
{
  cout << "Bienvenido" << endl;

  ifstream graph_file(argv[1]);
  ifstream heuristic_file(argv[2]);                       //Variables con los ficheros
  int tam = 0, check = 0;
  vector<int> vector_int_aux;     //Vector que almacena los datos del fichero de costes
  vector<int> vector_heuristica;  //Vector que almacena los datos del fichero de heuristica

  if(graph_file.is_open() && heuristic_file.is_open())        //Comprobar que el fichero este abierto
  {
    check = leer_ficheros(graph_file, heuristic_file, tam, vector_int_aux, vector_heuristica);
    if(check == 1)    //si devuelve 1, el numero de nodos especificado en cada fichero es diferente
      return 1;

    vector<vector<int>> nodos_fichero(tam, vector<int>(tam - 1));
    formatear_vector(vector_int_aux, nodos_fichero, tam);

    // cout << endl << endl;
    cout << "Contenido de nodos_fichero: " << endl;
    for(int i = 0; i < nodos_fichero.size(); i++)
    {
      for(int j = 0; j < nodos_fichero[i].size(); j++)
      {
        cout << nodos_fichero[i][j] << '|';
      }
      cout << endl;
    }

    cout << endl << endl;

    int ini = 0, fin = 0;
    cout << "Indique el nodo inicial: ";
    cin >> ini;
    cout << endl;

    cout << "Indique el nodo final: ";
    cin >> fin;
    cout << endl;

    if(ini < 0 || ini > tam)
    {
      cout << "Inicial fuera de rango." << endl;
      return 1;
    }

    if(fin < 0 || fin > tam)
    {
      cout << "Final fuera de rango." << endl;
      return 1;
    }

    astar_t A_estrella(nodos_fichero, vector_heuristica, tam, ini, fin);
    A_estrella.write(cout);

    A_estrella.busqueda();

  }
  else
  {
    cout << "No se pudo abrir el fichero: " << argv[1] << endl;
    return 1;
  }


  return 0;
}
