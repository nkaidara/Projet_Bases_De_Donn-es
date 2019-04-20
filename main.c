#include <stdlib.h>
#include <gtk/gtk.h>
#include "fonction.h"
#include <time.h>
typedef struct donnee{
    int mois;
    int annee;
    GtkWidget** widgets;
    GtkWidget* label_mois;
    GtkWidget* bprec;
    GtkWidget* bsuiv;
}Donnee;

void get_date(int* day, int* month, int*year);
void afficher_mois(GtkWidget** widgets,int mois,int annee,GtkWidget*);
void on_precedent_clicked(GtkWidget* w, gpointer data);
void on_suivant_clicked(GtkWidget* w, gpointer data);
void on_aujourdhui_clicked(GtkWidget* w,gpointer data);

int main (int argc, char **argv)
{
    Donnee* d =(Donnee*)malloc(sizeof(Donnee));
    GtkWidget* fenetre = NULL;
    gtk_init(&argc,&argv);
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget* lundi = NULL;
    GtkWidget* mardi = NULL;
    GtkWidget* mercredi = NULL;
    GtkWidget* jeudi = NULL;
    GtkWidget* vendredi = NULL;
    GtkWidget* samedi = NULL;
    GtkWidget* dimanche = NULL;

    GtkWidget* mois = NULL;
    GtkWidget* bprec = NULL;
    GtkWidget* bsuiv = NULL;
    GtkWidget* table = NULL;
    GtkWidget* bjour = NULL;

    GtkWidget** widgets = NULL;

    lundi = gtk_label_new("Lundi");
    gtk_label_set_justify(lundi, GTK_JUSTIFY_CENTER);
    mardi = gtk_label_new("Mardi");
    gtk_label_set_justify(mardi, GTK_JUSTIFY_CENTER);
    mercredi = gtk_label_new("Mercredi");
    gtk_label_set_justify(mercredi, GTK_JUSTIFY_CENTER);
    jeudi = gtk_label_new("Jeudi");
    gtk_label_set_justify(jeudi, GTK_JUSTIFY_CENTER);
    vendredi = gtk_label_new("Vendredi");
    gtk_label_set_justify(vendredi, GTK_JUSTIFY_CENTER);
    samedi = gtk_label_new("Samedi");
    gtk_label_set_justify(samedi, GTK_JUSTIFY_CENTER);
    dimanche = gtk_label_new("Dimanche");
    gtk_label_set_justify(dimanche, GTK_JUSTIFY_CENTER);

    mois = gtk_label_new("Avril 2019");
    gtk_label_set_justify(GTK_LABEL(mois),GTK_JUSTIFY_CENTER);


    bprec = gtk_button_new_with_label("Précédent");
    gtk_label_set_justify(bprec,GTK_JUSTIFY_CENTER);
    bsuiv = gtk_button_new_with_label("Suivant");
    gtk_label_set_justify(bprec,GTK_JUSTIFY_CENTER);
    table = gtk_table_new(8,7, TRUE);



    gtk_table_attach_defaults(GTK_TABLE(table), bprec, 0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),mois,3,4,0,1);
    gtk_table_attach_defaults(GTK_TABLE(table),bsuiv,6,7,0,1);

    gtk_table_attach_defaults(GTK_TABLE(table),lundi,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),mardi,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),mercredi,2,3,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),jeudi,3,4,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),vendredi,4,5,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),samedi,5,6,1,2);
    gtk_table_attach_defaults(GTK_TABLE(table),dimanche,6,7,1,2);

    widgets = g_new(GtkWidget*,42);
    gint colonne = 0,ligne = 2;
    int i=0;
    while(i < 42){
        widgets[i] = gtk_label_new("19");
        gtk_label_set_justify(widgets[i],GTK_JUSTIFY_CENTER);
        gtk_table_attach_defaults(GTK_TABLE(table),widgets[i],colonne,colonne+1, ligne, ligne+1);
        colonne++;
        i++;
        if(colonne == 7){
            colonne = 0;
            ligne++;
        }

    }

    bjour = gtk_button_new_with_label("Aujourd'hui");
    gtk_label_set_justify(bjour,GTK_JUSTIFY_CENTER);
   gtk_table_attach_defaults(GTK_TABLE(table),bjour,2,5,7,8);

    d->widgets=widgets;
    d->label_mois=mois;
    d->bprec=bprec;
    d->bsuiv=bsuiv;


    gtk_container_add(GTK_CONTAINER(fenetre), table);
    gtk_window_set_default_size(GTK_WINDOW(fenetre),900,300);


    gtk_window_set_title(GTK_WINDOW(fenetre),"calendrier");
    gtk_widget_show_all(fenetre);
    int day;
    get_date(&day,&(d->mois),&(d->annee));
    afficher_mois(widgets,d->mois,d->annee,d->label_mois);
    int currentMois = 4;
    g_signal_connect(G_OBJECT(bprec),"clicked",G_CALLBACK(on_precedent_clicked),d);
    g_signal_connect(G_OBJECT(bsuiv),"clicked",G_CALLBACK(on_suivant_clicked),d);

    g_signal_connect(G_OBJECT(bjour),"clicked",G_CALLBACK(on_aujourdhui_clicked),d);
    gtk_main();

 return 0;
}


