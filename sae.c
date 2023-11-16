#include <stdio.h>
#include <string.h>


enum  {INPUTMAX = 100, NOM_MAX = 30, MAXENTREPRISES = 50, MISSIONMAX = 50}; 
typedef enum {SUCCES, LNA, SIGNAL, RECEPTEUR} t_code; 
typedef enum {OP = 1, AG, IN} t_traitance;

// structure d'une entreprise qui va contenir un nom de taille NOM_MAX (30), et un role (OP, AG, IN)
typedef struct s_entreprise
{
    char nom[NOM_MAX];
    t_traitance role;
} t_entreprise;

// structure pour nous permettre de faire la C7 (rapport d'une mission)
typedef struct s_rapport 
{
    t_code code;
    int idEntreprise;
} t_rapport;

//structure d'une mission qui va contenir un idOperateur saisi par l'utilisateur, un nom pour la mission, et sa remuneration
typedef struct s_mission
{
    int idOperateur; // l'id de l'operateur de la mission
    int idAcceptant; // l'id de l'entreprise qui a accepté la mission
    char nom_mission[NOM_MAX]; // son nom
    float remuneration; // la rémunération d'une mission
    int niveau; // les niveaux de sous-traitance
    struct s_mission *suivant; // pour voir si la mission actuelle a une mission suivante (sous-traitance)
    t_rapport rapport[MISSIONMAX]; // tableau de rapports qui va contenir le code de rapport et l'IdEntreprise en question
    int nbrEchec; // le nombre d'échecs qu'a subi une mission     
    int termine; // flag terminé à 0 ou 1 pour savoir si notre mission est terminée
    int identifiant; // identifiant de la mission
    
} t_mission;

// sous-fonction qui nous permet de print les infos d'une mission, nous permettant de ne pas reecrire les memes lignes dans details et consultation
void printinfos(t_entreprise entreprises[MAXENTREPRISES], t_mission missions[MISSIONMAX], int i){
    printf("%-3d %-15s %-15s %.2f (%d)\n", i + 1, missions[i].nom_mission, entreprises[missions[i].idOperateur - 1].nom, missions[i].remuneration, missions[i].niveau);
} 

// sous-fonction qui nous permet de vérifier si une mission est accepté et ne pas refaire le même check à chaque fonction
int estAccepte(t_mission missions[MISSIONMAX], int idMission){ 
    return (missions[idMission - 1].idAcceptant != -1); // retourne 0 ou 1 directement 
}
// sous-fonction qui nous permet si aucune mission est disponible dans C3 (consultation) 
int missionsIndispo(int nbrmissions, t_mission missions[MISSIONMAX]){
    for (int i = 0; i < nbrmissions; i++)
    {
        if (missions[i].idAcceptant == -1)
        {
            return 0;
        }
    }
    return 1;
}

/* C1 - Première fonction pour l'inscription d'une entreprise dans le tableau.
 Elle prend en fonction le pointeur vers le compteur d'entreprise et le tableau ou les entreprises sont stockés.*/
void inscription(int *nbrentreprises, t_entreprise entreprises[MAXENTREPRISES]){
    char entree[INPUTMAX];
    scanf("%s", entree);
    //on vérifie que ce que vient d'entrer l'utilisateur est équivalent à un des 3 rôles
    if (strcmp("OP", entree) == 0)
    {
        entreprises[*nbrentreprises].role = OP;
    }
    else if (strcmp("AG", entree) == 0)
    {
        entreprises[*nbrentreprises].role = AG;
    }
    else if (strcmp("IN", entree) == 0)
    {
        entreprises[*nbrentreprises].role = IN;
    }
    else
    {
        // si ce n'est pas le cas on affiche la phrase ci-dessous
        printf("Role incorrect\n");  
        return;
    }
    // on prend maintenant le nom qu'à saisi l'utilisateur
    scanf("%s", entree); 
    for (int i = 0; i < *nbrentreprises; i++)
    {
        // on vérifie que ce nom ne figure pas dans notre tableau entreprise en parcourant tous les indices, s'il figure on affiche la phrase ci-dessous
        if (strcmp(entree, entreprises[i].nom) == 0 ) 
        {
           printf("Nom incorrect\n");
           return;
        }
    }
    // si tout est bon alors on peut entrer le nom qu'à saisi l'utilisateur dans notre tableau entreprise, puis on incrémente notre indice de 1 pour la saisi suivante.
    strcpy(entreprises[*nbrentreprises].nom, entree);
    (*nbrentreprises)++;
    printf("Inscription realisee (%d)\n", *nbrentreprises);
}

