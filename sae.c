#include <stdio.h>
#include <string.h>

enum  {INPUTMAX = 100, NOM_MAX = 30, MAXENTREPRISES = 50, MISSIONMAX = 50}; 
typedef enum {OP = 1, AG, IN} t_traitance;

// structure d'une entreprise qui va contenir un nom de taille NOM_MAX (30), et un role (OP, AG, IN)
typedef struct s_entreprise
{
    char nom[NOM_MAX];
    t_traitance role;
} t_entreprise;

//structure d'une mission qui va contenir un idOperateur saisi par l'utilisateur, un nom pour la mission, et sa remuneration
typedef struct s_mission
{
    int idOperateur;
    int idAcceptant; 
    char nom_mission[NOM_MAX];
    float remuneration;    
} t_mission;

// C1 - Première fonction pour l'inscription d'une entreprise dans le tableau. Elle prend en fonction le pointeur vers le compteur d'entreprise et le tableau ou les entreprises sont stockés.
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

// C2 - Cette fois ci la seconde fonction pour publier une mission, tout comme la première elle prend en pointeur le compteur de publication de missions et le tableau ou les missions sont stockés.
void publication(int *nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES], int *nbrentreprises){
    int idOperateur;
    char nom_mission[NOM_MAX];
    float remuneration;

    scanf("%d", &idOperateur);
    if (idOperateur > *nbrentreprises || idOperateur <= 0 )
    {
        printf("%d %d %d", idOperateur, *nbrmissions, *nbrentreprises);
        printf("(1) Identifiant incorrect ou inexistant\n");
        return; 
    }
    if(entreprises[idOperateur - 1].role == OP)
    {
        missions[*nbrmissions].idOperateur = idOperateur;
    }
    else
    {
        printf("(2) Identifiant incorrect ou inexistant\n");
        return;
    }
    
    scanf("%s", nom_mission);
    strcpy(missions[*nbrmissions].nom_mission, nom_mission);
    scanf("%f", &remuneration);
    if (remuneration < 0)
    {
        printf("Remuneration incorrecte\n");
        return;
    }
    missions[*nbrmissions].remuneration = remuneration;
    (*nbrmissions)++;
    printf("Mission publiee (%d)\n", *nbrmissions);

}

void consultation(int nbrmissions, t_mission missions[MISSIONMAX], t_entreprise entreprises[MAXENTREPRISES]){
    if (nbrmissions == 0)
    {
        printf("Aucune mission disponible\n"); // A MODIFIER URGEMMENT QUAND ON AURA FAIT LACCEPTATION DE MISSIONS ozuefhqsfdôpihqsdfôihqfoîh 
        return;
    }
    for (size_t i = 0; i < nbrmissions; i++)
    {
        printf("%d %s %s %f (niveau de sous traitance qui arrive tkt)\n", i + 1, missions[i].nom_mission, entreprises[missions[i].idOperateur].nom, missions[i].remuneration);
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
        printf("Entrez votre commande: ");
        scanf("%s", &entree);
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
        
        
    } while (strcmp("exit", entree) != 0);  // C0 - Exit

    return 0;
}
