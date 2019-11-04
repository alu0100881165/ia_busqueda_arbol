#include "arbol_t.hpp"
#include <fstream>
#include <locale>
#include <algorithm>

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




int main (int argc, char** argv)      //pongo char** para que almacene los nombres correctamente
{
  cout << "Bienvenido" << endl;

  ifstream graph_file(argv[1]), heuristic_file;                       //Variables con los ficheros
  string graph_line, graph_line_fixed, heuristic_line, string_aux;    //Variables para almacenar contenido fichero y formatearlo
  int tam = 0, int_aux = 0, int_dummy = 0, cont = 0;                  //Variables de tamaño, y auxiliares

  if(graph_file.is_open())        //Comprobar que el fichero este abierto
  {
    graph_file >> tam;
    // cout << "Tamaño: " << tam << endl;

    int int_max = numeric_limits<int>::max();
    vector<vector<int>> nodos_fichero(tam, vector<int>(tam - 1));
    // vector<vector<int>> nodos_fichero(tam);

    int_aux = tam;

    while(int_aux > 0)        //Con esto creo un vector con el tamaño para almacenar los datos del fichero.
    {
      int_aux--;
      int_dummy += int_aux;
    }

    vector<int> vector_int_aux(int_dummy);    //Vector que almacena los datos del fichero de datos

    while(!graph_file.eof())
    {
      getline(graph_file, graph_line, ' ');       //Solo cogemos los datos hasta un espacio
      if(graph_line.size() > 0)
      {
        if(graph_line[0] == '\n')
          graph_line = graph_line.erase(0, 1);        //Eliminanmos el retorno de carro

        for(int i = 0; i < graph_line.size(); i++)
        {
          if(isdigit(graph_line[i]))                //Comprobamos si el valor es numerico para eliminar cualquier otro valor que no sea un número
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

        getline(graph_file, graph_line);      //Desechamos el resto de datos de la linea.
        graph_line_fixed.clear();             //Vaciamos el string para la siguiente ejecución, ya que usamos push back
      }
    }

    // nodos_fichero = formatear_vector(vector_int_aux, tam);
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

    arbol_t Grafo_busqueda(nodos_fichero, tam, ini, fin);

  }
  else
  {
    cout << "No se pudo abrir el fichero: " << argv[1];
    return 1;
  }


  return 0;
}
