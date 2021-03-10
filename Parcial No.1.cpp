#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define s 40


using namespace std;

const char *nombe_archivo = "parcial.dat";
const char *nom_temporal = "tempo10.dat";

struct Planilla
{
    int codigo;
    char nombre[s];
    char apellido[s];
    char puesto[s];
    float sueldo;
    float bonificacion;
    float total;
};

void menu();
void ingresar();
void modificar();
void mostrar();
void buscar();
void eliminar();

int main()
{
    menu();
}

void menu()
{
    int a, b, c;
    do
    {
  
        system("cls");
        cout << ("(1) Insertar  Datos")<< endl;
        cout << ("(2) Mostar Datos")<< endl;
        cout << ("(3) Eliminar Datos")<< endl;
        cout << ("(4) Buscar Datos")<< endl;
        cout << ("(5) Modificar Datos")<< endl;
        cout << ("(6) Salir")<< endl;
        cout << (" Ingrese opcion: ");
        cin >> a;
        switch (a)
        {
        case 1:
            system("cls");
            ingresar();
            break;
        case 2:
            system("cls");
            mostrar();
            break;
        case 3:
            system("cls");
            eliminar();
            break;
        case 4:
            system("cls");
            buscar();
            break;

        case 5:
            system("cls");
            modificar();
            break;
        }
    } while (a != 6);
}

void ingresar(){
    char continuar;
    FILE *archivo = fopen(nombe_archivo, "ab");
    Planilla plan;
        string nombre,apellido, puesto;
    do
    {
        system("cls");
        fflush(stdin);
        plan.codigo = 0;
        plan.codigo = plan.codigo + 1;
        cout << "Ingrese Nombre: ";
        getline(cin, nombre);
        strcpy(plan.nombre, nombre.c_str());

        cout << "Ingrese Apellido: ";
        getline(cin, apellido);
        strcpy(plan.apellido, apellido.c_str());

        cout << "Ingrese Puesto: ";
        getline(cin, puesto);
        strcpy(plan.puesto, puesto.c_str());

        cout << "Sueldo Base: ";
        cin >> plan.sueldo;
        cin.ignore();
        cout << "Bonificacion: ";
        cin >> plan.bonificacion;
        cin.ignore();
        
        plan.total = plan.sueldo + plan.bonificacion;

        fwrite(&plan, sizeof(Planilla), 1, archivo);

    
        cout << "Desea Agregar otro Dato s/n : ";
        cin >> continuar;
    } while ((continuar == 's') || (continuar == 'S'));
    fclose(archivo);
    system("cls");
}
void mostrar()
{
    system("cls");
    FILE *archivo = fopen(nombe_archivo, "rb");
    if (!archivo)
    {
        archivo = fopen(nombe_archivo, "w+b");
    }

    Planilla plan;
    int registro = 0;
    fread(&plan, sizeof(Planilla), 1, archivo);
    cout << "_________________________________________________________________________________" << endl;
    cout << "id |"
         << " NOMBRE |"
         << " APELLIDO |"
         << " PUESTO |"
         << " SUELDO |"
         << " BONIFICACION |"
         << " TOTAL |" << endl;

    do
    {

        cout << "_______________________________________________________________________________" << endl;
        cout << registro <<"\t"<<plan.nombre<< "|\t" << plan.apellido << "|\t" << plan.puesto << " \t|" << plan.sueldo << "\t|" << plan.bonificacion << "\t|" << plan.total << endl;

        fread(&plan, sizeof(Planilla), 1, archivo);
        registro += 1;

    } while (feof(archivo) == 0);

    cout << endl;
    

    fclose(archivo);
    getch();
}

