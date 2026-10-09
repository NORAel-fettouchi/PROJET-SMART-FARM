#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
panneau_sol *creat_panneau(int id_panneau,int id_lum){
	panneau_sol *p=(panneau_sol*)malloc(sizeof(panneau_sol));// Allocation mémoire pour un panneau solaire
	p->ID=id_panneau;// Assigne l'ID du panneau solaire
	p->ajustement_panneaux=0;// Initialise l'ajustement des panneaux à 0 (désactivé)
	p->etat_journnee=(char*)malloc(20*sizeof(char));// Allocation pour l'état de la journée
	strcpy(p->etat_journnee,"aucun");// Initialise l'état de la journée à "aucun"
	p->luminosite=creat_capteur(id_lum,"luminosite");// Création du capteur de luminosité
	return p;// Retourne le panneau solaire créé
}
// Fonction pour afficher les informations de tous les panneaux solaires
void afficher_panneaux(panneaux_sol *P){
	panneaux_sol *i;
	int j=1;
	if(P==NULL){
		printf("il n'y aucun panneau!\n");
		return;
	}
	for(i=P;i!=NULL;i=i->next){
		printf("----panneau %d-----\n",j++);
		printf("ID :%d\n",i->panneau_sol->ID);
		printf("valeurs du capteur luminosite:%d\n",i->panneau_sol->luminosite->val);
		printf("etat de l'ajustement des panneaux:%d\n",i->panneau_sol->ajustement_panneaux);
		printf("etat de la journee:%s\n",i->panneau_sol->etat_journnee);
		
	}
}
void ajouter_panneaux(panneaux_sol **P,panneau_sol *np){
	panneaux_sol *NP=(panneaux_sol*)malloc(sizeof(panneaux_sol));// Allocation mémoire pour un nouveau panneau
	NP->panneau_sol=np;
	NP->next=NULL;
	if(*P==NULL){
		*P=NP;
		return;
	}
	panneaux_sol *i=*P;
	while(i->next!=NULL){
		i=i->next;
	}
	// Ajoute le panneau à la fin de la liste
	i->next=NP;
	return;
}
void supprimer_panneau(panneaux_sol *p){
	// Libération de la mémoire allouée pour le capteur et l'état de la journée
	free(p->panneau_sol->luminosite->type);
	free(p->panneau_sol->luminosite);
	free(p->panneau_sol->etat_journnee);
	free(p->panneau_sol);
	free(p);
}
void supprimer_panneaux(panneaux_sol **P,int id_panneau){
	if((*P)->panneau_sol->ID==id_panneau){ // Si le panneau à supprimer est le premier élément de la liste
		panneaux_sol *tmp=*P;
		(*P)=(*P)->next;
		supprimer_panneau(tmp);
		return;
	}
	panneaux_sol *i=*P,*precedent=NULL;
	while(i!=NULL && i->panneau_sol->ID!=id_panneau){
		precedent=i;
		i=i->next;
		
	}
	if(i==NULL){
		printf("ce panneau n'existe pas!\n");
		return;
	}
	precedent->next=i->next;
	supprimer_panneau(i);// Libère la mémoire du panneau supprimé
	
}
//fonction pour changer la valeur du capteur luminosite d'un panneau par id:
void changer_cap_value_panneau(panneaux_sol *P,int id_panneau,int nvl_val){
	if(P==0){
		printf("il n'y a aucun panneau!\n");
		return;
	}
	panneaux_sol *i=P;
	while(i!=0 && i->panneau_sol->ID!=id_panneau){
		i=i->next;
	}
	if(i==0){
		printf("id non valide!!\n");
		return;
	}
	// Modifie la valeur du capteur de luminosité
	if (nvl_val != -1) i->panneau_sol->luminosite->val=nvl_val;
}

