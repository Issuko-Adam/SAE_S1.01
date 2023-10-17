#include <stdio.h>
#include <string.h>

enum  {INPUTMAX = 100, NOM_MAX = 30, MAXENTREPRISES = 50, MISSIONMAX = 50}; 
enum {OP = 1, AG, IN};

// structure d'une entreprise qui va contenir un nom de taille NOM_MAX (30), et un role (OP, AG, IN)
typedef struct s_entreprise
{
    char nom[NOM_MAX];
    int role;
} t_entreprise;

//structure d'une mission qui va contenir un identifiant saisi par l'utilisateur, un nom pour la mission, et sa remuneration
typedef struct s_mission
{
    int identifiant;
    char nom_mission[NOM_MAX];
    float remuneration;    
} t_mission;

//Enfin, les deux tableaux pour stocker ces derniers.
t_entreprise entreprises[MAXENTREPRISES];
t_mission missions[MISSIONMAX];

// C1 - Première fonction pour l'inscription d'une entreprise dans le tableau. Elle prend en fonction le pointeur vers le compteur d'entreprise 
void inscription(int *nbrentreprises){
    char entree[INPUTMAX];
    scanf("%s", entree);
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
        printf("Role incorrect\n");
        return;
    }
    scanf("%s", entree);
    for (int i = 0; i < *nbrentreprises; i++)
    {
        if (strcmp(entree, entreprises[i].nom) == 0 )
        {
           printf("Nom incorrect\n");
           return;
        }
    }
    strcpy(entreprises[*nbrentreprises].nom, entree);
    (*nbrentreprises)++;
    printf("Inscription realisee (%d)\n", *nbrentreprises);
}

// C2 - Cette fois ci la seconde fonction pour publier une mission, tout comme la première elle prend en pointeur le compteur de publication de missions.
void publication(int *nbrmissions){
    int identifiant;
    char nom_mission[NOM_MAX];
    float remuneration;

    scanf("%d", &identifiant);
    missions[*nbrmissions].identifiant = identifiant;
    scanf("%s", nom_mission);
    strcpy(missions[*nbrmissions].nom_mission, nom_mission);
    scanf("%f", remuneration);
    if (remuneration < 0)
    {
        printf("Remuneration incorrecte");
        return;
    }
    missions[*nbrmissions].remuneration = remuneration;
    (*nbrmissions)++;
    printf("Mission publiee (%d)\n", *nbrmissions);
    
}

int main()
{
    char entree[INPUTMAX]; // commande utilisateur
    int nbrentreprises = 0; // mon compteur (indice) pour les inscriptions
    int nbrmissions = 0;  // mon compteur pour les publications

    do 
    {
        printf("Entrez votre commande: ");
        scanf("%s", &entree);
        if (strcmp("inscription", entree) == 0)
        {
            inscription(&nbrentreprises); // C1 - inscription
        }
        else if (strcmp("mission", entree) == 0)
        {
            publication(&nbrmissions); // C2 - publication
        }
        
    } while (strcmp("exit", entree) != 0);  // C0 - Exit

    return 0;
}