void eliminar()
{
    Planilla plan;
    FILE *temporal = fopen(nom_temporal, "w+b");
    FILE *archivo = fopen(nombe_archivo, "r+b");
    int id;
    cout << "Ingrese el ID que desea eliminar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Planilla), SEEK_SET);
    plan.codigo = -1;
    fwrite(&plan, sizeof(Planilla), 1, archivo);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "r+b");

    fread(&plan, sizeof(Planilla), 1, archivo);
    temporal = fopen(nom_temporal, "a+b");
    do
    {
        if (plan.codigo == -1)
        {
            cout << "Archivo eliminado";
        }
        if (plan.codigo >= 0)
        {
            fwrite(&plan, sizeof(Planilla), 1, temporal);
        }
        fread(&plan, sizeof(Planilla), 1, archivo);
    } while (feof(archivo) == 0);
    fclose(temporal);
    fclose(archivo);

    archivo = fopen(nombe_archivo, "w");
    fclose(archivo);

    temporal = fopen(nom_temporal, "r+b");

    fread(&plan, sizeof(Planilla), 1, temporal);
    archivo = fopen(nombe_archivo, "a+b");
    do
    {
        fwrite(&plan, sizeof(Planilla), 1, archivo);
        fread(&plan, sizeof(Planilla), 1, temporal);
    } while (feof(temporal) == 0);
    fclose(archivo);
    fclose(temporal);

    temporal = fopen(nom_temporal, "w");
    fclose(temporal);

    mostrar();
}
void buscar()
{

   FILE* archivo = fopen(nombe_archivo, "rb");
	
	int pos=0;
	cout<<"Que Dato desea ver: ";
	cin>>pos;
	cout<<"------------------ "<<pos<<" ------------------"<<endl;
	fseek ( archivo,pos * sizeof(Planilla), SEEK_SET );
	
	Planilla plan;
    
    fread(&plan, sizeof(Planilla), 1, archivo);

    cout << "Codigo: " <<pos<< endl;
    cout << "Nombre: " << plan.nombre << endl;
    cout << "Apellido: " << plan.apellido << endl;
    cout << "Puesto: " << plan.puesto << endl;
    cout << "Sueldo Base: " << plan.sueldo << endl;
    cout << "Bonificacion: " << plan.bonificacion << endl;
    cout << "Total: " << plan.total << endl;
    cout << endl;

    fclose(archivo);
    system("PAUSE");
}
void modificar()
{
    FILE *archivo = fopen(nombe_archivo, "r+b");
    int id;
    char respuesta[s];
    string nombre, apellido, puesto;
    Planilla plan;

    cout << "Ingrese el ID que desea Modificar: ";
    cin >> id;
    fseek(archivo, id * sizeof(Planilla), SEEK_SET); // esto es lo que permite modificar en la pocision
    fread(&plan, sizeof(Planilla), 1, archivo);

    cout << ("------------   Datos Encontrados -------------")<< endl;
    cout << ("nombre:  [") << plan.nombre << ("]")<< endl;
    cout << ("apellido:  [") << plan.apellido << ("]")<< endl;
    cout << ("Puesto:  [") << plan.puesto << ("]")<< endl;
    cout << ("Sueldo Base:  [") << plan.sueldo << ("]")<< endl;
    cout << ("bonificacion [") << plan.bonificacion << ("]")<< endl;
    cout << ("---------------------------------------------")<< endl;
    cout << "<\n\n Nombre: " << plan.nombre << endl;
    cout << ("Desea modificar [s/n]: ")<< endl;
    cin >> respuesta, s;

    if (strcmp(respuesta, "s") == 0)
    {

        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << ("Nuevo Nombre : ");
        getline(cin, nombre);
        strcpy(plan.nombre, nombre.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nApellido: " << plan.apellido << endl;
    cout << ("Desea Modificar la Apellido [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << "Ingrese Nuevo Apellido: ";
        getline(cin, apellido);
        strcpy(plan.apellido, apellido.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nPuesto: " << plan.puesto << endl;
    cout << ("Desea modificar el puesto [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();

        cout << "Ingrese Nuevo Puesto: ";
        getline(cin, puesto);
        strcpy(plan.puesto, puesto.c_str());
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nSueldo: " << plan.sueldo << endl;
    cout << ("Desea Modificar el Sueldo [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0)
    {
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();

        cout << "Ingrese Nuevo Sueldo: ";
        cin >> plan.sueldo;
        plan.total = plan.sueldo + plan.bonificacion;
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << "\n\nBonificion: " << plan.bonificacion << endl;
    cout << ("Desea Modificar la Bonificacion [s/n]: ");
    cin >> respuesta, s;
    if (strcmp(respuesta, "s") == 0){
        fseek(archivo, id * sizeof(Planilla), SEEK_SET);
        cin.ignore();
        cout << "Ingrese la Neva Bonificacion: ";
        cin >> plan.bonificacion;
        plan.total = plan.sueldo + plan.bonificacion;
        fwrite(&plan, sizeof(Planilla), 1, archivo);
    }

    cout << ("Datos actualizados");
    fclose(archivo);
    getch();
    mostrar();
}
