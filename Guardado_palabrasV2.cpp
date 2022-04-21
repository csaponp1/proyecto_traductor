#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void leer();
void crear();
void actualizar();
void eliminar();
int consultar(string &palabra_aux);



const char *nom_arch="archivo.dat";
const char *tem="temporal.dat";

struct Traductor{
	int n;
	char palabra[20];
	char palabra_trad[20];
	char descripcion[300];	
};

main(){
	int n=0;
	bool ciclo=true;
	do{
			system("cls");
			cout<<"Escriba el numero de la opcion que desea realizar: " <<endl;
			cout<<"1.Ver listado de palabra "<<endl;
			cout<<"2.Agregar palabras al listado "<<endl;
			cout<<"3.Actualizar listado de palabras "<<endl;
			cout<<"4.Eliminar "<<endl;
			cout<<"5. Salir"<<endl;
			cin>>n;
		switch(n){
			case 1:
				leer(); 
				break;
			case 2:
				crear();
				break;
			case 3:
				actualizar();
				break;
			case 4:
				eliminar();
				break;
			case 5:
				ciclo=false;
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
	int id_palabra=1;
	cout<<"id    |    palabra    |    palabra traducida    |    descripcion\n";
	cout<<"__________________________________________________________________________"<<endl;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		cout<<id_palabra<<"     |    "<<traductor.palabra<<"   |    "<<traductor.palabra_trad<<"                |    "<<traductor.descripcion<<endl;

		fread(&traductor,sizeof(Traductor),1,archivo);
		id_palabra++;
	}while(feof(archivo)==0);
	fclose(archivo);
	getch();
}

void crear(){
	FILE* archivo=fopen(nom_arch,"ab");
	char con;
	Traductor traductor;
	int resultado=1;
	string pal_aux,descripcion;

	do{
		fflush(stdin);

			do
			{
				cout<<"ingrese palabra, una que no exista obvio, luego presiona una tecla muchas veces"<<endl;
				cin>>pal_aux;
				resultado=consultar(pal_aux);
				cout<<"\n1 si se repite, 0 si no  : "<<endl;
				cout<<resultado;
			} while (resultado==1);
		
		strcpy(traductor.palabra,pal_aux.c_str());
		
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
	//do{
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
	//	cout<<"Desea modificar mas palabras? (s/n): ";
	//	cin>>con;
	//}while(con=='s'||con=='S');
	
	fclose(archivo);
}

void eliminar(){
 	
	FILE *archivo, *archivo_tem; 	
	Traductor traductor; 
	archivo_tem=fopen(tem,"w+b");
	archivo=fopen(nom_arch,"rb"); 

	leer();

	int id=1,i=1;
	cout<<"ingrese el id a eliminar:"; 
	cin>>id; 	                      				                
	                                                                                
	while(fread(&traductor,sizeof(Traductor),1,archivo)){ 	
	if (i != id){
	fwrite(&traductor,sizeof(Traductor),1,archivo_tem);
	} 
	i++;
	}
	fclose(archivo_tem); 
	fclose(archivo);                 
	archivo_tem=fopen(tem,"rb"); 
	archivo=fopen(nom_arch,"wb");
	while(fread(&traductor,sizeof(Traductor),1, archivo_tem)){ 
	fwrite(&traductor,sizeof(Traductor),1, archivo); 
	}
	                
	fclose(archivo_tem);
	fclose(archivo); 
	leer();	
}	

int consultar(string &palabra_aux){

	FILE *archivo = fopen(nom_arch,"rb+");
	Traductor traductor;
	int valor;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do
	{
			valor=strcmp(traductor.palabra,palabra_aux.c_str());
			if(valor <0)
				valor=(valor*-1);

			
			if(valor>0){
				
				cin.ignore();
				
			}
			else{
				cout<<"valor "<<valor<<endl;
				return 1;

			}
			fread(&traductor,sizeof(Traductor),1,archivo);
	} while (feof(archivo)==0);
	fclose(archivo);

}