void afficher_mois(GtkWidget** widgets,int mois,int annee,GtkWidget* label_mois){
    int jact, moisact, anneeact;
    get_date(&jact,&moisact,&anneeact);
    gchar* tab_mois[]={"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Août","Semptembre","Octobre","Novembre","Decembre"};
    int offset = get_offset(mois,annee);
    int dernier_jour = daysInMonth[mois - 1];
    int isLeapyear = testLeapYear(annee);
    if(mois == 2 && isLeapyear == 1){
        dernier_jour++;
    }
    int i;
    for(i = 0;i < offset;i++){
        gtk_label_set_label(widgets[i]," ");

    }
    gchar tab[2];
    int col = offset;
    for(i = firstDayOfMonth;i <= dernier_jour; i++){
        g_sprintf(tab,"%d",i);
        gtk_label_set_label(widgets[col] ,tab);
        if (i == jact && mois == moisact && annee == anneeact){
            GdkColor color;
            gdk_color_parse("red",&color);
            gtk_widget_modify_fg(widgets[col],GTK_STATE_NORMAL,&color);
        }
        else{
            GdkColor color;
            gdk_color_parse("black",&color);
            gtk_widget_modify_fg(widgets[col],GTK_STATE_NORMAL,&color);
        }
        col++;
    }

    for(i = col;i<42;i++)
        gtk_label_set_label(widgets[i]," ");
    gchar texte[20];
    g_sprintf(texte, "%s %d", tab_mois[mois-1], annee);
    gtk_label_set_text(label_mois,texte);
}

void get_date(int* day, int* month, int*year){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    *day = local->tm_mday;
    *month = local->tm_mon + 1;
    *year = local->tm_year+ 1900;

}

void on_precedent_clicked(GtkWidget* w, gpointer data){
    Donnee* donnes = (Donnee*)data;
    donnes->mois--;
    if(donnes->mois == 1){
        gtk_widget_set_sensitive(w,FALSE);

    }
    gtk_widget_set_sensitive(donnes->bsuiv,TRUE);
    if(donnes->mois >=1)
        afficher_mois(donnes->widgets,donnes->mois,donnes->annee,donnes->label_mois);
}

void on_suivant_clicked(GtkWidget* w, gpointer data){
    Donnee* donnes = (Donnee*)data;
     donnes->mois++;
    if(donnes->mois == 12){
    gtk_widget_set_sensitive(w,FALSE);
       /*donnes->annee++;
       donnes->mois=1;
        afficher_mois(donnes->widgets,donnes->mois,donnes->annee,donnes->label_mois);*/

    }
    gtk_widget_set_sensitive(donnes->bprec,TRUE);

    if (donnes->mois <= 12)
    afficher_mois(donnes->widgets,donnes->mois,donnes->annee,donnes->label_mois);

    }

void on_aujourdhui_clicked(GtkWidget* w,gpointer data){
    Donnee* donnes = (Donnee*)data;
    int day,month,year;
    get_date(&day,&month,&year);
    donnes->mois = month;
    donnes->annee = year;
    afficher_mois(donnes->widgets,donnes->mois,donnes->annee,donnes->label_mois);

}





