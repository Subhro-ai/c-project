#include <gtk/gtk.h>
#include <stdio.h> 
//#include <conio.h>
//#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

GtkApplication *appMenu;
GtkWidget *win;
GtkWidget *winLogin;
GtkWidget *winSignup;
GtkWidget *winProfile;
GtkWidget *boxh;
GtkWidget *boxv;
GtkWidget *btnLogin;
GtkWidget *btnSignup;
GtkWidget *btnClose;
GtkWidget *btnDone;
GtkWidget *label;
GtkWidget *leftSpace;
GtkWidget *rightSpace;
GtkWidget *welcome;
GtkWidget *centreSpace;
GtkWidget *entryUser;
GtkWidget *entryPass;
GtkWidget *entryFname;
GtkWidget *entryLname;
GtkWidget *grid;
GtkWidget *entryBal;
GtkWidget *entrySum;
GtkWidget *balance;
GtkWidget *error;

struct users{
    char username[15];
    char fname[20];
    char lname[20];
    char pass[10];
    char bal[9];
};

void app_login();
void app_signup();
void app_activate();
void app_profile();
void login(gpointer data);
void signup();
void withdraw();
void deposit();
struct users userFile;

void clearEntry(GtkWidget *widget, gpointer data)
{
    GtkWidget *entry = GTK_WIDGET(data);
    gtk_editable_set_text(GTK_EDITABLE(entry),"");
}


void win_destroy(GtkButton *btn, GtkWindow *win)
{
    gtk_window_destroy(win);
}

char balText[20];
void app_profile()
{
    label = gtk_label_new("YOUR PROFILE");
    gtk_widget_set_name(label, "bank");
    GtkWidget  *text1 = gtk_label_new("Your balance is : ");
    char nameText[50];
    sprintf(nameText, "Welcome! %s %s", userFile.fname, userFile.lname);
    //sprintf(balText, "Your balance is: %s", userFile.bal);
    GtkWidget *name = gtk_label_new(nameText);
    error = gtk_label_new("INSUFFICIENT FUNDS");
    gtk_widget_set_visible(error, FALSE);
    balance = gtk_label_new(userFile.bal);
    entrySum = gtk_entry_new();
    GtkWidget *Wbtn = gtk_button_new_with_label("WITHDRAW");
    GtkWidget *Tbtn = gtk_button_new_with_label("TRANSFER");
    GtkWidget *Dbtn = gtk_button_new_with_label("DEPOSIT");
    btnClose = gtk_button_new_with_label("Close");
    leftSpace = gtk_label_new("");
    rightSpace = gtk_label_new("");
    boxv = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *boxh1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 150);
    GtkWidget *boxh2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *boxh3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_widget_set_name(error, "text"); // Setting the widget name to "text"

    gtk_widget_add_css_class(error, "red-text"); // Add CSS class

    // CSSs to change text color for the class ".red-text" applied to the label named "text"
    const char *css = "#text { color: red; }";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    // CSS to change text Size for the class 
    const char *css1 = "#bank {  font-size: 20px; color: rgb(153, 196, 210); font-weight: bold; font-family: 'Arial', sans-serif;}";
    GtkCssProvider *provider1 = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider1, css1);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    gtk_window_set_child (GTK_WINDOW (winProfile), boxv);
    gtk_box_append(GTK_BOX(boxv), label);
    gtk_box_append(GTK_BOX(boxv), boxh1);
    //gtk_box_append(GTK_BOX(boxh1), leftSpace);
    gtk_box_append(GTK_BOX(boxh1), name);
    gtk_box_append(GTK_BOX(boxv), boxh3); 
    gtk_box_append(GTK_BOX(boxh3), text1); 
    gtk_box_append(GTK_BOX(boxh3), balance);
    gtk_box_append(GTK_BOX(boxv), boxh2);
        gtk_box_append(GTK_BOX(boxh2), entrySum);
        gtk_box_append(GTK_BOX(boxh2), Wbtn);
        gtk_box_append(GTK_BOX(boxh2), Dbtn);
        gtk_box_append(GTK_BOX(boxh2), Tbtn);
    gtk_box_append(GTK_BOX(boxv), error);
    gtk_box_append(GTK_BOX(boxv), btnClose);
    
    g_signal_connect(btnClose, "clicked", G_CALLBACK(win_destroy), winProfile);
    g_signal_connect(Wbtn, "clicked", G_CALLBACK(withdraw), NULL);
    g_signal_connect(Dbtn, "clicked", G_CALLBACK(deposit), NULL);
    g_signal_connect(Tbtn, "clicked", G_CALLBACK(withdraw), NULL);
    g_signal_connect(Wbtn, "clicked", G_CALLBACK(clearEntry), entrySum);
    g_signal_connect(Dbtn, "clicked", G_CALLBACK(clearEntry), entrySum);
    g_signal_connect(Tbtn, "clicked", G_CALLBACK(clearEntry), entrySum);
    gtk_window_present(GTK_WINDOW(winProfile));
}
void deposit()
{
    const char *sum = gtk_editable_get_text(GTK_EDITABLE(entrySum));
    int s = atoi(sum);
    int bal = atoi(userFile.bal);
    if (sum < 0)
    {
        gtk_widget_set_visible(error, TRUE);
        g_print("INSUFFICIENT FUNDS\n");
        return;
    }
    bal += s;
    sprintf(userFile.bal, "%d", bal);
    g_print("%s\n", userFile.bal);
    g_print("%d\n", bal);
    gtk_label_set_text(GTK_LABEL(balance), userFile.bal);
    gtk_widget_set_visible(error, FALSE);
    return;
}
void withdraw()
{
    g_print("WITHDRAW\n");
    const char *sum = gtk_editable_get_text(GTK_EDITABLE(entrySum));
    //g_print("1\n");
    int s = atoi(sum);
    //g_print("2\n");
    int bal = atoi(userFile.bal);
    //g_print("3\n");
    if (s > bal)
    {
        gtk_widget_set_visible(error, TRUE);
        g_print("INSUFFICIENT FUNDS\n");
        return;
    }
    else if (sum < 0)
    {
        gtk_widget_set_visible(error, TRUE);
        g_print("INSUFFICIENT FUNDS\n");
        return;
    }
    else
    {
        //g_print("4\n");
        bal -= s;
        gtk_widget_set_visible(error, FALSE);
        sprintf(userFile.bal, "%d", bal);
        //("%s", userFile.bal);
        //sprintf(balText, "Your balance is: %s", userFile.bal);
        gtk_label_set_text(GTK_LABEL(balance), userFile.bal);
        //g_print("5\n");
        return;
    }
}



