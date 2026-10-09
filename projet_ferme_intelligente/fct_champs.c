#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
champ_ouvert *creat_champ(int id_champ,int id_temp,int id_hum,int id_ph){
	champ_ouvert *ch=(champ_ouvert*)malloc(sizeof(champ_ouvert));// Alloue de la mémoire pour une serre
	ch->ID=id_champ;
	ch->systeme_irrigation=0;// Initialise le système d'irrigation à 0 (désactivé)
	// Crée les capteurs de température, humidité et pH associés au champ
	ch->temperature=creat_capteur(id_temp,"temperature");
	ch->humidite=creat_capteur(id_hum,"humidite");
	ch->ph=creat_capteur(id_ph,"ph");
	return ch;// Retourne le champ créé
}
// Fonction pour afficher les informations de tous les champs
void afficher_champs(champs *CH){
	champs *i;
	int j=1;
	if(CH==NULL){
		printf("il n'y a pas de champs!\n");
		return;
	}
	for(i=CH;i!=NULL;i=i->next){
		printf("----champ %d-----\n",j++);
		printf("ID :%d\n",i->champ_ouvert->ID);
		
		printf("valeurs des capteurs:\n\ttemperature:%d\n\thumidite:%d\n\tph:%d\n",i->champ_ouvert->temperature->val,i->champ_ouvert->humidite->val,i->champ_ouvert->ph->val);
		printf("etat des système:\n\tsys d'irrigation:%d\n",i->champ_ouvert->systeme_irrigation);
		
		
	}
}
void ajouter_champs(champs **CH,champ_ouvert *nch){
	champs *NCH=(champs*)malloc(sizeof(champs));// Alloue de la mémoire pour un nouveau noeud de champ
	NCH->champ_ouvert=nch;// Assigne le champ à ce noeud
	NCH->next=NULL;
	if(*CH==NULL){ // Si la liste des champs est vide
		*CH=NCH;// Le nouveau champ devient le premier élément de la liste
		return;
	}
	champs *i=*CH;
	while(i->next!=NULL){
		i=i->next;
	}
	// Ajoute le nouveau noeud à la fin de la liste
	i->next=NCH;
	return;
}
void supprimer_champ(champs *ch){
	// Libère la mémoire allouée pour les capteurs et le champ
	free(ch->champ_ouvert->temperature->type);
	free(ch->champ_ouvert->humidite->type);
	free(ch->champ_ouvert->ph->type);
	free(ch->champ_ouvert->temperature);
	free(ch->champ_ouvert->humidite);
	free(ch->champ_ouvert->ph);
	free(ch->champ_ouvert);
	free(ch);
}
void supprimer_champs(champs **CH,int id_champ){
	if((*CH)->champ_ouvert->ID==id_champ){ // Si le champ à supprimer est le premier élément de la liste
		champs *tmp=*CH;
		(*CH)=(*CH)->next;
		supprimer_champ(tmp);
		return;
	}
	champs *i=*CH,*precedent=NULL;
	while(i!=NULL && i->champ_ouvert->ID!=id_champ){
		precedent=i;
		i=i->next;
		
	}
	if(i==NULL){
		printf("ce champ n'existe pas!\n");
		return;
	}
	// Si le champ est trouvé, on le supprime de la liste
	precedent->next=i->next;
	supprimer_champ(i);
	
}

// fonction pour changer les val des capteur :
void changer_cap_value_champ(champs *C, int id_champ, int val_temperature, int val_humidite, int val_ph) {
    if (C == NULL) {
        printf("Il n'y a aucun champ!\n");
        return;
    }

    champs *i = C;
    while (i!=NULL && i->champ_ouvert->ID !=id_champ) {
        i = i->next;
    }

    if(i==NULL) {
        printf("ID de champ non valide!\n");
        return;
    }
    // Mise à jour des valeurs des capteurs (si les valeurs ne sont pas égales à -1)
    if (val_temperature!=-1)i->champ_ouvert->temperature->val=val_temperature;
    if (val_humidite!=-1)i->champ_ouvert->humidite->val=val_humidite;
    if (val_ph!=-1)i->champ_ouvert->ph->val=val_ph;
}