/* fonction tres pratique qui va nous créer l'entièreté de la mission et mettre toutes les valeurs à ce qu'on souhaite
notamment utilisé pour la publication d'une mission, quand on fait une sous-traitance ou encore un rapport*/
void creationMission(t_mission missions[MISSIONMAX], int *nbrmissions, char nom_mission[NOM_MAX], float remuneration, int IdOperateur, t_rapport rapport[MISSIONMAX], int nbrEchec, int niveau){
    strcpy(missions[*nbrmissions].nom_mission, nom_mission);
    missions[*nbrmissions].remuneration = remuneration;
    missions[*nbrmissions].idAcceptant = -1; // On initialise à -1 pour dire que cette mission est encore non attribuee.
    missions[*nbrmissions].niveau = niveau; // On initialise le niveau de sous-traitance a 0 car ce n'est pas encore le cas. 
    missions[*nbrmissions].suivant = NULL;
    missions[*nbrmissions].idOperateur = IdOperateur;
    missions[*nbrmissions].nbrEchec = nbrEchec;
    missions[*nbrmissions].termine = 0;
    missions[*nbrmissions].identifiant = *nbrmissions + 1;
    // on entre tous les échecs précédents si on recrée une mission
    for (int i = 0; i < nbrEchec; i++)
    {
        missions[*nbrmissions].rapport[i].code = rapport[i].code;
        missions[*nbrmissions].rapport[i].idEntreprise = rapport[i].idEntreprise;
    }
    (*nbrmissions)++;
}

/* C2 - Cette fois ci la seconde fonction pour publier une mission, 
tout comme la première elle prend en pointeur le compteur de publication de missions et le tableau ou les missions sont stockés.*/
void publication(int *nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES], int *nbrentreprises){
    int idOperateur;
    char nom_mission[NOM_MAX];
    float remuneration;
    // On verifie les conditions d'erreurs, si l'ID entree est bien un operateur, on peut le rentrer dans notre tableau.
    scanf("%d", &idOperateur);
    scanf("%s", nom_mission);
    scanf("%f", &remuneration);
    if (idOperateur > *nbrentreprises || idOperateur <= 0 || entreprises[idOperateur - 1].role != OP)
    {
        printf("Identifiant incorrect\n");
        return; 
    }
    
    if (remuneration <= 0)
    {
        printf("Remuneration incorrecte\n");
        return;
    }
    creationMission(missions, nbrmissions, nom_mission, remuneration, idOperateur, NULL, 0, 0);
    printf("Mission publiee (%d)\n", *nbrmissions);
}

/*C3 - La fonction consultation qui va afficher toutes les missions disponibles actuellement */
void consultation(int nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES]){
    if (missionsIndispo(nbrmissions, missions))
    {
        printf("Aucune mission disponible\n"); 
        return;
    }
    for (int i = 0; i < nbrmissions; i++)
    {
        if (missions[i].idAcceptant == -1)
        {
            printinfos(entreprises, missions, i);
        }
    }
    
}