void login(gpointer data)
{
    GtkWidget *text = GTK_WIDGET(data);
    gtk_widget_set_name(text, "text"); // Setting the widget name to "text"

    gtk_widget_add_css_class(text, "red-text"); // Add CSS class

    // CSS to change text color for the class ".red-text" applied to the label named "text"
    const char *css = "#text { color: red; }";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const char *usern = gtk_editable_get_text(GTK_EDITABLE(entryUser));
    const char *pass = gtk_editable_get_text(GTK_EDITABLE(entryPass));
    struct users userEntry;
    strcpy(userEntry.pass, pass);
    strcpy(userEntry.username, usern);
    g_print("LOGIN\n");
    //g_print((char *)usern);
    FILE *fptr = fopen("users.txt", "r");
    if (fptr == NULL) 
    { 
        printf("Could not open file"); 
        return; 
    }
    g_print("FIle Opened!\n");
    int count = 0;
    for (char c = getc(fptr); c != EOF; c = getc(fptr))
        if (c == '\n')
            count = count + 1;
    fclose(fptr);
    g_print("Count Finished!");
    FILE *fp = fopen("users.txt", "r");
    bool accFound = false;
    for ( int i = 0; i < count; i++)
    {
        g_print("IN FOR LOOP!\n");
        fscanf(fp, "%s %s %s %s %s", userFile.username, userFile.fname, userFile.lname, userFile.pass, userFile.bal);
        if (strcmp(userEntry.username,userFile.username) == 0)
        {
            g_print("User Found!\n");
            if (strcmp(userEntry.pass,userFile.pass) == 0)
            {
                g_print("PASSWORD IS CORRECT\n");
                gtk_widget_set_visible(text, FALSE);
                //pass userFile struct
                
                gtk_window_destroy(GTK_WINDOW(winLogin));
                g_print("OPENS PROFILE\n");
                app_profile();
                //g_signal_connect(btnDone, "clicked", G_CALLBACK(app_profile), NULL);
                accFound = true;
                fclose(fp);
            }
            else
            {
                //gtk_label_set_text(GTK_LABEL(text), "Wrong Password!");
                //g_print("PASSWORD IS NOT CORRECT\n");
                gtk_widget_set_visible(text, TRUE);
            }
        }
        else
        {
            //gtk_label_set_text(GTK_LABEL(text), "Wrong Username!");
            gtk_widget_set_visible(text, TRUE);
        }
    }
    fclose(fp);  
}
    


