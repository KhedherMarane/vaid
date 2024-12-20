#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>
#include <glib.h>
#include "fonctions.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h" 
 


int Male=0;
int Female=0;
Agent a;
Agent nouv;
GtkWidget *radiobuttonMale, *radiobuttonFemale;
void on_Full_Time_toggled(GtkToggleButton *Full_Time, gpointer user_data)
{


}

void
on_Permanent_toggled                   (GtkToggleButton *Permanent,gpointer         user_data)
{
}

void
on_Part_Time_toggled                   (GtkToggleButton *Part_Time,
                                        gpointer         user_data)
{
 
}

void
on_Temporary_Seasonal_toggled (GtkToggleButton *Temporary_Seasonal, gpointer         user_data)
{

}


void on_CancelAdd_clicked(GtkButton *button, gpointer user_data)
{
    // Declare all widgets
    GtkWidget *entryNIC, *entryFirstName, *entryLastName, *entryPhoneNumber, *entryadress;
    GtkWidget *combo_entry5;
    GtkWidget *spinbutton2, *spinbutton3, *spinbutton4;
    GtkWidget *radiobutton1, *radiobutton2;
    GtkWidget *Permanent, *Full_Time, *Part_Time, *Temporary_Seasonal;

    // Look up all widgets using the button as context
    entryNIC = lookup_widget(GTK_WIDGET(button), "entryNIC");
    entryFirstName = lookup_widget(GTK_WIDGET(button), "entryFirstName");
    entryLastName = lookup_widget(GTK_WIDGET(button), "entryLastName");
    entryPhoneNumber = lookup_widget(GTK_WIDGET(button), "entryPhoneNumber");
    entryadress = lookup_widget(GTK_WIDGET(button), "entryadress");

    spinbutton2 = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    spinbutton3 = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    spinbutton4 = lookup_widget(GTK_WIDGET(button), "spinbutton4");

    combo_entry5 = lookup_widget(GTK_WIDGET(button), "combo_entry5");

    radiobutton1 = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radiobutton2 = lookup_widget(GTK_WIDGET(button), "radiobutton2");

    Permanent = lookup_widget(GTK_WIDGET(button), "Permanent");
    Temporary_Seasonal = lookup_widget(GTK_WIDGET(button), "Temporary_Seasonal");
    Full_Time = lookup_widget(GTK_WIDGET(button), "Full_Time");
    Part_Time = lookup_widget(GTK_WIDGET(button), "Part_Time");

    // Clear text entries
    gtk_entry_set_text(GTK_ENTRY(entryNIC), "");
    gtk_entry_set_text(GTK_ENTRY(entryFirstName), "");
    gtk_entry_set_text(GTK_ENTRY(entryLastName), "");
    gtk_entry_set_text(GTK_ENTRY(entryPhoneNumber), "");
    gtk_entry_set_text(GTK_ENTRY(entryadress), "");

    // Reset spin button values (set to 0)
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton3), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton4), 0);

    // Reset combo box selection and clear text
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_entry5), -1);  // Deselect any item
    GtkWidget *entry_in_combo = gtk_bin_get_child(GTK_BIN(combo_entry5));  // Get the entry inside the combo box
    gtk_entry_set_text(GTK_ENTRY(entry_in_combo), "");  // Clear the text in the combo box entry

    // Uncheck gender radio buttons
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2), FALSE);

    // Uncheck contract type checkboxes (unselect all)
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Permanent), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Temporary_Seasonal), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Full_Time), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Part_Time), FALSE);

    // Optionally, print a message to confirm the action
    g_print("Adding cancelled. All information cleared.\n");
}




