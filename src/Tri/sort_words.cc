#include <iostream>
#include <string>
#include <fstream>
 
using namespace std;
 
int main() {

        ifstream fichier("../files/mots_faciles.txt", ios::in);  // on ouvre en lecture
        string file;
 
        if(fichier) {

            string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
            while( getline(fichier, contenu) ) {  // on met dans "contenu" la ligne

	            switch( contenu.length() ) {
	            	case 7 :
	            		file = "../files/mots_faciles_7_lettres.txt";
	            		break;
	            	case 8:	
	            		file = "../files/mots_faciles_8_lettres.txt";
	            		break;
	            	case 9:
	            		file = "../files/mots_faciles_9_lettres.txt";
	            		break;
	            	case 10:
	            		file = "../files/mots_faciles_10_lettres.txt";
	            		break;
	            	default:
	            		file = "../files/autres.txt";	
	            		break;		
	            }

	            ofstream fichier2(file, ios::out | ios::app);
	            fichier2 << contenu + '\n';
	        } 
        }

        ifstream fichier2("../files/mots_difficiles.txt", ios::in);  // on ouvre en lecture
 
        if(fichier2) {

            string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
            while( getline(fichier2, contenu) ) {  // on met dans "contenu" la ligne

	            switch( contenu.length() ) {
	            	case 7 :
	            		file = "../files/mots_difficiles_7_lettres.txt";
	            		break;
	            	case 8:	
	            		file = "../files/mots_difficiles_8_lettres.txt";
	            		break;
	            	case 9:
	            		file = "../files/mots_difficiles_9_lettres.txt";
	            		break;
	            	case 10:
	            		file = "../files/mots_difficiles_10_lettres.txt";
	            		break;
	            	default:
	            		file = "../files/autres.txt";	
	            		break;		
	            }

	            ofstream fichier3(file, ios::out | ios::app);
	            fichier3 << contenu + '\n';
	        } 
        }

        return 0;
}