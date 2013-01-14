#include <stdio.h> // unter Win auskommentieren
#include <time.h>
#include <malloc.h>
#include <string.h>
// Win #include <windows.h>

// Struktur der Felder der Spalten
typedef struct {
	// Anzahl der Zeichen die noch folgen
	int count;
	// Farbe des Strangs
	int color;
	// geheimes Wort
	int secret;
	int secretcount;
} column;

const char geheimedinge[4][30]={
	"Wake up Neo",
	"The Matix has you",
	"Why is the Rum gone?",
	"Knock knock, Neo!"
	};

int main(int argc, int** argv){
	// Anzahl Spalten
	const int spalten = 100; // Win 79
	// Speicher anfordern
	column* a = (column*)malloc(sizeof(column)*spalten);

	// Speicher initialisieren
	int i=0;
	for (i=0;i<spalten;i++){
		a[i].count=0;
		a[i].color=0;
		a[i].secret=-1;
		a[i].secretcount=0;
	}
	
	// drei mögliche Textarten
	const char f [4][9] = {{"\e[1;32m"},{"\e[2;32m"},{"\e[3;32m"},{"\e[0m"}};
	// Win grüne Ausgabe
	// system("Color 02");

	// Zufallszahlengenerator initialisieren
	srand(time(0));

	// Endlosschleife
	for(;;){
		// zufällige Spalte wählen
		int s = rand()%spalten;
		// entsprechende Zeile, zufällige Farbe und Anzahl
	 	a[s].count=rand()%30;
		a[s].color=(rand()%3+3)%3;

		// Geheimnis wählen
		if (a[s].secret<0)
			a[s].secret=rand()%260-(260-4);

		int i=0;
		// Ausgabe jede Spalte
		for(i=0;i<spalten;i++){
			// Ausgabe mit Farbe Betriebssystemabhängig
			// Ausgabe eines zufälligen (zwischen 32 und 126) Zeichens in entsprechender Farbe
			char c=a[i].count>0?' '+((rand()%94+94)%94):' ';

			// wenn Geheimnis gewählt und noch nicht fertig ausgegeben 
			if (a[i].secret>=0 && a[i].secretcount<strlen(geheimedinge[a[i].secret])){
				c=geheimedinge[a[i].secret][a[i].secretcount];
				a[i].secretcount++;
			} else {
				a[i].secret=-1;
				a[i].secretcount=0;
			}

			// Ausgabe Farbe und Zeichen
			// Geheimnis weiß
			printf("%s%c",f[a[i].secret>=0?3:a[i].color],c); // Win Ausgabe ohne Farbstring
			// Zähler der Spalte verringern
			a[i].count--;
		}
		// 100 Millisekunden warten	
		usleep(100000);
		// Sleep(100); // Windows

		printf("\n");
	}
	// Farbe zurücksetzten
	printf("\e[0m");
}
