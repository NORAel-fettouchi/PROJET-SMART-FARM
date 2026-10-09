#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
capteur *creat_capteur(int id_capteur,char *type){
	capteur *P=(capteur*)malloc(sizeof(capteur));//alloue de la mémoire pour un capteur
	P->ID=id_capteur;// Assigne l'ID du capteur
	P->type=(char*)malloc(20*sizeof(char));// Alloue de la mémoire pour le type
	strcpy(P->type,type);
	P->val=0;// Initialise la valeur du capteur à 0
	return P;// Retourne le capteur créé
}
serre *creat_serre(int id_serre,int id_temp,int id_hum,int id_pluit){
	serre *s=(serre*)malloc(sizeof(serre));// Alloue de la mémoire pour une serre
	s->ID=id_serre;// Assigne l'ID de la serre
	s->systeme_irrigation=0;// Initialise le système d'irrigation à 0 (désactive)
	s->chauffage=0;// Initialise le chauffage à 0 (désactivé)
	s->etat=(char*)malloc(20*sizeof(char));// Alloue de la mémoire pour l'état de la serre
	strcpy(s->etat,"ouvert");// Assigne l'état initial de la serre à "ouvert"
	s->temperature=creat_capteur(id_temp,"temperature");// Crée les capteurs de température, humidité et pluie associés à la serre
	s->humidite=creat_capteur(id_hum,"humidite");
	s->pluit=creat_capteur(id_pluit,"pluit");
	return s;// Retourne la serre crée
}
// Fonction pour afficher les informations de toutes les serres
void afficher_serres(serres *S){
	serres *i;
	int j=1;
	if(S==NULL){
		printf("il n'y a pas de serre!\n");
		return;
	}
	for(i=S;i!=NULL;i=i->next){
		printf("----serres %d-----\n",j++);
		printf("ID :%d\n",i->serre->ID);
		
		printf("valeurs des capteurs:\n\ttemperature:%d\n\thumidite:%d\n\tpluit:%d\n",i->serre->temperature->val,i->serre->humidite->val,i->serre->pluit->val);
		printf("etat des système:\n\tsys d'irrigation:%d\n\tsys chauffage:%d\n",i->serre->systeme_irrigation,i->serre->chauffage);
		printf("etat de la serre :%s\n",i->serre->etat);
		
	}
}
void ajouter_serres(serres **S,serre *ns){
	serres *NS=(serres*)malloc(sizeof(serres));// Alloue de la mémoire pour un nouveau noeud de serre
	NS->serre=ns;// Assigne la serre à ce noeud
	NS->next=NULL;
	if(*S==NULL){ // Si la liste des serres est vide
		*S=NS;// La nouvelle serre devient le premier élément de la liste
		return;
	}
	serres *i=*S;
	while(i->next!=NULL){
		i=i->next;
	}
	i->next=NS;// Ajoute le nouveau noeud à la fin de la liste
	return;
}
void supprimer_serre(serres *s){
	// Libère la mémoire allouée pour les capteurs et la serre
	free(s->serre->temperature->type);
	free(s->serre->humidite->type);
	free(s->serre->pluit->type);
	free(s->serre->temperature);
	free(s->serre->humidite);
	free(s->serre->pluit);
	free(s->serre);
	free(s);
}
void supprimer_serres(serres **S,int id_serre){
	if((*S)->serre->ID==id_serre){ // Si la serre à supprimer est le premier élément de la liste
		serres *tmp=*S;
		(*S)=(*S)->next;
		supprimer_serre(tmp);
		return;
	}
	serres *i=*S,*precedent=NULL;
	while(i!=NULL && i->serre->ID!=id_serre){
		precedent=i;
		i=i->next;
		
	}
	if(i==NULL){
		printf("cette serre n'existe pas!\n");
		return;
	}
	precedent->next=i->next;
	supprimer_serre(i);// Libère la mémoire de la serre supprimée
	
}
// fonction pour changer les val des cap :
void changer_cap_value_serre(serres *S, int id_serre, int val_temperature, int val_humidite, int val_pluit) {
    if (S == NULL) {
        printf("Il n'y a aucune serre!\n");
        return;
    }
    serres *i =S;
    // Recherche de la serre avec l'ID donné
    while (i!=NULL && i->serre->ID!=id_serre) {
        i = i->next;
    }
    if (i==NULL) {
        printf("ID de serre non valide!\n");
        return;
    }
    // Mise à jour des valeurs des capteurs (si les valeurs ne sont pas égales à -1)
    if (val_temperature !=-1) i->serre->temperature->val = val_temperature;
    if (val_humidite !=-1) i->serre->humidite->val = val_humidite;
    if (val_pluit !=-1)  i->serre->pluit->val = val_pluit;
}

