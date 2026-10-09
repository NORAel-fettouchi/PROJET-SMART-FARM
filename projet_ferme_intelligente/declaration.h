#ifndef STRUCTURES_BASE_H
#define STRUCTURES_BASE_H

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

//---------------------------------------------------- declaration des fonctions ---------------------------------------------------
// fonctions de gestion :
capteur *creat_capteur(int id_capteur,char *type);
void gestion_ferme(ferme *F,alertes **A,file *file_notif);
void gestion_serres(serres **S,alertes **A,file *file_notif);
void gestion_champs(champs **CH,alertes **A,file *file_notif);
void gestion_panneaux(panneaux_sol **P,file *file_notif);
void gestion_reserves_eau(reserves_eau **R,alertes **A,file *file_notif);

//fonctions des serres :
serre *creat_serre(int id_serre,int id_temp,int id_hum,int id_lum);
void supprimer_serre(serres *s);
void afficher_serres(serres *S);
void ajouter_serres(serres **S,serre*ns);
void supprimer_serres(serres **S,int id_serre);
// fonctions des champs :
void supprimer_champs(champs **CH,int id_champ);
void supprimer_champ(champs *ch);
void ajouter_champs(champs **CH,champ_ouvert *nch);
void afficher_champs(champs *CH);
champ_ouvert *creat_champ(int id_champ,int id_temp,int id_hum,int id_ph);
// fonctions des panneaux solaires :
panneau_sol *creat_panneau(int id_panneau,int id_lum);
void afficher_panneaux(panneaux_sol *P);
void ajouter_panneaux(panneaux_sol **P,panneau_sol *np);
void supprimer_panneau(panneaux_sol *p);
void supprimer_panneaux(panneaux_sol **P,int id_panneau);
// fonction des  reserves d'eau :
reserve_eau *creat_reserve(int id_reserve,int id_niveau,int id_fuit,int id_pression);
void afficher_reserves(reserves_eau *R);
void ajouter_reserves(reserves_eau **R,reserve_eau *nr);
void supprimer_reserve(reserves_eau *r);
void supprimer_reserves(reserves_eau **R,int id_reserve);
//fonction pour changer la val d'un capteur :
void changer_cap_value_panneau(panneaux_sol *P,int id_panneau,int nvl_val);
void changer_cap_value_reserve(reserves_eau *R,int id_reserve,int val_niveau,int val_fuit,int val_pression);
void changer_cap_value_champ(champs *C, int id_champ, int val_temperature, int val_humidite, int val_ph);
void changer_cap_value_serre(serres *S, int id_serre, int val_temperature, int val_humidite, int val_pluit);
// fonction d'ajustement :
void ajustement_panneau_sol(panneaux_sol *P,file *file_notif);
void ajustement_serres(serres *S,alertes **A,file *file_notif);
void ajustement_reserves(reserves_eau *R,alertes **A,file *file_notif);
void ajustement_champs(champs *C,alertes **A,file *file_notif);
// les fonctions d'historique :
void get_current_timestamp(char *times);
void fichier__serres(serres *S, int id_serre);
void fichier__reserves(reserves_eau *R, int id_reserve);
void fichier__panneaux(panneaux_sol *P, int id_panneau);
void fichier__champs(champs *CH, int id_champ);
// fonction pour la gestion des alertes :
alerte *creat_alerte(int ID_element,char *description,int priorite);
void ajouter_alerte(alertes **A,alerte *na);
void afficher_alertes(alertes *A);
//fonction pour la gestion des notifications :
notification *creat_notif(char *notif, int id_zone);
void Enfiler(file *F,notification *notif);
void afficher_File(file *F);



#endif

