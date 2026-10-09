#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
reserve_eau *creat_reserve(int id_reserve,int id_niveau,int id_fuit,int id_pression){
	reserve_eau *r=(reserve_eau*)malloc(sizeof(reserve_eau));// Allocation mémoire pour la réserve d'eau
	r->ID=id_reserve;// Assigne l'ID de la réserve
	r->pompe_remplissage=0;// Initialisation de la pompe à 0 (désactivé)
	r->vanne_decharge=0;// Initialisation de la vanne de décharge à 0 (désactivé)
    // Création des capteurs pour la réserve d'eau
	r->niveau_eau=creat_capteur(id_niveau,"niveau");
	r->fuit=creat_capteur(id_fuit,"fuit");
	r->pression=creat_capteur(id_pression,"pression");
	return r;// Retourne la réserve d'eau crée
}
void afficher_reserves(reserves_eau *R){
	// Fonction pour afficher les informations de toutes les réserves d'eau
	reserves_eau *i;
	int j=1;
	if(R==NULL){
		printf("il n'y a pas de reserve!\n");
		return;
	}
	for(i=R;i!=NULL;i=i->next){
		printf("----reserve %d-----\n",j++);
		printf("ID :%d\n",i->reserve_eau->ID);
		
		printf("valeurs des capteurs:\n\tniveau d'eau:%d\n\tfuit:%d\n\tpression:%d\n",i->reserve_eau->niveau_eau->val,i->reserve_eau->fuit->val,i->reserve_eau->pression->val);
		printf("etat des système:\n\tpompe_remplissage:%d\n\tvanne_decharge:%d\n",i->reserve_eau->pompe_remplissage,i->reserve_eau->vanne_decharge);
		
	}
}
void ajouter_reserves(reserves_eau **R,reserve_eau *nr){
	reserves_eau *NR=(reserves_eau*)malloc(sizeof(reserves_eau));// Allocation mémoire pour un nouveau noeud
	NR->reserve_eau=nr;
	NR->next=NULL;
	if(*R==NULL){ // Si la liste est vide
		*R=NR;// Le nouveau noeud devient le premier élément de la liste
		return;
	}
	reserves_eau *i=*R;
	while(i->next!=NULL){
		i=i->next;
	}
	i->next=NR;// Ajoute le noeud à la fin de la liste
	return;
}
void supprimer_reserve(reserves_eau *r){
	// Libération de la mémoire allouée pour les capteurs et la réserve d'eau
	free(r->reserve_eau->niveau_eau->type);
	free(r->reserve_eau->fuit->type);
	free(r->reserve_eau->pression->type);
	free(r->reserve_eau->niveau_eau);
	free(r->reserve_eau->fuit);
	free(r->reserve_eau->pression);
	free(r->reserve_eau);
	free(r);
}
void supprimer_reserves(reserves_eau **R,int id_reserve){
	if((*R)->reserve_eau->ID==id_reserve){ // Si la réserve à supprimer est le premier élément de la liste
		reserves_eau *tmp=*R;
		(*R)=(*R)->next;
		supprimer_reserve(tmp);
		return;
	}
	reserves_eau *i=*R,*precedent=NULL;
	while(i!=NULL && i->reserve_eau->ID!=id_reserve){
		precedent=i;
		i=i->next;
		
	}
	if(i==NULL){
		printf("cet reserve n'existe pas!\n");
		return;
	}
	precedent->next=i->next;
	supprimer_reserve(i);// Libère la mémoire de la réserve supprimée
	
}

// fonction pour changer les val des capteurs :
void changer_cap_value_reserve(reserves_eau *R,int id_reserve,int val_niveau,int val_fuit,int val_pression){
	if(R==NULL){
		printf("il n'y a aucun reserve!\n");
		return;
	}
	reserves_eau *i=R;
	while(i!=NULL && i->reserve_eau->ID!=id_reserve){
		i=i->next;
	}
	if(i==NULL){
		printf("id non valide!!\n");
		return;
	}
	// Modifie les valeurs des capteurs si les nouvelles valeurs sont valides
	if(val_niveau !=-1) i->reserve_eau->niveau_eau->val=val_niveau;
	if(val_fuit !=-1) i->reserve_eau->fuit->val=val_fuit;
	if(val_pression !=-1) i->reserve_eau->pression->val=val_pression;
}