/*La fonction detail qui va nous afficher toutes les infos d'une mission ainsi que tout ses échecs précédents*/
void detail(int nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES]){
    int identifiant;
    scanf("%d", &identifiant);
    // on check d'abord nos conditions d'erreurs
    if (identifiant <= 0 || identifiant > nbrmissions || missions[identifiant - 1].idAcceptant != -1)
    {
        printf("Identifiant incorrect\n");
        return;
    }
    // et on affiche les infos de la mission ainsi que ses rapports
    printinfos(entreprises, missions, identifiant - 1);
    for (int i = missions[identifiant - 1].nbrEchec; i > 0; i--)
    {
        if (missions[identifiant - 1].rapport[i - 1].code == SUCCES)
        {
            printf("Succes\n");
        }
        else if (missions[identifiant - 1].rapport[i - 1].code == LNA)
        {
            printf("Local non accessible\n");
        }
        else if (missions[identifiant - 1].rapport[i - 1].code == SIGNAL)
        {
            printf("Pas de signal dans le boitier general\n");
        }
        else if (missions[identifiant - 1].rapport[i - 1].code == RECEPTEUR)
        {
            printf("Recepteur defectueux\n");
        }
    }
}
/*Fonction nous permettant de check qu'une entreprise qui a déjà échoué la mission x ne pourras pas la reprendre plus tard*/
int aEchoue(t_mission missions[MISSIONMAX], int idMission, int idEntreprise){
    for (int i = 0; i < missions[idMission - 1].nbrEchec; i++)
    {
        if (missions[idMission - 1].rapport[i].idEntreprise == idEntreprise)
        {
            return 1;
        }
    }
    return 0;
}
/*Fonction permettant d'accepter une mission par une entreprise != OP*/
void acceptation(int nbrentreprises, t_entreprise entreprises[MAXENTREPRISES], t_mission missions[MISSIONMAX]){
    int idEntreprise;
    int idMission;
    scanf("%d", &idEntreprise);
    scanf("%d", &idMission);
    if (estAccepte(missions, idMission))
    {
        printf("Mission incorrecte\n"); // car la mission a ete acceptee
        return;
    }
    if (idEntreprise <= 0 || idEntreprise > nbrentreprises || entreprises[idEntreprise - 1].role == OP || aEchoue(missions, idMission, idEntreprise))
    {
        printf("Entreprise incorrecte\n");
        return;
    }
    missions[idMission - 1].idAcceptant = idEntreprise;
    printf("Acceptation enregistree\n");
    

}
/*La fonction qui va nous permettre de faire sous-traiter une mission en vérifiant d'abord les cas d'erreur,
puis créer une nouvelle mission avec la rémunération choisi et de modifier la valeur de la mission.suivant à l'adresse 
de la prochaine mission. Ce qui va nous être utile pour vérifier plus tard si on est bien à la fin de la chaine de sous-traitance*/
void sousTraitance(t_entreprise entreprises[MAXENTREPRISES], int nbrentreprises, t_mission missions[MISSIONMAX], int *nbrmissions){
    int idEntreprise;
    int idMission;
    float remuneration;

    scanf("%d", &idEntreprise);
    scanf("%d", &idMission);
    scanf("%f", &remuneration);
    if (idEntreprise <= 0 || idEntreprise > nbrentreprises || entreprises[idEntreprise - 1].role != AG)
    {
        printf("Entreprise incorrecte\n");
        return;
    }
    if (estAccepte(missions, idMission) || idMission > *nbrmissions || idMission <= 0 || missions[idMission - 1].niveau >= 5)
    {
        printf("Mission incorrecte\n"); // car la mission a ete acceptee || la mission n'existe pas 
        return;
    }
    if (remuneration <= 0)
    {
        printf("Remuneration incorrecte\n");
        return;
    }
    missions[idMission - 1].idAcceptant = idEntreprise;
    /*mission.suivant est égal à la mission à l'indice qu'on vient de créer*/
    missions[idMission - 1].suivant = &missions[*nbrmissions]; 
    // on crée une nouvelle mission comme elle s'est faite sous-traitée
    creationMission(missions, nbrmissions, missions[idMission - 1].nom_mission, remuneration, idEntreprise, missions[idMission - 1].rapport, missions[idMission - 1].nbrEchec, missions[idMission - 1].niveau + 1);
    printf("Sous-traitance enregistree (%d)\n", *nbrmissions);
    
}
/*La fonction pour faire un rapport sur une mission en cours, ce qui va créer une nouvelle mission avec la majoration correspondant
au code de l'échec*/
void rapport(t_mission missions[MISSIONMAX], int *nbrmissions){
    int IdMission;
    int code;
    float majoration;

    scanf("%d", &IdMission);
    scanf("%d", &code);
    /* on vérifie nos bornes et que "suivant" dans notre struct mission existe pour verifier qu'on soit a la fin de la chaine de sous traitance*/
    if (IdMission <= 0 || IdMission > *nbrmissions || missions[IdMission - 1].suivant || missions[IdMission - 1].idAcceptant == -1)
    {
        printf("Mission incorrecte\n");
        return;
    }
    if (code < SUCCES || code > RECEPTEUR)
    {
        printf("Code de retour incorrect\n");
        return;
    }
    /*si nos conditions d'erreurs sont checkés et qu'on va faire un rapport sur notre mission actuelle
    on peut mettre mission.termine sur 1 pour dire que notre mission actuelle est terminée*/
    missions[IdMission - 1].termine = 1;
    if (code)
    {
        missions[IdMission - 1].rapport[missions[IdMission - 1].nbrEchec].code = code;
        missions[IdMission - 1].rapport[missions[IdMission - 1].nbrEchec].idEntreprise = missions[IdMission - 1].idAcceptant;
        missions[IdMission - 1].termine = 1;
        missions[IdMission - 1].nbrEchec++;
        majoration = missions[IdMission - 1].remuneration;
        if (code == 2)
        {
            majoration += majoration * (5.5 / 100);
        }
        else if (code == 3)
        {
            majoration += majoration * (4.0 / 100);
        }
        creationMission(missions, nbrmissions, missions[IdMission - 1].nom_mission, majoration, missions[IdMission - 1].idOperateur, missions[IdMission - 1].rapport, missions[IdMission - 1].nbrEchec, missions[IdMission - 1].niveau);
        printf("Rapport enregistre (%d)\n", *nbrmissions);
    }
    else
    {
        printf("Rapport enregistre\n");
    }
    
}
/*la fonction qui nous permet de voir si la mission actuelle est terminée en vérifiant s'il n'y a pas une autre
mission derrière celle-ci, donc si temp est NULL c'est qu'il n'y a plus de mission après */
int estTermine(t_mission mission){
    t_mission *temp = mission.suivant;
    if (!temp)
    {
        return mission.termine;
    }
    while (temp->suivant)
    {
        temp = temp->suivant;
    }
    return temp->termine;
}

