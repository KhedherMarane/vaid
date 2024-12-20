#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonctions.h"

int choix[]={0,0,0,0}; 
void on_Full_Time_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix[0]=1;}
}
void on_Permanent_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix[3]=1;}
}
 
void on_Part_Time_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix[1]=1;}
}

void on_Temporary_Seasonal_toggled(GtkToggleButton *togglebutton,gpointer user_data)
{
if (gtk_toggle_button_get_active(togglebutton))
{choix[2]=1;}
}
void on_SaveAdd_clicked(GtkButton *button,gpointer user_data)
{
char texte[100]="";
GtkWidget*output;
GtkWidget*entryNIC;
GtkWidget*entryFirstName;
GtkWidget*entryLastName;
GtkWidget*entryPhoneNumber;
GtkWidget*entryadress;
entryNIC=lookup_widget(button,"entryNIC");
entryFirstName=lookup_widget(button,"entryFirstName");
entryLastName=lookup_widget(button,"entryLastName");
entryPhoneNumber=lookup_widget(button,"entryPhoneNumber");
entryadress=lookup_widget(button,"entryadress");
output=lookup_widget(button,"labelresultat");
resultat(choix,texte);
gtk_label_set_text(GTK_LABEL(output), texte);
}
void on_CancelAdd_clicked(GtkButton*button,gpointer user_data)
{
}