void on_SaveAdd_clicked(GtkButton *SaveAdd, gpointer user_data) {
    Agent a;
    GtkWidget *entryNIC, *entryFirstName, *entryLastName, *entryPhoneNumber, *entryadress;
    GtkWidget *combo_entry5;
    GtkWidget *spinbutton2, *spinbutton3, *spinbutton4;
    GtkWidget *radiobutton1, *radiobutton2;
  
    // Lookup widgets
    entryNIC = lookup_widget(GTK_WIDGET(SaveAdd), "entryNIC");
    entryFirstName = lookup_widget(GTK_WIDGET(SaveAdd), "entryFirstName");
    entryLastName = lookup_widget(GTK_WIDGET(SaveAdd), "entryLastName");
    entryPhoneNumber = lookup_widget(GTK_WIDGET(SaveAdd), "entryPhoneNumber");
    entryadress = lookup_widget(GTK_WIDGET(SaveAdd), "entryadress");
    spinbutton2 = lookup_widget(GTK_WIDGET(SaveAdd), "spinbutton2");
    spinbutton3 = lookup_widget(GTK_WIDGET(SaveAdd), "spinbutton3");
    spinbutton4 = lookup_widget(GTK_WIDGET(SaveAdd), "spinbutton4");
    combo_entry5 = lookup_widget(GTK_WIDGET(SaveAdd), "combo_entry5");
    radiobutton1 = lookup_widget(GTK_WIDGET(SaveAdd), "radiobutton1");
    radiobutton2 = lookup_widget(GTK_WIDGET(SaveAdd), "radiobutton2");

    // Gender validation
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1))) {
        strcpy(a.Sexe, "Male");
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2))) {
        strcpy(a.Sexe, "Female");
    } 
    else {
        g_print("Error: No gender selected.\n");
        GtkWidget *gender_window;
        gender_window = create_Gender(); 
        gtk_widget_show(gender_window);
        return ;  // Stop further processing
    }

    // Populate agent data
    strcpy(a.FirstName, gtk_entry_get_text(GTK_ENTRY(entryFirstName)));
    strcpy(a.LastName, gtk_entry_get_text(GTK_ENTRY(entryLastName)));
    strcpy(a.Adress, gtk_entry_get_text(GTK_ENTRY(entryadress)));
    strcpy(a.NIC, gtk_entry_get_text(GTK_ENTRY(entryNIC)));
    strcpy(a.PhoneNumber, gtk_entry_get_text(GTK_ENTRY(entryPhoneNumber)));
    strcpy(a.Workspace,
gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_entry5)));
  
    a.Dateofbirth.Day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton4));
    a.Dateofbirth.Month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton3));
    a.Dateofbirth.Year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
   
    // Contract Type logic
    strcpy(a.Contract_Type, "");
    GtkWidget *Permanent = lookup_widget(GTK_WIDGET(SaveAdd), "Permanent");
    GtkWidget *Temporary_Seasonal = lookup_widget(GTK_WIDGET(SaveAdd), "Temporary_Seasonal");
    GtkWidget *Full_Time = lookup_widget(GTK_WIDGET(SaveAdd), "Full_Time");
    GtkWidget *Part_Time = lookup_widget(GTK_WIDGET(SaveAdd), "Part_Time");

    // Construct the contract type string
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Full_Time))) {
        strcat(a.Contract_Type, "Full_Time|");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Permanent))) {
        strcat(a.Contract_Type, "Permanent|");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Part_Time))) {
        strcat(a.Contract_Type, "Part_Time|");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Temporary_Seasonal))) {
        strcat(a.Contract_Type, "Temporary_Seasonal|");
    }

    // Remove the last '|' if it exists
    size_t len = strlen(a.Contract_Type);
    if (len > 0 && a.Contract_Type[len - 1] == '|') {
        a.Contract_Type[len - 1] = '\0';
    }
  
    // Add agent and handle success/failure
    if (AddAgent("agents.txt", a)) {
        g_print("Agent successfully added.\n");
        GtkWidget *Add_window = lookup_widget(GTK_WIDGET(SaveAdd), "Add");
        gtk_widget_destroy(Add_window);
        GtkWidget *success_window = create_Success();
        gtk_widget_show(success_window);
    } else {
        g_print("Error when adding the agent.\n");
        GtkWidget *Add_window = lookup_widget(GTK_WIDGET(SaveAdd), "Add");
        gtk_widget_destroy(Add_window);
        GtkWidget *echec_window = create_Echec();
        gtk_widget_show(echec_window);
    }
}


