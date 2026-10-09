#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "declaration.h"
#include <time.h>
// Fonction pour obtenir la date et l'heure actuel :
void get_current_timestamp(char *times) {
    time_t now = time(NULL);// récupère la date et l'heure actuelle
    struct tm *t = localtime(&now);// Convertit en heure locale
    // Formate la date et l'heure au format JJ/MM/AAAA-HH:MM:SS
	sprintf(times, "%02d/%02d/%d-%02d:%02d:%02d", 
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec);
}

// Fonction pour enregistrer l'historique des serres dans le fichier correspondante :
void fichier__serres(serres *S, int id_serre){
	FILE *f = fopen("historique_serres.txt", "a");// Ouvre le fichier en mode "a"
	if (f == NULL) { // Vérifie si l'ouverture du fichier a échoué
        printf("Erreur lors de l'ouverture du fichier d'historique\n");
        return;
    }
    char timestamp[30];// Tableau pour stocker la date et l'heure actuelle
    get_current_timestamp(timestamp);
    serres *i=S;
        while (i!= NULL){
            if (i->serre->ID== id_serre) {
            	// Si l'ID de la serre est correspond , on enregistre l'historique dans le fichier
                fprintf(f, "%s - serre-%d - temp[ID:%d]-%d - hum[ID:%d]-%d - pluie[ID:%d]-%d - irrigation-%d - chauffage-%d - etat-%s\n",
				timestamp, i->serre->ID,
				i->serre->temperature->ID, i->serre->temperature->val,
				i->serre->humidite->ID, i->serre->humidite->val,
				i->serre->pluit->ID, i->serre->pluit->val,
				i->serre->systeme_irrigation, i->serre->chauffage,i->serre->etat);
                break;
            }
            i= i->next;
        }
        fclose(f);// Ferme le fichier après écriture
}
// Fonction pour enregistrer l'historique des champs dans le fichier correspondante :
void fichier__champs(champs *CH, int id_champ){
	FILE *f = fopen("historique_champs.txt", "a");
	if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique\n");
        return;
    }
    char timestamp[30];
    get_current_timestamp(timestamp);
    champs *i=CH;
    while (i!= NULL) {
            if (i->champ_ouvert->ID == id_champ) {
                fprintf(f, "%s - champ-%d - temp[ID:%d]-%d - hum[ID:%d]-%d - ph[ID:%d]-%d - irrigation-%d\n",
                    timestamp, i->champ_ouvert->ID,
                    i->champ_ouvert->temperature->ID, i->champ_ouvert->temperature->val,
                    i->champ_ouvert->humidite->ID, i->champ_ouvert->humidite->val,
                    i->champ_ouvert->ph->ID, i->champ_ouvert->ph->val,
                    i->champ_ouvert->systeme_irrigation);
                break;
            }
            i= i->next;
        }
        fclose(f);
}
// Fonction pour enregistrer l'historique des panneaux solaires dans le fichier correspondante :
void fichier__panneaux(panneaux_sol *P, int id_panneau){
	FILE *f = fopen("historique_panneaux.txt", "a");
	if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique\n");
        return;
    }
    char timestamp[30];
    get_current_timestamp(timestamp);
    panneaux_sol *i=P;
    while (i!= NULL) {
            if (i->panneau_sol->ID == id_panneau) {
                fprintf(f, "%s - panneau-%d - lum[ID:%d]-%d - ajustement-%d - etat-%s\n",
                    timestamp, i->panneau_sol->ID,
                    i->panneau_sol->luminosite->ID, i->panneau_sol->luminosite->val,
                    i->panneau_sol->ajustement_panneaux, i->panneau_sol->etat_journnee);
                break;
            }
            i=i->next;
        }
        fclose(f);
}
// Fonction pour enregistrer l'historique des reserves d'eau dans le fichier correspondante :
void fichier__reserves(reserves_eau *R, int id_reserve){
	FILE *f = fopen("historique_reserves.txt", "a");
	if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'historique\n");
        return;
    }
    char timestamp[30];
    get_current_timestamp(timestamp);
    reserves_eau *i=R;
    while (i!= NULL) {
            if (i->reserve_eau->ID == id_reserve) {
                fprintf(f, "%s - reserve-%d - niveau[ID:%d]-%d - fuite[ID:%d]-%d - pression[ID:%d]-%d - pompe-%d - alerte-%d - reg_pression-%d - vanne-%d - detect_fuite-%d\n",
                    timestamp, i->reserve_eau->ID,
                    i->reserve_eau->niveau_eau->ID, i->reserve_eau->niveau_eau->val,
                    i->reserve_eau->fuit->ID, i->reserve_eau->fuit->val,
                    i->reserve_eau->pression->ID, i->reserve_eau->pression->val,
                    i->reserve_eau->pompe_remplissage,i->reserve_eau->vanne_decharge);
                break;
            }
            i= i->next;
        }
        fclose(f);
}
