#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
//------------------les panneaux solaires :
//les traitements possibles selon les valeurs de capteur de luminosité
void ajustement_panneau_sol(panneaux_sol *P,file *file_notif){
	if(P==NULL){
		printf("\npanneau solaire non valide !\n");
		return ;
	}
	panneaux_sol *i;
	notification *nv=NULL;
	for(i=P;i!=NULL;i=i->next){
		//cas de luminosité est entre 100 et 300
		if(i->panneau_sol->luminosite->val<=300 && i->panneau_sol->luminosite->val>100){
		strcpy(i->panneau_sol->etat_journnee,"nuage");// État "nuage"
		i->panneau_sol->ajustement_panneaux=0;// Désactivation de l'ajustement des panneaux
		nv=creat_notif("Ajustement du panneau solaire est desactive ",i->panneau_sol->ID);
        Enfiler(file_notif,nv);
	    }
	    // Cas où la luminosité est supérieure à 300
	    else if(i->panneau_sol->luminosite->val>300){
		strcpy(i->panneau_sol->etat_journnee,"jour");// État "jour"
		i->panneau_sol->ajustement_panneaux=1;// Activation de l'ajustement des panneaux
		nv=creat_notif("Ajustement du panneau solaire est active ",i->panneau_sol->ID);
        Enfiler(file_notif,nv);	
		}
		// Cas où la luminosité est inférieure ou égale à 100
		else if(i->panneau_sol->luminosite->val<=100){
		strcpy(i->panneau_sol->etat_journnee,"nuit");// État "nuit"
		i->panneau_sol->ajustement_panneaux=0;// Désactivation de l'ajustement des panneaux		
		nv=creat_notif("Ajustement du panneau solaire est desactive ",i->panneau_sol->ID);
        Enfiler(file_notif,nv);	
		}
	}
}
//---------------------les serres :
// les traitements possibles selon les valeurs des capteur temperature\humidite\pluit :
void ajustement_serres(serres *S,alertes **A,file *file_notif){
	if(S==NULL){
		printf("pas de serre!\n");
		return;
	}
	serres *i;
	notification *nv=NULL;
	for(i=S;i!=NULL;i=i->next){
		if(i->serre->temperature->val>=35){
		// Si la température est supérieure ou égale à 35°C, on active l'irrigation
		 i->serre->systeme_irrigation=1;
	     nv=creat_notif("Activation de systeme d'irrigation dans la serre ",i->serre->ID);
         Enfiler(file_notif,nv);
		 }
		 else{
		    i->serre->systeme_irrigation=0;
		    nv=creat_notif("Desactivation de systeme d'irrigation dans la serre",i->serre->ID);
            Enfiler(file_notif,nv);
		 }
		 // Si la température est inférieure ou égale à 10°C, on active le chauffage
		if(i->serre->temperature->val<=10){
		 i->serre->chauffage=1;
		 nv=creat_notif("Activation de chauffage dans la serre",i->serre->ID);
         Enfiler(file_notif,nv);
		 }
		else{
		    i->serre->chauffage=0;
			nv=creat_notif("Desactivation de systeme de chauffage dans la serre",i->serre->ID);
            Enfiler(file_notif,nv);
		}
		// Si la pluie est supérieure à 50 mm, on ferme la serre
		if(i->serre->pluit->val>50){
		strcpy(i->serre->etat,"ferme");
		nv=creat_notif("la serre est fermee",i->serre->ID);
        Enfiler(file_notif,nv);
		}
		else{
		 strcpy(i->serre->etat,"ouvert");
		 nv=creat_notif("la serre est ouvert",i->serre->ID);
         Enfiler(file_notif,nv);
		 }
		 // Si l'humidité est supérieure à 80%, on génère une alerte
		if(i->serre->humidite->val >80){
			alerte *a=creat_alerte(i->serre->ID,"humidite elevee",2);
			ajouter_alerte(A,a);
		}
	}
}
//---------------------les reserves d'eau:
// les traitements possibles selon les valeurs des capteur niveau_eau\fuit\pression :
void ajustement_reserves(reserves_eau *R,alertes **A,file *file_notif){
	if(R==NULL){
		printf("pas de reserve!\n");
		return;
	}
	reserves_eau *i;
	notification *nv=NULL;
	for(i=R;i!=NULL;i=i->next){
	// Si le niveau d'eau est inférieur ou égal à 10, on active la pompe de remplissage
    if (i->reserve_eau->niveau_eau->val <= 10) {
        printf("Niveau d'eau bas ! Activation de la pompe de remplissage.\n");
        i->reserve_eau->pompe_remplissage = 1;
        nv=creat_notif("Activation de la pompe de remplissage",i->reserve_eau->ID);
        Enfiler(file_notif,nv);
    } 
    else {
    	i->reserve_eau->pompe_remplissage = 0;
        nv=creat_notif("La pompe de remplissage est desactivee",i->reserve_eau->ID);
        Enfiler(file_notif,nv);
    }
	// Si le niveau d'eau est supérieur à 500, on active la vanne de décharge
	if(i->reserve_eau->niveau_eau->val > 500) {
        printf("Le réservoir est trop plein ! Activation de la vanne de décharge.\n");
        i->reserve_eau->vanne_decharge = 1;
        nv=creat_notif("Activation de la vanne de decharge",i->reserve_eau->ID);
        Enfiler(file_notif,nv);
    }
    else {
        i->reserve_eau->vanne_decharge = 0;
        nv=creat_notif("la vanne de decharge est desactivee",i->reserve_eau->ID);
        Enfiler(file_notif,nv);
    }
    // Si une fuite est détectée, on génère une alerte
    if (i->reserve_eau->fuit->val == 1) {
    	alerte *a=creat_alerte(i->reserve_eau->ID,"detection d'un fuit",10);
		ajouter_alerte(A,a);
    }
    // Si la pression est supérieure à 100, on génère une alerte
    if (i->reserve_eau->pression->val > 100) {
    	alerte *a=creat_alerte(i->reserve_eau->ID,"pression elevee",8);
		ajouter_alerte(A,a);
    }
 }
}
//------------------------ les champs 
// les traitements possibles selon les valeurs des capteur temperature\humidite\ph :
void ajustement_champs(champs *C,alertes **A,file *file_notif) {
    if (C == NULL) {
        printf("Pas de champ!\n");
        return;
    }
    champs *i;
    for (i=C;i!=NULL;i=i->next){
    	// Si la température est supérieure ou égale à 35°C, on active l'irrigation
        if (i->champ_ouvert->temperature->val >= 35) {
            i->champ_ouvert->systeme_irrigation = 1;// Active le système d'irrigation si la température est trop élevée
            notification *nv=creat_notif("Activation de systeme d'irrigation dans le champ",i->champ_ouvert->ID);
            Enfiler(file_notif,nv);
	    } 
	    // Sinon, on désactive le système d'irrigation
		else {
            i->champ_ouvert->systeme_irrigation = 0;  // Désactive le système d'irrigation si la température est trop basse
            notification *nv=creat_notif("Desactivation ",i->champ_ouvert->ID);
            Enfiler(file_notif,nv);
		} 
        // // Si l'humidité est inférieure à 30%, on génère une alerte d'humidité trop basse
        if (i->champ_ouvert->humidite->val < 30) {
        	alerte *a=creat_alerte(i->champ_ouvert->ID,"humidite trop basse",3);
		    ajouter_alerte(A,a);
        } else if (i->champ_ouvert->humidite->val > 70) {
        	alerte *a=creat_alerte(i->champ_ouvert->ID,"humidite trop eleve",2);
	    	ajouter_alerte(A,a);
        }
        // Si le pH est en dehors de la plage idéale (5-7.5), on génère une alerte
        if (i->champ_ouvert->ph->val < 5 || i->champ_ouvert->ph->val > 7.5) {
        	alerte *a=creat_alerte(i->champ_ouvert->ID,"ph en dehors de la plage optimale",5);
		    ajouter_alerte(A,a);
        }
    }
}