/*La dernière commande de ce projet, on cherche à l'idEntreprise donné toutes ses missions,
on va ensuite effectuer plusieurs boucle for pour check à chaque fois le statut de toutes ses missions
pour enfin les rentrer dans les tableaux correspondants à leurs statuts.
à la fin on print dans l'ordre tout ce que contiennent les tableaux*/
void recapitulatif(int nbrentreprises, int nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES]){
    int idEntreprise;
    // nos 5 tableaux différents correspondants aux statuts des missions
    t_mission nonAttribuees[MISSIONMAX];
    t_mission attribuees[MISSIONMAX];
    t_mission terminees[MISSIONMAX];
    t_mission aRealiser[MISSIONMAX];
    t_mission realisees[MISSIONMAX];
    // les compteurs correspondants aux tableaux qu'on incrémente à chaque fois qu'on entre une mission dans le tableau
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int n = 0;

    scanf("%d", &idEntreprise);
    // On check nos conditions d'erreur
    if (idEntreprise <= 0 || idEntreprise > nbrentreprises)
    {
        printf("Entreprise incorrecte\n");
        return;
    }
    // Notre première boucle pour entrer les missions correspondantes dans les tableaux.
    for (int i = 0; i < nbrmissions; i++)
    {
        // Premièrement les missions qui sont publiées par l'entreprise
        if (missions[i].idOperateur == idEntreprise)
        {
            // Mais pas encore attribuées
            if (missions[i].idAcceptant == -1)
            {
                nonAttribuees[j] = missions[i];
                j++;
            }
            // Et qui sont terminées
            else if (estTermine(missions[i]))
            {
                terminees[k] = missions[i];
                k++;
            }
            // Mais qui sont attribuées
            else
            {
                attribuees[l] = missions[i];
                l++;
            }
        }
        // Et enfin les missions qui sont acceptés par l'entreprise
        else if (missions[i].idAcceptant == idEntreprise && !missions[i].suivant)
        {   
            // mais qui sont à réaliser
            if (missions[i].termine == 0)
            {
                aRealiser[m] = missions[i];
                m++;
            }
            // et qui sont réalisées
            else
            {
                realisees[n] = missions[i];
                n++;
            }
        }
    }
    /*Si le compteur J est non nul pour le tableau des missions non attribuées alors il affiche l'entièreté des missions
    avec le padding donné*/
    if (j)
    {
        printf("* non attribuees\n");
        for (int i = 0; i < j; i++)
        {
            printf("%-3d %-15s %-15s %.2f (%d)\n", nonAttribuees[i].identifiant, nonAttribuees[i].nom_mission, entreprises[nonAttribuees[i].idOperateur - 1].nom, nonAttribuees[i].remuneration, nonAttribuees[i].niveau);
        }
    }
    // Pareil cette fois-ci mais pour le compteur "l" qui correspond aux missions attribuées
    if (l)
    {
        printf("* attribuees\n");
        for (int i = 0; i < l; i++)
        {
            printf("%-3d %-15s %-15s %.2f (%d)\n", attribuees[i].identifiant, attribuees[i].nom_mission, entreprises[attribuees[i].idOperateur - 1].nom, attribuees[i].remuneration, attribuees[i].niveau);
        }
    }
    // Pareil avec le compteur "k" pour les missions terminées
    if (k)
    {
        printf("* terminees\n");
        for (int i = 0; i < k; i++)
        {
            printf("%-3d %-15s %-15s %.2f (%d)\n", terminees[i].identifiant, terminees[i].nom_mission, entreprises[terminees[i].idOperateur - 1].nom, terminees[i].remuneration, terminees[i].niveau);
        }
    }
    // Le compteur "m" pour les missions à réaliser
    if (m)
    {
        printf("* a realiser\n");
        for (int i = 0; i < m; i++)
        {
            printf("%-3d %-15s %-15s %.2f (%d)\n", aRealiser[i].identifiant, aRealiser[i].nom_mission, entreprises[aRealiser[i].idOperateur - 1].nom, aRealiser[i].remuneration, aRealiser[i].niveau);
        }
    }
    // Et enfin le dernier compteur n pour afficher l'entièreté du tableau de missions qui sont réalisées
    if (n)
    {
        printf("* realisees\n");
        for (int i = 0; i < n; i++)
        {
            printf("%-3d %-15s %-15s %.2f (%d)\n", realisees[i].identifiant, realisees[i].nom_mission, entreprises[realisees[i].idOperateur - 1].nom, realisees[i].remuneration, realisees[i].niveau);
        }
    }
    
    
    
}