void
on_radiobutton1_toggled(GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        Male= 1;
        Female=0;   
}
}

void
on_radiobutton2_toggled(GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton)) {
        Female = 2;
        Male=0;     
        
}
}


void on_Editedit_clicked(GtkButton *Editedit, gpointer user_data) {
    char NIC1[20];
    //Agent found_agent;
    GtkWidget *entryNIC = lookup_widget(GTK_WIDGET(Editedit), "entryNIC");
    GtkWidget *entryFirstName = lookup_widget(GTK_WIDGET(Editedit), "entryFirstName");
    GtkWidget *entryLastName = lookup_widget(GTK_WIDGET(Editedit), "entryLastName");
    GtkWidget *entryPhoneNumber = lookup_widget(GTK_WIDGET(Editedit), "entryPhoneNumber");
    GtkWidget *entryAdress = lookup_widget(GTK_WIDGET(Editedit), "entryAdress");
    GtkWidget *comboboxentry2 = lookup_widget(GTK_WIDGET(Editedit), "comboboxentry2");

    GtkWidget *spinbuttonDay = lookup_widget(GTK_WIDGET(Editedit), "spinbuttonDay");
    GtkWidget *spinbuttonMonth = lookup_widget(GTK_WIDGET(Editedit), "spinbuttonMonth");
    GtkWidget *spinbuttonYear = lookup_widget(GTK_WIDGET(Editedit), "spinbuttonYear");

    GtkWidget *radiobuttonMale = lookup_widget(GTK_WIDGET(Editedit), "radiobuttonMale");
    GtkWidget *radiobuttonFemale = lookup_widget(GTK_WIDGET(Editedit), "radiobuttonFemale");

    GtkWidget *checkbuttonPermanent = lookup_widget(GTK_WIDGET(Editedit), "checkbuttonPermanent");
    GtkWidget *checkbuttonTemporary = lookup_widget(GTK_WIDGET(Editedit), "checkbuttonTemporary");
    GtkWidget *checkbuttonFull_Time = lookup_widget(GTK_WIDGET(Editedit), "checkbuttonFull_Time");
    GtkWidget *checkbuttonPart_Time = lookup_widget(GTK_WIDGET(Editedit), "checkbuttonPart_Time");

    strcpy(NIC1, gtk_entry_get_text(GTK_ENTRY(entryNIC)));
    g_strstrip(NIC1); 
    snprintf(nouv.NIC, sizeof(nouv.NIC), "%s", NIC1);

    strcpy(nouv.FirstName, gtk_entry_get_text(GTK_ENTRY(entryFirstName)));
    strcpy(nouv.LastName, gtk_entry_get_text(GTK_ENTRY(entryLastName)));
    strcpy(nouv.Adress, gtk_entry_get_text(GTK_ENTRY(entryAdress)));
    strcpy(nouv.PhoneNumber, gtk_entry_get_text(GTK_ENTRY(entryPhoneNumber)));
    strcpy(nouv.Workspace, gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxentry2)));

    nouv.Dateofbirth.Day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonDay));
    nouv.Dateofbirth.Month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonMonth));
    nouv.Dateofbirth.Year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonYear));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonMale)))
        strcpy(nouv.Sexe, "Male");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonFemale)))
        strcpy(nouv.Sexe, "Female");

    // Construct Contract_Type
    nouv.Contract_Type[0] = '\0';
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonPermanent))) strcat(nouv.Contract_Type, "Permanent|");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonTemporary))) strcat(nouv.Contract_Type, "Temporary|");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonFull_Time))) strcat(nouv.Contract_Type, "Full_Time|");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonPart_Time))) strcat(nouv.Contract_Type, "Part_Time|");
    if (nouv.Contract_Type[strlen(nouv.Contract_Type) - 1] == '|') nouv.Contract_Type[strlen(nouv.Contract_Type) - 1] = '\0';
    if (EditAgent("agents.txt", NIC1, nouv)) {
        g_print("Agent information successfully modified.\n");
        GtkWidget *edit_window;
	GtkWidget *confirm_window;
        edit_window = lookup_widget(GTK_WIDGET(Editedit), "Edit");
        gtk_widget_destroy(edit_window);
        confirm_window = create_Confirmation ();
        gtk_widget_show(confirm_window);
    } else {
        g_print("No agent found with NIC: %s\n", NIC1);
	GtkWidget *Agent_not_found,*edit_window;
        edit_window = lookup_widget(GTK_WIDGET(Editedit), "Edit");
        gtk_widget_destroy(edit_window);
	Agent_not_found = create_Agent_not_found();
        gtk_widget_show (Agent_not_found);
}
}


