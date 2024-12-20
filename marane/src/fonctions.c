#include <stdio.h>
#include <string.h>
#include "fonctions.h"
#include <gtk/gtk.h>

int AddAgent(char *filename, Agent a) {
    FILE *fichier = fopen(filename, "a");
    if (fichier == NULL) {
        perror("Error while opening file");
        return -1;
    }
    if(fprintf(fichier, "%s %s %s %s %s %s %s %d/%d/%d %s \n",
            a.NIC, a.FirstName, a.LastName, a.PhoneNumber, a.Adress, a.Sexe, a.Workspace , a.Dateofbirth.Day, a.Dateofbirth.Month, a.Dateofbirth.Year, a.Contract_Type)< 0){
    fclose(fichier);
    return 0;
}
    fclose(fichier);
    return 1;
}  



int DeleteAgent(char *filename, const char* NIC) {
    FILE *fichier = fopen("agents.txt", "r");
    FILE *temporaire = fopen("temp.txt", "w");
    Agent a;
    int found = 0;

    if (fichier == NULL || temporaire == NULL) {
        perror("Error while opening file.\n");
        return 0;
    }

    while (fscanf(fichier, "%s %s %s %s %s %s %s %d/%d/%d %s \n",
                  a.NIC, a.FirstName, a.LastName, a.PhoneNumber, a.Adress,
                  a.Sexe, a.Workspace, &a.Dateofbirth.Day, &a.Dateofbirth.Month,
                  &a.Dateofbirth.Year, a.Contract_Type) != EOF) {
        if (strcmp(a.NIC, NIC) != 0) {
            // Write non-deleted agents to the temp file
            fprintf(temporaire, "%s %s %s %s %s %s %s %d/%d/%d %s\n",
                    a.NIC, a.FirstName, a.LastName, a.PhoneNumber, a.Adress,
                    a.Sexe, a.Workspace, a.Dateofbirth.Day, a.Dateofbirth.Month,
                    a.Dateofbirth.Year, a.Contract_Type);
        } else {
            // Mark as found (delete this agent)
            found = 1;
        }
    }

    fclose(fichier);
    fclose(temporaire);

    if (found) {
        // Delete the old file and rename the temp file
        remove("agents.txt");
        rename("temp.txt", "agents.txt");
        printf("Agent successfully deleted.\n");
    } else {
        printf("Agent with NIC %s not found.\n", NIC);
    }

    return found;
}


int EditAgent(const char *filename , const char *NIC1 , Agent nouv) {
    FILE *fichier = fopen(filename, "r");
    FILE *temporaire = fopen("temp.txt", "w");
    Agent a;
    int found = 0;

    if (fichier == NULL && temporaire == NULL) {
        perror("Error while opening file. \n ");
        return found ;
    }

    while (fscanf(fichier, "%s %s %s %s %s %s %s %d/%d/%d %s \n",
                  a.NIC ,a.FirstName,a.LastName , a.PhoneNumber,a.Adress, a.Sexe, a.Workspace, &a.Dateofbirth.Day, &a.Dateofbirth.Month, &a.Dateofbirth.Year, a.Contract_Type ) != EOF){
        if (strcmp(a.NIC, NIC1) == 0) {
           fprintf(temporaire, "%s %s %s %s %s %s %s %d/%d/%d %s \n",
              nouv.NIC, nouv.FirstName, nouv.LastName, nouv.PhoneNumber, nouv.Adress, nouv.Sexe, nouv.Workspace, nouv.Dateofbirth.Day, nouv.Dateofbirth.Month, nouv.Dateofbirth.Year, nouv.Contract_Type);
found = 1;
        }
else{
       fprintf(temporaire, "%s %s %s %s %s %s %s %d/%d/%d %s \n", a.NIC, a.FirstName,a.LastName,a.PhoneNumber,a.Adress, a.Sexe, a.Workspace,  a.Dateofbirth.Day, a.Dateofbirth.Month, a.Dateofbirth.Year, a.Contract_Type );
}
    }

    fclose(fichier);
    fclose(temporaire);

    remove(filename);
    rename("temp.txt", filename);
return found;
}