void signup()
{
    // Get the text from the entry widget
    const char *usern = gtk_editable_get_text(GTK_EDITABLE(entryUser));
    const char *pass = gtk_editable_get_text(GTK_EDITABLE(entryPass));
    const char *fname = gtk_editable_get_text(GTK_EDITABLE(entryFname));
    const char *lname = gtk_editable_get_text(GTK_EDITABLE(entryLname));
    const char *bal = gtk_editable_get_text(GTK_EDITABLE(entryBal));
    struct users user;
    strcpy(user.fname, fname);
    strcpy(user.lname, lname);
    strcpy(user.pass, pass);
    strcpy(user.username, usern);
    strcpy(user.bal, bal);
    //user.bal = atoi(bal);
    FILE *fptr = fopen("users.txt", "a");
    if (fptr == NULL) 
    { 
        printf("Could not open file"); 
        return; 
    } 
    fprintf(fptr,"%s %s %s %s %s\n", user.username, user.fname, user.lname, user.pass, user.bal);
    fclose(fptr);
}

void app_signup()
{
    label = gtk_label_new("Sign Up");
    gtk_widget_set_name(label, "title");

    //gtk_window_set_child (GTK_WINDOW (winLogin), label);

    btnClose = gtk_button_new_with_label("Close");
    g_signal_connect(btnClose, "clicked", G_CALLBACK(win_destroy), win);

    btnDone = gtk_button_new_with_label("Done");
    entryUser = gtk_entry_new();
    entryPass = gtk_entry_new();
    entryFname = gtk_entry_new();
    entryLname = gtk_entry_new();
    entryBal = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryPass), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryUser), "Enter your Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryPass), "Enter your Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryFname), "Enter your First Name");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryLname), "Enter your Last Name");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryBal), "Enter your Balance");

    GtkWidget *boxv1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *boxv2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *boxv3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    boxh = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 120);
    gtk_window_set_child (GTK_WINDOW (winSignup), boxh);
    gtk_box_set_homogeneous(GTK_BOX(boxv), FALSE);
    gtk_box_append(GTK_BOX(boxh), boxv1);    
    gtk_box_append(GTK_BOX(boxh), boxv2);    
    gtk_box_append(GTK_BOX(boxv2), label);
    gtk_box_append(GTK_BOX(boxv2), entryFname);
    gtk_box_append(GTK_BOX(boxv2), entryLname);
    gtk_box_append(GTK_BOX(boxv2), entryUser);
    gtk_box_append(GTK_BOX(boxv2), entryPass);
    gtk_box_append(GTK_BOX(boxv2), entryBal);

    gtk_box_append(GTK_BOX(boxv2), btnDone);
    gtk_box_append(GTK_BOX(boxv2), btnClose);
    gtk_box_append(GTK_BOX(boxh), boxv3);

    g_signal_connect(btnDone, "clicked", G_CALLBACK(signup), NULL);
    g_signal_connect(btnDone, "clicked", G_CALLBACK(win_destroy), winSignup);
    g_signal_connect(btnDone, "clicked", G_CALLBACK(app_activate), NULL);
    gtk_window_present(GTK_WINDOW(winSignup));
}