void on_verifier_clicked(GtkButton *button, gpointer user_data) {
    char NIC[20];
    GtkWidget *entryNIC, *entryFirstName, *entryLastName, *entryPhoneNumber, *entryAdress, *comboboxentry2 , *agent_not_found_window,*edit_window ;
    GtkWidget *spinbuttonDay, *spinbuttonMonth, *spinbuttonYear;
    GtkWidget *radiobuttonMale, *radiobuttonFemale;
    GtkWidget *checkbuttonPermanent, *checkbuttonTemporary, *checkbuttonFull_Time, *checkbuttonPart_Time;
    Agent nouv;

    // Récupération des widgets
    entryNIC = lookup_widget(GTK_WIDGET(button), "entryNIC");
    entryFirstName = lookup_widget(GTK_WIDGET(button), "entryFirstName");
    entryLastName = lookup_widget(GTK_WIDGET(button), "entryLastName");
    entryPhoneNumber = lookup_widget(GTK_WIDGET(button), "entryPhoneNumber");
    entryAdress = lookup_widget(GTK_WIDGET(button), "entryAdress");

    spinbuttonDay = lookup_widget(GTK_WIDGET(button), "spinbuttonDay");
    spinbuttonMonth = lookup_widget(GTK_WIDGET(button), "spinbuttonMonth");
    spinbuttonYear = lookup_widget(GTK_WIDGET(button), "spinbuttonYear");

    radiobuttonMale = lookup_widget(GTK_WIDGET(button), "radiobuttonMale");
    radiobuttonFemale = lookup_widget(GTK_WIDGET(button), "radiobuttonFemale");

    comboboxentry2 = lookup_widget(GTK_WIDGET(button), "comboboxentry2");

    checkbuttonPermanent = lookup_widget(GTK_WIDGET(button), "checkbuttonPermanent");
    checkbuttonTemporary = lookup_widget(GTK_WIDGET(button), "checkbuttonTemporary");
    checkbuttonFull_Time = lookup_widget(GTK_WIDGET(button), "checkbuttonFull_Time");
    checkbuttonPart_Time = lookup_widget(GTK_WIDGET(button), "checkbuttonPart_Time");

    // Récupération du NIC
    strcpy(NIC, gtk_entry_get_text(GTK_ENTRY(entryNIC)));
    g_strstrip(NIC); // Suppression des espaces inutiles

    // Recherche de l'agent
    if (SearchAgent("agents.txt", NIC, &nouv)) {
        // Remplir les champs du formulaire
        gtk_entry_set_text(GTK_ENTRY(entryFirstName), nouv.FirstName);
        gtk_entry_set_text(GTK_ENTRY(entryLastName), nouv.LastName);
        gtk_entry_set_text(GTK_ENTRY(entryAdress), nouv.Adress);
        gtk_entry_set_text(GTK_ENTRY(entryPhoneNumber), nouv.PhoneNumber);

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonDay), nouv.Dateofbirth.Day);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonMonth), nouv.Dateofbirth.Month);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonYear), nouv.Dateofbirth.Year);

        // Boutons radio pour le sexe
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonMale), strcmp(nouv.Sexe, "Male") == 0);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonFemale), strcmp(nouv.Sexe, "Female") == 0);

        // Combobox pour le lieu de travail
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboboxentry2), nouv.Workspace);
        gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxentry2), 0);

        // Réinitialiser les checkbuttons avant de les configurer
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonPermanent), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonTemporary), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonFull_Time), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonPart_Time), FALSE);

        // Suppression des espaces inutiles dans Contract_Type
        g_strstrip(nouv.Contract_Type);

        // Découpage de la chaîne Contract_Type avec strtok
        char *token = strtok(nouv.Contract_Type, "|");
        while (token != NULL) {
            // Supprimer les espaces dans le token
            g_strstrip(token);

            if (strcmp(token, "Full_Time") == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonFull_Time), TRUE);
            } else if (strcmp(token, "Part_Time") == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonPart_Time), TRUE);
            } else if (strcmp(token, "Permanent") == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonPermanent), TRUE);
            } else if (strcmp(token, "Temporary") == 0) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonTemporary), TRUE);
            }

            // Passe au token suivant
            token = strtok(NULL, "|");
        }

        g_print("Agent found and information displayed.\n");
    } else {
        g_print("Agent not found with NIC: %s\n", NIC);
        // Agent not found: show the Agent_not_found window
        agent_not_found_window = create_Agent_not_found();
        gtk_widget_show(agent_not_found_window);
        edit_window = lookup_widget(GTK_WIDGET(button), "Edit");
        gtk_widget_destroy(edit_window);
    }
}