int SearchAgent(const char *filename, const char *NIC, Agent *nouv) {
    FILE *file = fopen(filename, "r");
    Agent a;

    if (!file) {
        perror("Error opening the file");
        return 0; // Agent not found
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Parse each line
        sscanf(line, "%s %s %s %s %s %s %s %d/%d/%d %[^\n]", 
               a.NIC, a.FirstName, a.LastName, a.PhoneNumber, 
               a.Adress, a.Sexe, a.Workspace, 
               &a.Dateofbirth.Day, &a.Dateofbirth.Month, 
               &a.Dateofbirth.Year, a.Contract_Type);

        // Remove any trailing newline characters from Contract_Type
        a.Contract_Type[strcspn(a.Contract_Type, "\n")] = 0;

        if (strcmp(a.NIC, NIC) == 0) {
            // Copy the found agent to the nouv struct
            *nouv = a;

            // Debugging output: print contract types
            printf("Agent found:\nNIC: %s\n", a.NIC);
            char *contract_type = strtok(a.Contract_Type, "|");
            while (contract_type) {
                printf("Contract Type: %s\n", contract_type);
                contract_type = strtok(NULL, "|");
            }

            fclose(file);
            return 1; // Agent found
        }
    }

    fclose(file);
    return 0; // Agent not found
}



void afficherlistereserv(char *filenameR, GtkWidget *treeview, const char *date_recherche) { 
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *file;
    char date_naissance[15];
    char temps_res1[10];
    char temps_res2[10];
    Reservation res; 

    // Check if a model already exists for the tree view
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (store == NULL) {
        // If the store doesn't exist, create columns for the tree view
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Reservation ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Citizen ID", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Reservation Date", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Start Time", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("End Time", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Vehicle Type", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking Address", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    // Create a new data model with 7 columns
    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Open the file and read the reservation data
    file = fopen(filenameR, "r");
    if (file == NULL) {
        g_print("Error: Could not open file %s\n", filenameR);
        return;
    }

    // Reading the file and populating the treeview
    while (fscanf(file, "%d %d %d %2d/%2d/%4d %2d:%2d %2d:%2d %49s %99[^\n]",
                  &res.id_reservation, &res.id_citoyen, &res.parking.id_parking,
                  &res.date_reservation.Day, &res.date_reservation.Month, &res.date_reservation.Year,
                  &res.heure_debut.heure, &res.heure_debut.minute,
                  &res.heure_fin.heure, &res.heure_fin.minute,
                  res.vehicule.type, res.parking.adresse) != EOF) {
        // Format date and times
        sprintf(date_naissance, "%02d/%02d/%04d", res.date_reservation.Day, res.date_reservation.Month, res.date_reservation.Year);

        // Check if the reservation date matches the search date
        char date_formatee[15];
        sprintf(date_formatee, "%02d/%02d/%04d", res.date_reservation.Day, res.date_reservation.Month, res.date_reservation.Year);

        if (strcmp(date_formatee, date_recherche) == 0) {  // Dates match
            sprintf(temps_res1, "%02d:%02d", res.heure_debut.heure, res.heure_debut.minute);
            sprintf(temps_res2, "%02d:%02d", res.heure_fin.heure, res.heure_fin.minute);

            // Add data to list store
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, res.id_reservation,
                               1, res.id_citoyen,
                               2, date_naissance,
                               3, temps_res1,
                               4, temps_res2,
                               5, res.vehicule.type,
                               6, res.parking.adresse,
                               -1);}    
    }

    fclose(file);

    // Set the model for the tree view
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Unreference the store to free memory
    g_object_unref(store);
}



void DisplayAgents(char *filename, GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char date_naissance[15];
    Agent a;  

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (store == NULL) {
        // Création des colonnes si elles n'existent pas encore
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NIC", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("First Name", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Last Name", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date of Birth", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("workspace", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("contract Type", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Phone Number", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adress", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

       
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    // Création du modèle de données
    store = gtk_list_store_new(9, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING);

    // Lecture des données depuis le fichier
    FILE *fichier = fopen(filename, "r");
    if (fichier == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    while (fscanf(fichier, "%s %s %s %s %s %s %s %d/%d/%d  %s\n",
                 a.NIC, a.FirstName, a.LastName, a.PhoneNumber, a.Adress, a.Sexe, a.Workspace , &a.Dateofbirth.Day, &a.Dateofbirth.Month, &a.Dateofbirth.Year, a.Contract_Type) != EOF) {
        // Formatage de la date de naissance
        sprintf(date_naissance, "%02d/%02d/%04d", a.Dateofbirth.Day, a.Dateofbirth.Month, a.Dateofbirth.Year);

        // Ajouter les données au modèle
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, a.NIC,
                           1, a.FirstName,
                           2, a.LastName,
                           3, date_naissance,
                           4, a.Workspace,
                           5, a.Sexe,
                           6, a.Contract_Type,
                           7, a.PhoneNumber,
                           8, a.Adress,
                           -1);
    }
    fclose(fichier);

    // Associer le modèle de données au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Ne pas libérer store ici (ownership transféré à treeview)
}

