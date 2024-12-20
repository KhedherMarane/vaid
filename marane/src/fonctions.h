#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>


typedef struct {
int Day;
int Month;
int Year;
}Date;

typedef struct{
   char type[50];
   int matricule;
}Vehicule;
typedef struct{
 char type[50];
 char bloc[50];
 int places_disponibles;
}Place;  

typedef struct {
    char FirstName[50];          
    char LastName[50];        
    char NIC[20];          
    Date Dateofbirth;
    char Sexe[10];        
    char Workspace[20];      
    char Contract_Type[100];    
    char PhoneNumber[20]; 
    char Adress[50];                    
} Agent;

typedef struct{
 int heure;
 int minute;
}Heure;

typedef struct {
    char nom[100];
    int id_parking;
    char adresse[100];
}Parking;

typedef struct {
   char paiement[50];
   char demande_service[50];
}Service;

typedef struct {
    int id_reservation;
    int id_citoyen;
    Date date_reservation;
    Heure heure_debut;
    Heure heure_fin;
    Vehicule vehicule;
    Service service;
    Parking parking;
    Place place;
}Reservation;

int AddAgent(char *filename, Agent a);
int EditAgent(const char *filename ,const char *NIC1 , Agent nouv);
int SearchAgent(const char *filename, const char *NIC, Agent *nouv);
int DeleteAgent( char *filename, const char* NIC);
void DisplayAgents(char *filename, GtkWidget *treeview);
void afficherlistereserv(char *filenameR , GtkWidget *treeview , const char *date_recherche);
#endif
