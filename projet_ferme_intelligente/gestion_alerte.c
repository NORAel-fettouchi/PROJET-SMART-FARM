#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
//------------------------------------------------------------------foctions de gestions des alertes :
  // fonction pour creer un alerte :
alerte *creat_alerte(int ID_element,char *description,int priorite){
	alerte *a=(alerte*)malloc(sizeof(alerte));// Allouer de la mémoire pour la nouvelle alerte
	a->description=(char*)malloc(50*sizeof(char));// Allouer de la mémoire pour la description de l'alerte
	strcpy(a->description,description);// Copier la description dans la structure
	a->ID_element=ID_element;// Initialiser de l'identifiant de l'élément qui a généré l'alerte
	a->priorite=priorite;// initialiser la priorite
	return a;// Retourner un pointeur vers l'alerte crée
}
  // fonction pour ajouter l'alerte à la liste des alertes en fct de sa priorité :
void ajouter_alerte(alertes **A,alerte *na){
	alertes *NA=(alertes*)malloc(sizeof(alertes));// Allouer de la mémoire pour un nouvel élément de la liste
	NA->alerte=na;// Assigner l'alerte à cet élément
	NA->next=NULL;
	if(*A==NULL){ // Si la liste des alertes est vide, on insère directement l'alerte
		*A=NA;
		return;
	}
	if(na->priorite > (*A)->alerte->priorite){ // Si la nouvelle alerte a une priorité plus élevée, on l'ajoute en tête de liste
		NA->next=*A;
		*A=NA;
		return;
	}
	// sinon recherche du bon emplacement pour insérer la nouvelle alerte
	alertes *i=*A,*precedent=NULL;
	while(i!=NULL){
		if(i->alerte->priorite < na->priorite) break;
		precedent=i;
		i=i->next;
	}
	precedent->next=NA;
	NA->next=i;
}
  //fonction pour afficher les alertes :
void afficher_alertes(alertes *A){
	alertes *i;
	int j=1;
	if(A==NULL){ // Si la liste est vide
		printf("il n'y a aucun alerte !\n");
		return;
	}
	 // sinon afficher chaque alerte dans la liste
	for(i=A;i!=NULL;i=i->next){
		printf("----Alerte %d-----\n",j++);
		printf("%s\n",i->alerte->description);
		printf("ID de l'element  :%d\n",i->alerte->ID_element);
		printf("avec une priorite de :%d\n",i->alerte->priorite);
		
	}
}
//-----------------------------------------------------------------------fonction de gestion des notifications :
  // fonction pour créer une notification :
// fonction pour créer une notification :
notification *creat_notif(char *notif, int id_zone){
    notification *nv = (notification*)malloc(sizeof(notification));// Allouer de la mémoire pour la notification
    nv->action=(char*)malloc(50*sizeof(char));// Allouer de la mémoire pour la chaîne d'action et la copier
    strcpy(nv->action,notif);
    nv->id_zone = id_zone;// Assigner l'ID de zone concernée par la notification
    return nv;// Retourner le pointeur vers la notification crée
}
  // Fonction pour ajouter une notification à la fin de la file
void Enfiler(file *F,notification *notif){
    notifications *N= (notifications*)malloc(sizeof(notifications));// Allouer de la mémoire pour un nouvel élément de la file
    N->notif=notif;// Assigner la notification à cet élément de la file
    N->next=NULL;
     // Si la file est vide, l'élément devient à la fois le premier et le dernier
    if (F->first==NULL){
        F->first=N;
        F->last=N;
    } 
    // Sinon, ajouter l'élément à la fin de la file
	else {
        F->last->next=N;
        F->last=N;
    }
    F->size++;// Augmenter la taille de la file
} 
  // Fonction pour afficher la file des notifications :
void afficher_File(file *F){
    notifications *i=F->first;
    if(F->first==NULL){ // Si la file est vide
    	printf("pas de notification !\n");
    	return;
	}
	// sinon afficher toutes les notifications dans la file
    printf("\n----Affichage des notifications----\n");
    while (i!=NULL) {
        printf("\nAction: %s, Zone ID: %d",i->notif->action,i->notif->id_zone);
        i=i->next;
    }
    printf("\nnombre de notifications dans la file : %d\n",F->size);
}