void on_Delete_clicked(GtkButton *button, gpointer user_data) {
    char NIC[20];
    GtkWidget *ID_entry;
    GtkWidget *Delete_confirmation, *agent_not_found_window, *delete_window , *remove_window ;
    Agent found_agent; // Struct to hold the found agent's data

    // Get the NIC from the entry field
    ID_entry = lookup_widget(GTK_WIDGET(button), "ID_entry");
    strcpy(NIC, gtk_entry_get_text(GTK_ENTRY(ID_entry)));

    // Check if the agent exists in the file using the SearchAgent function
    if (SearchAgent("agents.txt", NIC, &found_agent)) {
        // Agent found: show the confirmation window
        Delete_confirmation = create_Delete_confirmation();
        gtk_widget_show(Delete_confirmation);
        g_object_set_data_full(G_OBJECT(Delete_confirmation),"NIC",
g_strdup(NIC),g_free);      
        remove_window= lookup_widget(GTK_WIDGET(button), "Remove");
        gtk_widget_destroy(remove_window);
    } else {
        // Agent not found: show the Agent_not_found window
        agent_not_found_window = create_Agent_not_found();
        gtk_widget_show(agent_not_found_window);
        remove_window = lookup_widget(GTK_WIDGET(button), "Remove");
        gtk_widget_destroy(remove_window);
    }
}







void
on_Close_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *reser_window;
    GtkWidget *display_window;
    reser_window = lookup_widget(GTK_WIDGET(button), "Tache_supplementaire_");
    gtk_widget_destroy(reser_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);

}




void
on_yes_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *yes_window,*Success;
    yes_window = lookup_widget(GTK_WIDGET(button), "Confirmation");
    gtk_widget_destroy(yes_window);
    Success = create_Success ();
    gtk_widget_show (Success);
}


 
void
on_cancelconfirmation_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *confirmation_window;
    GtkWidget *remove_window;
    confirmation_window = lookup_widget(GTK_WIDGET(button), "Delete_confirmation");
    gtk_widget_destroy(confirmation_window);
    remove_window = create_Remove ();
    gtk_widget_show(remove_window);
}


void on_confirm_clicked(GtkButton *button, gpointer user_data) {
   GtkWidget *Delete = gtk_widget_get_toplevel(GTK_WIDGET(button));
   char *NIC = (char*)g_object_get_data(G_OBJECT(Delete),"NIC");
   if(NIC){
     if(DeleteAgent("agents.txt",NIC)){
     GtkWidget *successfulldel = create_successfull_deletion ();
     gtk_widget_show(successfulldel);
}
   else{
     g_warning("agent introuvable");
}
}
   else{
     g_critical("aucun id associe a la boite de dialogue");
}
   gtk_widget_hide(Delete);
}


