#include <stdio.h>
#include <stdlib.h>
#include "declaration.h"

 main() {
 	//déclaration et initialisation d'une ferme
 	ferme *F=(ferme*)malloc(sizeof(ferme));
 	F->serres=NULL;
 	F->champs=NULL;
 	F->reserves_eau=NULL;
 	F->panneaux_sol=NULL;
 	alertes *A=NULL;//déclaration et initialisation d'une liste chainée d'alerte
 	//déclaration et initialisation d'une file de notification
	file *file_notif=(file*)malloc(sizeof(file));
 	file_notif->first=NULL;
 	file_notif->last=NULL;
 	file_notif->size=0;
 	//intialisation d'une serre :
    serre *ns=creat_serre(123,1,2,3);
    ajouter_serres(&(F->serres),ns);
    fichier__serres(F->serres,123);
    F->serres->serre->temperature->val=9;
    F->serres->serre->humidite->val=20;
    F->serres->serre->pluit->val=10;
    ajustement_serres(F->serres,&A,file_notif);
    //initialisation d'un panneaux :
    panneau_sol *np=creat_panneau(123,1);
    ajouter_panneaux(&(F->panneaux_sol),np);
    fichier__panneaux(F->panneaux_sol,123);
    F->panneaux_sol->panneau_sol->luminosite->val=500;
    ajustement_panneau_sol(F->panneaux_sol,file_notif);
    fichier__panneaux(F->panneaux_sol,123);
    //appel de la fonction gestion ferme :
    printf("--------------------------------------SMART FARM--------------------------------------\n");
    int choix;
    printf("\nclique 1 pour la gestion de la ferme :");
    scanf("%d",&choix);
    while(choix==1){
    printf("\n-------gestion de la ferme--------\n");
 	gestion_ferme(F,&A,file_notif);
 	printf("clique 1 pour la gestion de la ferme :");
    scanf("%d",&choix);
    }
    //liberer l'espace mémoire :
    serres *i=F->serres;
    while(i!=NULL){
        serres *tmp1=i;
		i=i->next;
		supprimer_serre(tmp1);	
	}
	champs *j=F->champs;
    while(j!=NULL){
        champs *tmp2=j;
		j=j->next;
		supprimer_champ(tmp2);	
	}
	panneaux_sol *k=F->panneaux_sol;
    while(k!=NULL){
        panneaux_sol *tmp3=k;
		k=k->next;
		supprimer_panneau(tmp3);	
	}
	reserves_eau *l=F->reserves_eau;
    while(l!=NULL){
        reserves_eau *tmp4=l;
		l=l->next;
		supprimer_reserve(tmp4);	
    }
 	return 0;
}