int main()
{
    char entree[INPUTMAX]; // commande utilisateur
    int nbrentreprises = 0; // mon compteur (indice) pour les inscriptions
    int nbrmissions = 0;  // mon compteur pour les publications
    //Enfin, les deux tableaux pour stocker ces derniers.
    t_entreprise entreprises[MAXENTREPRISES];
    t_mission missions[MISSIONMAX];

    do 
    {
        scanf("%s", entree);
        if (strcmp("inscription", entree) == 0)
        {
            inscription(&nbrentreprises, entreprises); // C1 - inscription
        }
        else if (strcmp("mission", entree) == 0)
        {
            publication(&nbrmissions, missions, entreprises, &nbrentreprises); // C2 - publication
        }
        else if (strcmp("consultation", entree) == 0)
        {
            consultation(nbrmissions, missions, entreprises); // C3 - consultation
        }
        else if (strcmp("detail", entree) == 0)
        {
            detail(nbrmissions, missions, entreprises); // C4 - détails
        }
        else if (strcmp("acceptation", entree) == 0)
        {
            acceptation(nbrentreprises, entreprises, missions); // C5 - acceptation
        }
        else if (strcmp("sous-traitance", entree) == 0)
        {
            sousTraitance(entreprises, nbrentreprises, missions, &nbrmissions); // C6 - sous-traitance
        }
        else if (strcmp("rapport", entree) == 0)
        {
            rapport(missions, &nbrmissions); // C7 - rapport
        }
        else if (strcmp("recapitulatif", entree) == 0)
        {
            recapitulatif(nbrentreprises, nbrmissions, missions, entreprises); // C8 - recapitulatif !!!
        }
        
        
    } while (strcmp("exit", entree) != 0);  // C0 - Exit

    return 0;
}