//LOGIN PAGE 
void app_login()
{
    label = gtk_label_new("Login");
    gtk_widget_set_name(label, "title");

    //gtk_window_set_child (GTK_WINDOW (winLogin), label);
    GtkWidget *text = gtk_label_new("Wrong PASSWORD Or USERNAME!");
    gtk_widget_set_visible(text, FALSE);

    btnClose = gtk_button_new_with_label("Close");
    g_signal_connect(btnClose, "clicked", G_CALLBACK(win_destroy), winLogin);

    btnDone = gtk_button_new_with_label("Done");
    entryUser = gtk_entry_new();
    entryPass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entryPass), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryUser), "Enter your Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(entryPass), "Enter your Password");

    GtkWidget *boxv1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *boxv2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *boxv3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    boxh = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 120);
    gtk_window_set_child (GTK_WINDOW (winLogin), boxh);
    gtk_box_set_homogeneous(GTK_BOX(boxv), FALSE);
    gtk_box_append(GTK_BOX(boxh), boxv1);    
    gtk_box_append(GTK_BOX(boxh), boxv2);    
    gtk_box_append(GTK_BOX(boxv2), label);
    gtk_box_append(GTK_BOX(boxv2), entryUser);
    gtk_box_append(GTK_BOX(boxv2), entryPass);
    gtk_box_append(GTK_BOX(boxv2), text);
    gtk_box_append(GTK_BOX(boxv2), btnDone);
    gtk_box_append(GTK_BOX(boxv2), btnClose);
    gtk_box_append(GTK_BOX(boxh), boxv3);

    g_signal_connect(btnDone, "clicked", G_CALLBACK(login), text);
    gtk_window_present(GTK_WINDOW(winLogin));
}


//MENU FUNCTION
void app_activate()
{

    win = gtk_application_window_new(GTK_APPLICATION(appMenu));
    gtk_window_set_title(GTK_WINDOW(win), "Bank");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 300);

    winLogin = gtk_application_window_new(GTK_APPLICATION(appMenu));
    gtk_window_set_title(GTK_WINDOW(winLogin), "Login");
    gtk_window_set_default_size(GTK_WINDOW(winLogin), 400, 300);

    winSignup = gtk_application_window_new(GTK_APPLICATION(appMenu));
    gtk_window_set_title(GTK_WINDOW(winSignup), "Sign Up");
    gtk_window_set_default_size(GTK_WINDOW(winSignup), 400, 300);

    winProfile = gtk_application_window_new(GTK_APPLICATION(appMenu));
    gtk_window_set_title(GTK_WINDOW(winProfile), "Your Profile");
    gtk_window_set_default_size(GTK_WINDOW(winProfile), 400, 300);

    boxh = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(boxh), TRUE);
    gtk_window_set_child(GTK_WINDOW(win), boxh);

    boxv = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(boxv), TRUE);

    leftSpace = gtk_label_new (NULL);
    gtk_label_set_width_chars (GTK_LABEL(leftSpace), 10);
    

    centreSpace = gtk_label_new (NULL);
    gtk_widget_set_hexpand (centreSpace, TRUE);
    
    btnLogin = gtk_button_new_with_label("Login");
    g_signal_connect(btnLogin, "clicked", G_CALLBACK(win_destroy), win);
    g_signal_connect(btnLogin, "clicked", G_CALLBACK(app_login), NULL);

    btnSignup = gtk_button_new_with_label("Sign Up");
    g_signal_connect(btnSignup, "clicked", G_CALLBACK(win_destroy), win);
    g_signal_connect(btnSignup, "clicked", G_CALLBACK(app_signup), NULL);

    btnClose = gtk_button_new_with_label("Close");
    g_signal_connect(btnClose, "clicked", G_CALLBACK(win_destroy), win);

    const char cssPath[] = "/Users/subhrajyotisingha/Documents/C/Project/styles.css";
    GtkCssProvider * cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, cssPath);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);


    label = gtk_label_new("WELCOME");
    gtk_widget_set_name(label, "title");

    gtk_box_append(GTK_BOX(boxv), label);
    gtk_box_append(GTK_BOX(boxh), leftSpace);
    gtk_box_append(GTK_BOX(boxh), boxv);
    gtk_box_append(GTK_BOX(boxh), centreSpace);
    gtk_box_append(GTK_BOX(boxv), btnLogin);
    gtk_box_append(GTK_BOX(boxv), btnSignup);
    gtk_box_append(GTK_BOX(boxv), btnClose);;
    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char **argv)
{
    int stat;

    appMenu = gtk_application_new("com.github.ToshioCP.lb4", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(appMenu, "activate", G_CALLBACK(app_activate), NULL);
    stat = g_application_run(G_APPLICATION(appMenu), argc, argv);
    g_object_unref(appMenu);
    return stat;
}