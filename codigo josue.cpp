#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void leer();
void crear();
void actualizar();

const char *nom_arch="archivo.dat";
const char *tem="temporal.dat";

struct Traductor{
	char palabra[20];
	char palabra_trad[20];
	char descripcion[300];	
};

main(){
	int n=0;
	char con;
	do{
			system("cls");
			cout<<"Escriba el numero de la opcio que desea realizar:\n1.Ver listado de palabra\n2.Agregar palabras al listado\n3.Actualizar listado de palabras\n";
			cin>>n;
		switch(n){
			case 1:
				leer(); break;
			case 2:
				crear(); break;
			case 3:
				actualizar(); break;
			default:
				cout<<"El numero seleccionado no es una opcion, vuelva a intentarlo";			
		}
		
			cout<<"Desea Realizar otra accion? (s/n): ";
			cin>>con;
	}while(con=='s'||con=='S');
}

void leer(){
	system("cls");
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id_palabra=0;
	cout<<"id    |    palabra    |    palabra traducida    |    descripcion\n";
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		cout<<id_palabra<<"    |    "<<traductor.palabra<<"    |    "<<traductor.palabra_trad<<"    |    "<<traductor.descripcion<<endl;

		fread(&traductor,sizeof(Traductor),1,archivo);
		id_palabra++;
	}while(feof(archivo)==0);
	fclose(archivo);
}

void crear(){
	FILE* archivo=fopen(nom_arch,"ab");
	char con;
	Traductor traductor;
	string descripcion;
	do{
		fflush(stdin);
		cout<<"Ingrese una plabra: ";
		cin>>traductor.palabra;
		cout<<"Ingrese su traduccion: ";
		cin>>traductor.palabra_trad;
		cin.ignore();
		cout<<"Ingrese su descripcion: ";
		getline(cin,descripcion);
		strcpy(traductor.descripcion,descripcion.c_str());
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Desea agragar mas palabras? (s/n): ";
		cin>>con;
	}while(con=='s'||con=='S');
	fclose(archivo);
}

void actualizar(){
	FILE* archivo=fopen(nom_arch,"r+b");
	int id;
	char con;
	Traductor traductor;
	string descripcion;
	do{
		system("cls");
		leer();
		cout<<"\nIngrese el id de la palabra a modificar: ";
		cin>>id;
		fseek(archivo,id *sizeof(Traductor),SEEK_SET);
			cout<<"Ingrese una plabra: ";
			cin>>traductor.palabra;
			cout<<"Ingrese su traduccion: ";
			cin>>traductor.palabra_trad;
			cin.ignore();
			cout<<"Ingrese su descripcion: ";
			getline(cin,descripcion);
			strcpy(traductor.descripcion,descripcion.c_str());
			fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Desea modificar mas palabras? (s/n): ";
		cin>>con;
	}while(con=='s'||con=='S');
	
	fclose(archivo);
}

void eliminar(){

	int cod=0, id;

	FILE *archivo= fopen(nom_arch,"rb");
	FILE *temp=	fopen(temp,"wb");
		if(!archivo)
			archivo=fopen(nom_arch,"wb");
	Traductor traductor;
	leer();
	cout<<"digite el codigo a eliminar/ingrese 0 si no desea eliminar"<<endl;
	cin>>cod;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		if(p_estudiante->codigo!=cod){
			fwrite(&estudiante,sizeof(Estudiante),1,temp);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}while (feof(archivo)==0);
	
	fclose(archivo);
	fclose(temp);
	remove(nombre_archivo);
	rename(temporal,nombre_archivo);
	cout<<"\nRegistro eliminado!!!!!!"<<endl;
	getch();
}










