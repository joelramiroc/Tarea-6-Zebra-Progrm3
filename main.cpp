#include <iostream>
#include <list>
#include <fstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include "Pais.h"
#include "Evaluador.h"
#include "NodoNario.h"

using namespace std;
int TAMANO_DE_REGISTRO=15;
//Escribe "pais" en un achivo con nombre "nombre_archivo" en la posicion "posicion"
//Nota: Se deben poder agregar varios registros en un solo archivo
void escribir(string nombre_archivo, Pais*pais, int posicion)
{
    ofstream out(nombre_archivo.c_str(),ios::in | ios::out);
  if(!out.is_open())
  {
    out.open(nombre_archivo.c_str());
  }

  out.seekp(posicion*TAMANO_DE_REGISTRO);
  out.write(pais->nombre.c_str(),10);
  out.write((char*)&pais->habitantes,4);
  out.write((char*)&pais->hablan_espanol,1);
  out.close();
}

//Devuelve un pais previamente escrito (con la funcion escribir()) en el archivo con nombre "nombre_archivo" en la posicion "posicion"
//Nota: Se deben poder leer varios registros de un archivo
Pais* leer(string nombre_archivo, int posicion)
{


     ifstream in(nombre_archivo.c_str());
     in.seekg(posicion*TAMANO_DE_REGISTRO);

      int habitantes;
      char espan;
      char nombre[10];

      in.read(nombre,10);
      in.read((char*)&habitantes,4);
      in.read(&espan,1);

    Pais *pais = new Pais(nombre,habitantes,espan);
    return pais;
}

//Devuelve suma de habitantes de paises que hablan espanol en el archivo con nombre "nombre_archivo"
//Nota: Los registros se deben de haber guardado previamente con la funcion escribir()
int contarHispanohablantes(string nombre_archivo)
{

  ifstream in(nombre_archivo.c_str(), ios::ate);
  int cantidad_r = in.tellg()/TAMANO_DE_REGISTRO;
  int suma = 0;
  for(int i=0;i<cantidad_r;i++)
  {
      if(leer(nombre_archivo, i)->hablan_espanol)
      {
          suma+=leer(nombre_archivo, i)->habitantes;
      }
  }
    in.close();

  return suma;

}

//Devuelve un set que contenga los numeros fibonacci.
//La cantidad de numeros que contiene se determina por el parametro "cantidad"
set<int> getNumerosFibonacci(int cantidad)
{
    set<int>respuesta;
    int pN=1,sG=1,t=0;
    for(int i=0;i<cantidad;i++)
    {
        if(i==0)
        {
        respuesta.insert(0);
        }else if(i==1 || i==2)
        {
        respuesta.insert(1);
        }else
        {
        t=pN+sG;
        respuesta.insert(t);
        sG=pN;
        pN=t;
        }
    }

    return respuesta;
}

//Devuelve la cantidad de letras mayusculas presentes en "a" y "b"
int contarMayusculas(stack<char> a,queue<char> b)
{
    int cantidad=0;
    while(!a.empty())
    {
        if(a.top()=='A' || a.top()=='B' || a.top()=='C' || a.top()=='D' || a.top()=='E' || a.top()=='F' || a.top()=='G' ||
           a.top()=='H' || a.top()=='I' || a.top()=='J' || a.top()=='K' || a.top()=='L' || a.top()=='M' || a.top()=='N' ||
           a.top()=='O' || a.top()=='P' || a.top()=='Q' || a.top()=='R' || a.top()=='S' || a.top()=='T' || a.top()=='U' ||
           a.top()=='V' || a.top()=='W' || a.top()=='X' || a.top()=='Y' || a.top()=='Z')
        {
            cantidad++;
        }
        a.pop();
    }

    while(!b.empty()){
        if(b.front()=='A' || b.front()=='B' || b.front()=='C' || b.front()=='D' || b.front()=='E' || b.front()=='F' || b.front()=='G' ||
           b.front()=='H' || b.front()=='I' || b.front()=='J' || b.front()=='K' || b.front()=='L' || b.front()=='M' || b.front()=='N' ||
           b.front()=='O' || b.front()=='P' || b.front()=='Q' || b.front()=='R' || b.front()=='S' || b.front()=='T' || b.front()=='U' ||
           b.front()=='V' || b.front()=='W' || b.front()=='X' || b.front()=='Y' || b.front()=='Z')
        {
            cantidad++;
        }
        b.pop();
    }


    return cantidad;
}

//Devuelve la cantidad de llaves repetidas en "mi_multimapa"
//Nota: No devuelve la cantidad de repeticines
int contarLLavesRepetidas(multimap<string,string>mi_multimapa)
{
    map<string,string> temporal;
    for(multimap<string,string>::iterator i= mi_multimapa.begin(); i!= mi_multimapa.end(); i++)
    {
        pair<string,string>par_actual = *i;
        temporal [par_actual.first] = par_actual.second;
    }
    int repetidas = (mi_multimapa.size()- temporal.size());
    return repetidas;
}

//Devuelve true si y solo si "buscado" existe en el arbol nario "raiz"
bool existe(NodoNario* raiz,int buscado)
{
    if(raiz==NULL)
    return false;
    if(raiz->valor==buscado)
    return true;
    bool  buscar;
    for(int i=0; i<raiz->hijos.size();i++)
    {
        buscar = existe(raiz->hijos[i],buscado);
        if (buscar)
            return true;
    }
    return false;
}

NodoNario* object(NodoNario* raiz,int buscado)
{
    if(raiz==NULL)
    return NULL;
    if(raiz->valor==buscado)
    return raiz;
    NodoNario*  buscar;
    for(int i=0; i<raiz->hijos.size();i++)
    {
        buscar = object(raiz->hijos[i],buscado);
        if (buscar!=NULL)
            return buscar;
    }
    return NULL;
}

//Busca el valor "buscado" en el arbol "raiz" y lo reemplaza con "reemplazo"
void buscarYReemplazar(NodoNario* raiz, int buscado, int reemplazo)
{
    NodoNario* temporal=object(raiz,buscado);
    if(temporal!=NULL)
    {
        temporal->valor=reemplazo;
    }
}

//Devuelve un vector que contenga la siguiente secuencia binaria:
//00000001
//00000010
//00000100
//00001000
//00010000
//00100000
//01000000
//10000000
char encenderBit(char valor, int pos)
{
  int mascara = 1;
  mascara = mascara<<pos;
  return valor | mascara;
}

vector<char> obtenerSecuencia()
{
    vector<char>respuesta;

    int t=256;
    for(int i=0;i<8;i++)
    {
        int insertar= encenderBit(t,i);
        respuesta.push_back(insertar);
    }


    return respuesta;
}

int main ()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}

