#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
//---------------------------------------------------------- déclaration des structures -----------------------------------------------------
// structure capteur :
typedef struct capteur {
    int ID;            // Identifiant unique du capteur
    char *type;        // Type du capteur (ex: température, humidité)
    int val;           // Valeur mesurée par le capteur
} capteur;
// Structure serre : 
typedef struct serre {
    int ID;                    // Identifiant unique de la serre
    capteur *temperature;      // Capteur de température
    capteur *humidite;         // Capteur d'humidité
    capteur *pluit;            // Capteur de pluie
    int chauffage;             // État du chauffage : 0 pour actif, 1 pour inactif
    int systeme_irrigation;    // État du système d'irrigation
    char *etat;                // État de la serre : "ouvert" ou "fermé"
} serre;
// Liste chaînée de serres :
typedef struct serres {
    serre *serre;              // Pointeur vers une structure de serre
    struct serres *next;       // Pointeur vers la serre suivante
} serres;
// Structure champ_ouvert :
typedef struct champ_ouvert {
    int ID;                    // Identifiant unique du champ ouvert
    capteur *temperature;      // Capteur de température
    capteur *humidite;         // Capteur d'humidité
    capteur *ph;               // Capteur de pH 
    int systeme_irrigation;    // État du système d'irrigation
} champ_ouvert;
// Liste chaînée de champs ouverts :
typedef struct champs {
    champ_ouvert *champ_ouvert;
    struct champs *next;        
} champs;
// Structure reserve_eau :
typedef struct reserve_eau {
    int ID;                    // Identifiant unique de la réserve d'eau
    capteur *niveau_eau;        // Capteur de niveau d'eau
    capteur *fuit;              // Capteur de fuite : 0 pour pas de fuite, 1 pour fuite
    capteur *pression;         // Capteur de pression
    int pompe_remplissage;     // État de la pompe de remplissage
    int vanne_decharge;        // État de la vanne de décharge
} reserve_eau;
// Liste chaînée de réserves d'eau :
typedef struct reserves_eau {
    reserve_eau *reserve_eau;  
    struct reserves_eau *next; 
} reserves_eau;
// Structure panneau_sol : 
typedef struct panneau_sol {
    int ID;                    // Identifiant unique du panneau solaire
    capteur *luminosite;       // Capteur de luminosité
    char *etat_journnee;       // État de la journée ( jour,nuit )
    int ajustement_panneaux;   // Réglage d'angle des panneaux 
} panneau_sol;
// Liste chaînée de panneaux solaires : 
typedef struct panneaux_sol {
    panneau_sol *panneau_sol;  
    struct panneaux_sol *next; 
} panneaux_sol;
// Structure ferme :
typedef struct ferme {
    serres *serres;            // Liste de serres dans la ferme
    champs *champs;            // Liste de champs ouverts dans la ferme
    reserves_eau *reserves_eau; // Liste de réserves d'eau dans la ferme
    panneaux_sol *panneaux_sol; // Liste de panneaux solaires dans la ferme
} ferme;
// Structure alerte : 
typedef struct alerte {
    int ID_element;   // Identifiant de l'élément qui a généré l'alerte
    char *description; // Description de l'alerte
    int priorite;      // Niveau de priorité de l'alerte 
} alerte;
// Liste chaînée d'alertes : 
typedef struct alertes {
    alerte *alerte;    
    struct alertes *next; 
} alertes;
// Structure notification : 
typedef struct notification {
    char *action;  // Action qui a été effectuer 
    int id_zone;   // Identifiant de la zone concernée par la notification
} notification;
// Liste chaînée de notifications : 
typedef struct notifications {
    notification *notif;    
    struct notifications *next; 
} notifications;
// Structure de file : 
typedef struct file {
    notifications *first;   // Pointeur vers la première notification dans la file
    notifications *last;    // Pointeur vers la dernière notification dans la file
    int size;               // Taille de la file (nombre de notifications)
} file;

//------------------------------------------ fonctions pour la gerstion des alertes et notifications-------------------------------------------------
//foctions de gestions des alertes :
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
//fonction de gestion des notifications :
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

//--------------------------------------------------------------------------------fonction pour la gestion des fichier d'historique :
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

//--------------------------------------------------- fonction pour la gestion des serres :
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
//-----------------------------------------------------------------------------fonctions pour la gestion des champs :
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

//-------------------------------------------------------------------------------------fonction pour la gestion des panneaux solaires :
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

//---------------------------------------------------------------------------fonction pour la gestion des reserves d'eau :
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

//---------------------------------------------------------------------------------fonctions d'ajustement :
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