void
on_oksuccess_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *success_window;
    success_window = lookup_widget(GTK_WIDGET(button), "Success");
    gtk_widget_destroy(success_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);
}


void
on_okoups_clicked (GtkButton *button,gpointer  user_data)
{
    GtkWidget *display_window;
    GtkWidget *echec_window;
    echec_window = lookup_widget(GTK_WIDGET(button), "Echec");
    gtk_widget_destroy(echec_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);
}


void
on_no_clicked (GtkButton *button,gpointer user_data)
{
    GtkWidget *no_window, *display_window ;
    no_window = lookup_widget(GTK_WIDGET(button), "Confirmation");
    gtk_widget_destroy(no_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);
}

void on_Savedisplay_clicked(GtkButton *button, gpointer user_data) {
 
}

void on_Editdisplay_clicked(GtkButton *button, gpointer user_data) 
{
    GtkWidget *display_window;
    GtkWidget *edit_window;
    display_window = lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    edit_window = create_Edit ();
    gtk_widget_show(edit_window);
}

void on_Deletedisplay_clicked(GtkButton *button, gpointer user_data) 
{
    GtkWidget *display_window;
    GtkWidget *remove_window;
    display_window= lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    remove_window = create_Remove ();
    gtk_widget_show(remove_window);

}

void on_Canceldisplay_clicked(GtkButton *button, gpointer user_data) 
{
    GtkWidget *display_window;
    display_window = lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
}


void on_Adddisplay_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *display_window;
    GtkWidget *add_window;
    display_window = lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    add_window = create_Add();
    gtk_widget_show(add_window);
}



void
on_radiobuttonFemale_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonFemale)))
Female=2;
}


void
on_radiobuttonMale_toggled             (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonMale)))
Male=1;
}




void
on_checkbuttonFull_Time_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbuttonPart_Time_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbuttonTemporary_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_checkbuttonPermanent_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_retour1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *add_window;
    add_window= lookup_widget(GTK_WIDGET(button), "Add");
    gtk_widget_destroy(add_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);
}


void
on_retour2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *edit_window;
    edit_window= lookup_widget(GTK_WIDGET(button), "Edit");
    gtk_widget_destroy(edit_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);

}


void
on_Reservation_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *reser_window;
    display_window= lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    reser_window = create_Tache_supplementaire_ ();
    gtk_widget_show (reser_window);

}


void
on_retour3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *remove_window;
    remove_window= lookup_widget(GTK_WIDGET(button), "Remove");
    gtk_widget_destroy(remove_window);
    display_window = create_Display ();
    gtk_widget_show(display_window);
}


void
on_retour4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}

void on_Rechercher_clicked(GtkButton *Rechercher, gpointer user_data) {
    GtkWidget *Tache_supplementaire_;  
    GtkWidget *treeview2; 
    GtkWidget *spin_button_jour, *spin_button_mois, *spin_button_annee;
    gint jour, mois, annee;
    char date_recherche[15];

    // Récupérer la fenêtre principale "gestionagentsparkings" depuis Glade
    Tache_supplementaire_ = lookup_widget(GTK_WIDGET(Rechercher), "Tache_supplementaire_");

    if (Tache_supplementaire_ == NULL) {
        g_print("Erreur : Fenêtre non trouvée dans Glade.\n");
        return;
    }    
    gtk_widget_show_all(Tache_supplementaire_);

    treeview2 = lookup_widget(Tache_supplementaire_, "treeview2");
    if (treeview2 == NULL) {
        g_print("Erreur : TreeView2 non trouvé dans Glade.\n");
        return;
    }

    // Récupérer les valeurs des SpinButtons
    spin_button_jour = lookup_widget(Tache_supplementaire_, "spinbutton1");
    spin_button_mois = lookup_widget(Tache_supplementaire_, "spinbutton2");
    spin_button_annee = lookup_widget(Tache_supplementaire_,"spinbutton3");

    if (spin_button_jour == NULL || spin_button_mois == NULL || spin_button_annee == NULL) {
        g_print("Erreur : SpinButton non trouvé dans Glade.\n");
        return;
    }

    // Récupérer les valeurs sélectionnées dans les SpinButtons
    jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_jour));
    mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_mois));
    annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_annee));

    // Assembler la date dans une chaîne de caractères au format "dd/mm/yyyy"
    sprintf(date_recherche, "%02d/%02d/%04d", jour, mois, annee);

    // Appeler la fonction afficher pour remplir le TreeView avec les réservations correspondant à la date
    afficherlistereserv("reservations.txt", treeview2, date_recherche);
}


