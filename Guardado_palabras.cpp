

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>


using namespace std;

void leer();
void crear();
void actualizar();
void eliminar();

const char *nom_arch="archivo.dat";
const char *tem="temporal.dat";

struct Traductor{
	char palabra[20];
	char palabra_trad[20];
	char descripcion[300];	
};

main(){
	bool ciclo = true;
	int n;

	do{
			system("cls");
			cout<<"Escriba el numero de la opcio que desea realizar"<<endl;
			cout<<"1.Ver listado de palabra"<<endl;
			cout<<"2.Agregar palabras al listado"<<endl;
			cout<<"3.Actualizar listado de palabras"<<endl;
			cout<<"4. Eliminar palabras"<<endl;
			cout<<"5. Salir"<<endl;
			cin>>n;
		switch(n){
			case 1:
				leer(); break;
			case 2:
				crear(); break;
			case 3:
				actualizar(); break;

			case 4:
				eliminar(); break;

			case 5:
				ciclo = false;
			default:
				cout<<"El numero seleccionado no es una opcion, vuelva a intentarlo";			
		}
		
	}while(ciclo!=0);
}

void leer(){
	system("cls");
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id=0;
	cout<<"id    |    palabra    |    palabra traducida    |    descripcion\n";
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		cout<<id<<"    |    "<<traductor.palabra<<"    |    "<<traductor.palabra_trad<<"    |    "<<traductor.descripcion<<endl;

		fread(&traductor,sizeof(Traductor),1,archivo);
		id++;
	}while(feof(archivo)==0);
	fclose(archivo);
	getch();
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

	char palabra[3];
	char *p_palabra;
	p_palabra=new char;

	int id;

	FILE *archivo= fopen(nom_arch,"rb");
	FILE *temp=	fopen(tem,"wb");
		if(!archivo)
			archivo=fopen(nom_arch,"wb");
	Traductor traductor;
	leer();
	cout<<"escriba la palabra a eliminar"<<endl;
	cin>>palabra;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		if(traductor.palabra==palabra){
			fwrite(&traductor,sizeof(Traductor),1,temp);
		}
		fread(&traductor,sizeof(Traductor),1,archivo);
	}while (feof(archivo)==0);
	
	fclose(archivo);
	fclose(temp);
	remove(nom_arch);
	rename(tem,nom_arch);
	cout<<"\nRegistro eliminado!!!!!!"<<endl;
	getch();
}