//-------------------------------------------------------------fonctions de gestion :
//------------------------------- fonction pour la gestion des serres :
void gestion_serres(serres **S,alertes **A,file *file_notif){
	int choix;
	int id_serre,id_temp,id_hum,id_pluit;
	notification *nv=NULL;
	// Affichage des options disponibles pour la gestion des serres
    printf("\n--------gestion des serres--------\n");
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter une serre\n3: pour supprimer une serre\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des serres
    		afficher_serres(*S);
    		break;
    	case 2:
    	    // Ajouter une nouvelle serre
    		printf("entrez id de la nouvelle serre :");
    		scanf("%d",&id_serre);
    		printf("entrez id du capteur temperature|humidite|pluit:");
    		scanf("%d|%d|%d",&id_temp,&id_hum,&id_pluit);
    		serre *ns=creat_serre(id_serre,id_temp,id_hum,id_pluit);
    		ajouter_serres(S,ns);
    		nv=creat_notif("Ajout d'une serre ",id_serre);// Créer une notification pour l'ajout de serre
            Enfiler(file_notif,nv);
    		fichier__serres(*S,id_serre);// Mettre à jour le fichier des serres
    		break;
    	case 3:
    		if(*S==NULL){
		      printf("il n'y a pas de serres !\n");
		      return;
	        }
    		printf("entrez l'id de la serre a supprimer :");
    		scanf("%d",&id_serre);
    		supprimer_serres(S,id_serre);
    		nv=creat_notif("suppression d'une serre ",id_serre);// Créer une notification pour la suppression de serre
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'une serre existante
    		printf("entrez id du serre :");
    		scanf("%d",&id_serre);
    		int val_temp,val_hum,val_pluit;
    		printf("entrez la nouvelle val du capteur temperature|humidite|pluit (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_temp,&val_hum,&val_pluit);
    		changer_cap_value_serre(*S,id_serre,val_temp,val_hum,val_pluit);
    		nv=creat_notif("Changement des valeurs des capterus d'une serre ",id_serre);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les serres et mettre à jour le fichier
    		ajustement_serres(*S,A,file_notif);
    		fichier__serres(*S,id_serre);
    		break;
    	
	}
}
//---------------------------------------------------- fonction pour la gestion des champs :
void gestion_champs(champs **CH,alertes **A,file *file_notif){
	int choix;
	int id_champ,id_temp,id_hum,id_ph;
	notification *nv=NULL;
	printf("\n--------gestion des champs--------\n");
	// Affichage des options disponibles pour la gestion des champs
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un champ\n3: pour supprimer un champ\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des champs ouverts
    		afficher_champs(*CH);
    		break;
    	case 2:
    		// Ajouter un nouveau champ
    		printf("entrez id du nouveau champ :");
    		scanf("%d",&id_champ);
    		printf("entrez id du capteur temperature|humidite|ph:");
    		scanf("%d|%d|%d",&id_temp,&id_hum,&id_ph);
    		champ_ouvert *nch=creat_champ(id_champ,id_temp,id_hum,id_ph);
    		ajouter_champs(CH,nch);
    		nv=creat_notif("Ajout d'un champ ",id_champ);// Créer une notification pour l'ajout de champ
            Enfiler(file_notif,nv);
    		fichier__champs(*CH,id_champ);// Mettre à jour le fichier des champs
    		break;
    	case 3:
    		if(*CH==NULL){
		      printf("il n'y a pas de champs !\n");
		      return;
	        }
    		printf("entrez l'id du champ a supprimer :");
    		scanf("%d",&id_champ);
    		supprimer_champs(CH,id_champ);
    		nv=creat_notif("suppression d'un champ ",id_champ);// Créer une notification pour la suppression de champ
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'un champ existant
    		printf("entrez id du champ :");
    		scanf("%d",&id_champ);
    		int val_temp,val_hum,val_ph;
    		printf("entrez la nouvelle val du capteur temperature|humidite|ph (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_temp,&val_hum,&val_ph);
    		changer_cap_value_champ(*CH,id_champ,val_temp,val_hum,val_ph);
    		nv=creat_notif("Changement des valeurs des capterus d'un champ ",id_champ);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les champs et mettre à jour le fichier
    		ajustement_champs(*CH,A,file_notif);
    		fichier__champs(*CH,id_champ);
    		break;
    	
	}
}