void
on_research_clicked (GtkButton *research, gpointer user_data)
{
    GtkWidget *Display;  
    GtkWidget *treeview1;  

    Display = lookup_widget(GTK_WIDGET(research), "Display");

    if (Display == NULL) {
        g_print("Erreur : Fenêtre non trouvée dans Glade.\n");
        return;
    }

    gtk_widget_show_all(Display);

    // Récupérer le TreeView "treeview4" depuis la fenêtre
    treeview1 = lookup_widget(Display, "treeview1");
    if (treeview1 == NULL) {
        g_print("Erreur : TreeView non trouvé dans Glade.\n");
        return;
    }

    // Appeler la fonction afficher pour remplir le TreeView
    DisplayAgents("agents.txt", treeview1);
}



void
on_bye_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_bye1_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *sd_window ;
    display_window = create_Display ();
    gtk_widget_show(display_window);
    sd_window = lookup_widget(GTK_WIDGET(button), "successfull_deletion");
    gtk_widget_destroy(sd_window);

}


void
on_bye2_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *agent_not_found_window;
    display_window = create_Display ();
    gtk_widget_show(display_window);
    agent_not_found_window= lookup_widget(GTK_WIDGET(button), "Agent_not_found");
    gtk_widget_destroy(agent_not_found_window);
  
}


void
on_canceledit_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entryNIC, *entryFirstName, *entryLastName, *entryPhoneNumber, *entryAdress;
    GtkWidget *comboboxentry2;
    GtkWidget *spinbuttonDay, *spinbuttonMonth, *spinbuttonYear;
    GtkWidget *radiobutton1, *radiobutton2;
    GtkWidget *Permanent, *Full_Time, *Part_Time, *Temporary_Seasonal;

    // Look up all widgets using the button as context
    entryNIC = lookup_widget(GTK_WIDGET(button), "entryNIC");
    entryFirstName = lookup_widget(GTK_WIDGET(button), "entryFirstName");
    entryLastName = lookup_widget(GTK_WIDGET(button), "entryLastName");
    entryPhoneNumber = lookup_widget(GTK_WIDGET(button), "entryPhoneNumber");
    entryAdress = lookup_widget(GTK_WIDGET(button), "entryAdress");

    spinbuttonDay = lookup_widget(GTK_WIDGET(button), "spinbuttonDay");
    spinbuttonMonth = lookup_widget(GTK_WIDGET(button), "spinbuttonMonth");
    spinbuttonYear = lookup_widget(GTK_WIDGET(button), "spinbuttonYear");

    comboboxentry2 = lookup_widget(GTK_WIDGET(button), "comboboxentry2");

    radiobutton1 = lookup_widget(GTK_WIDGET(button), "radiobuttonFemale");
    radiobutton2 = lookup_widget(GTK_WIDGET(button), "radiobuttonMale");

    Permanent = lookup_widget(GTK_WIDGET(button), "checkbuttonPermanent");
    Temporary_Seasonal = lookup_widget(GTK_WIDGET(button), "checkbuttonTemporary");
    Full_Time = lookup_widget(GTK_WIDGET(button), "checkbuttonFull_Time");
    Part_Time = lookup_widget(GTK_WIDGET(button), "checkbuttonPart_Time");

    // Clear text entries
    gtk_entry_set_text(GTK_ENTRY(entryNIC), "");
    gtk_entry_set_text(GTK_ENTRY(entryFirstName), "");
    gtk_entry_set_text(GTK_ENTRY(entryLastName), "");
    gtk_entry_set_text(GTK_ENTRY(entryPhoneNumber), "");
    gtk_entry_set_text(GTK_ENTRY(entryAdress), "");

    // Reset spin button values (set to 0)
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonDay), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonMonth), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonYear), 0);

    // Reset combo box selection and clear text
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxentry2), -1);  // Deselect any item
    GtkWidget *entry_in_combo = gtk_bin_get_child(GTK_BIN(comboboxentry2));  // Get the entry inside the combo box
    gtk_entry_set_text(GTK_ENTRY(entry_in_combo), "");  

    // Uncheck gender radio buttons
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2), FALSE);

  
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Permanent), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Temporary_Seasonal), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Full_Time), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Part_Time), FALSE);

    g_print("Editing cancelled. All information cleared.\n");
}