// ---------------------------------------------fonction pour la gestion des panneaux solaires :
void gestion_panneaux(panneaux_sol **P,file *file_notif){
	int choix;
	int id_panneau,id_lum;
	notification *nv=NULL;
	printf("\n-------gestion des panneaux-------\n");
	// Affichage des options disponibles pour la gestion des panneaux solaires
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un panneau\n3: pour supprimer un panneaux\n4: pour changer la val d'un capteur\n");
do{
	printf("entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des panneaux solaires
    		afficher_panneaux(*P);
    		break;
    	case 2:
    		// Ajouter un nouveau panneau solaire
    		printf("entrez id du nouveau panneau :");
    		scanf("%d",&id_panneau);
    		printf("entrez id du capteur luminosite:");
    		scanf("%d",&id_lum);
    		panneau_sol *np=creat_panneau(id_panneau,id_lum);
    		ajouter_panneaux(P,np);
    		nv=creat_notif("Ajout d'un panneau ",id_panneau);// Créer une notification pour l'ajout de panneau
            Enfiler(file_notif,nv);
    		fichier__panneaux(*P,id_panneau);// Mettre à jour le fichier des panneaux
    		break;
    	case 3:
    		if(*P==NULL){
		      printf("il n'y a aucun panneau !\n");
		      return;
	        }
    		printf("entrez l'id du panneau a supprimer :");
    		scanf("%d",&id_panneau);
    		supprimer_panneaux(P,id_panneau);
    		nv=creat_notif("suppression d'un panneau ",id_panneau);// Créer une notification pour la suppression de panneau
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    		// Modifier les valeurs des capteurs d'un panneau solaire existant
    		printf("entrez id du panneau :");
    		scanf("%d",&id_panneau);
    		int nvl_val;
    		printf("entrez la nouvelle val de son cap luminosite :");
    		scanf("%d",&nvl_val);
    		changer_cap_value_panneau(*P,id_panneau,nvl_val);
    		nv=creat_notif("Changement des valeurs des capterus d'un panneau ",id_panneau);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les panneaux solaires et mettre à jour le fichier
    		ajustement_panneau_sol(*P,file_notif);
    		fichier__panneaux(*P,id_panneau);
    		break;
    		
    	
	}
}
//------------------------------------------------- fonction pour la gestion des reserves d'eaux :
void gestion_reserves_eau(reserves_eau **R,alertes **A,file *file_notif){
	int choix;
	int id_reserve,id_niveau,id_fuit,id_pression;
	notification *nv=NULL;
	printf("\n-------gestion des reserves-------\n");
	// Affichage des options disponibles pour la gestion des réserves d'eau
	printf("clique sur :\n1: pour l'affichage\n2: pour ajouter un reserve\n3: pour supprimer un reserve\n4: pour changer la val d'un capteur\n");
do{
	printf("\nentrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);
    switch(choix){
    	case 1:
    		// Affichage des réserves d'eau
    		afficher_reserves(*R);
    		break;
    	case 2:
    		// Ajouter une nouvelle réserve d'eau
    		printf("entrez id du nouveau reserve :");
    		scanf("%d",&id_reserve);
    		printf("entrez id du capteur niveau|fuit|pression:");
    		scanf("%d|%d|%d",&id_niveau,&id_fuit,&id_pression);
    		reserve_eau *nr=creat_reserve(id_reserve,id_niveau,id_fuit,id_pression);
    		ajouter_reserves(R,nr);
    		nv=creat_notif("Ajout d'un reserve ",id_reserve);// Créer une notification pour l'ajout de réserve
            Enfiler(file_notif,nv);
    		fichier__reserves(*R,id_reserve);// Mettre à jour le fichier des réserves
    		break;
    	case 3:
    		if(*R==NULL){
		      printf("il n'y a aucun reserve !\n");
		      return;
	        }
    		printf("entrez l'id du reserve a supprimer :");
    		scanf("%d",&id_reserve);
    		supprimer_reserves(R,id_reserve);
    		nv=creat_notif("suppression d'un reserve ",id_reserve);// Créer une notification pour la suppression de réserve
            Enfiler(file_notif,nv);
    		break;
    	case 4:
    	    // Modifier les valeurs des capteurs d'une réserve existante
    		printf("entrez id du reserve :");
    		scanf("%d",&id_reserve);
    		int val_niveau,val_fuit,val_pression;
    		printf("entrez la nouvelle val du capteur niveau_eau|fuit|pression (-1 si tu veut garder sa valeur) :");
    		scanf("%d|%d|%d",&val_niveau,&val_fuit,&val_pression);
    		changer_cap_value_reserve(*R,id_reserve,val_niveau,val_fuit,val_pression);
    		nv=creat_notif("Changement des valeurs des capterus d'un reserve ",id_reserve);// Créer une notification pour le changement de valeurs
            Enfiler(file_notif,nv);
            // Ajuster les réserves d'eau et mettre à jour le fichier
    		ajustement_reserves(*R,A,file_notif);
    		fichier__reserves(*R,id_reserve);
    		break;
    	
	}
}

//-----------------------------fonction pour la gestion de la ferme--------------------------------------------
void gestion_ferme(ferme *F,alertes **A,file *file_notif){
	int choix;
	printf("clique sur :\n1: pour la gestion des serres\n2: pour la gestion de champ ouvert\n3: pour la gestion du reserve d'eau\n4: pour la gestion des panneaux solaires\n5: pour afficher les alertes\n6: pour afficher les notifications\n");
do{
	printf("\n==> Entrez votre choix : ");
	scanf("%d",&choix);
}while(choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5 && choix!=6 );
    switch(choix){
    	case 1:
    		gestion_serres(&(F->serres),A,file_notif);
    		break;
    	case 2:
    		gestion_champs(&(F->champs),A,file_notif);
    		break;
    	case 3:
    		gestion_reserves_eau(&(F->reserves_eau),A,file_notif);
    		break;
    	case 4:
    		gestion_panneaux(&(F->panneaux_sol),file_notif);
    		break;
    	case 5:
    		afficher_alertes(*A);
    		break;
    	case 6:
    		afficher_File(file_notif);
    		break;
    	
	}
}

//--------------------------------------------------main()-----------------------------------
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