void on_Research2_clicked(GtkButton *button, gpointer user_data) 
{
    char NIC[20];
    GtkWidget *label86 = lookup_widget(GTK_WIDGET(button), "label86");
    GtkWidget *label83 = lookup_widget(GTK_WIDGET(button), "label83");
    GtkWidget *entry1 ;
    Agent found_agent; 
    char texte_resultat[200];
    char texte[200];
    // Get the NIC from the entry field
    entry1 = lookup_widget(GTK_WIDGET(button), "entry1");
    strcpy(NIC, gtk_entry_get_text(GTK_ENTRY(entry1)));

    // Check if the agent exists in the file using the SearchAgent function
    if (SearchAgent("agents.txt", NIC, &found_agent)) {
        // Agent found: show the info
        snprintf(texte_resultat, sizeof(texte_resultat),"First Name:  %s \nLast Name : %s \nWorkspace:  %s \nSexe:  %s \n", found_agent.FirstName , found_agent.LastName , found_agent.Workspace ,  found_agent.Sexe );
        gtk_label_set_text(GTK_LABEL(label86), texte_resultat);
        snprintf(texte, sizeof(texte),"Agent with NIC '%s' found and here are its information :\n\n ", NIC );
        gtk_label_set_text(GTK_LABEL(label83), texte);

    } else {
        // Agent not found: 
        snprintf(texte_resultat, sizeof(texte_resultat)," Agent with NIC '%s' not found ", NIC );
        gtk_label_set_text(GTK_LABEL(label86), texte_resultat);
        snprintf(texte, sizeof(texte),"\n");
        gtk_label_set_text(GTK_LABEL(label83), texte);
}
}


void
on_researchID_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *res_window;
    display_window= lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    res_window = create_Research();
    gtk_widget_show (res_window);

}


void
on_button2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *ID_window;
    ID_window= lookup_widget(GTK_WIDGET(button), "Research");
    gtk_widget_destroy(ID_window);
    display_window = create_Display();
    gtk_widget_show (display_window);

}


void
on_buttonservice_gerer_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonadministrateur_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *home_window;
    GtkWidget *admin_window;
    home_window= lookup_widget(GTK_WIDGET(button), "admincitoyen");
    gtk_widget_destroy(home_window);
    admin_window = create_gerer();
    gtk_widget_show (admin_window);
}


void
on_buttonagents_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *display_window;
    GtkWidget *admin_window;
    admin_window= lookup_widget(GTK_WIDGET(button), "gerer");
    gtk_widget_destroy(admin_window);
    display_window = create_Display();
    gtk_widget_show (display_window);
}


void
on_button_retour_ladmincitoyen_clicked (GtkButton       *button,
                                        gpointer         user_data)
{   
    GtkWidget *gestion_window;
    GtkWidget *admin_window;
    gestion_window= lookup_widget(GTK_WIDGET(button), "gerer");
    gtk_widget_destroy(gestion_window);
    admin_window = create_admincitoyen();
    gtk_widget_show (admin_window);
}



void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *gestion_window;
    GtkWidget *display_window;
    display_window= lookup_widget(GTK_WIDGET(button), "Display");
    gtk_widget_destroy(display_window);
    gestion_window = create_gerer();
    gtk_widget_show (gestion_window);
}

