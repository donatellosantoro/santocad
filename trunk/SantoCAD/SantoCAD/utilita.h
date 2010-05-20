#ifndef UTILITA_H
#define UTILITA_H

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Logger.h"
#define GetCurrentDir _getcwd

using namespace std;

class Utilita{

public:
	static char* Utilita::stringToChar(string stringa) {
		char* charArray;
		charArray = new char[stringa.length()+1];
		strcpy_s(charArray,stringa.length()+1,stringa.c_str());
		return charArray;
	}

	static string Utilita::getCartellaCorrente(){
		char cCurrentPath[FILENAME_MAX];

		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
			return NULL;
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '/0'; /* not really required */
		return string(cCurrentPath);
	}

	static string Utilita::getPercorsoRelativo(string percorsoAssoluto, string cartellaIniziale){
		string percorsoRelativo = percorsoAssoluto;
		if(percorsoAssoluto.length() > cartellaIniziale.length()){
			string baseDir = percorsoAssoluto.substr(0,cartellaIniziale.length());
			if(baseDir.compare(cartellaIniziale)==0){
				percorsoRelativo = percorsoRelativo.substr(baseDir.length(),percorsoAssoluto.length() - baseDir.length());
			}
		}
		return percorsoRelativo;
	}

	static string Utilita::getPercorsoAssoluto(string percorsoRelativo, string cartellaIniziale){
		string percorsoAssoluto = percorsoRelativo;
		if(percorsoRelativo.length() > 1){
			char c = percorsoRelativo.at(1);
			if(c != ':'){
				percorsoAssoluto = cartellaIniziale + percorsoRelativo;
			}
		}
		return percorsoAssoluto;
	}

	
	static void Utilita::convertiInDoppioSlash(string *text){
		string old_s = "\\";
		string new_s = "\\\\";
		int pos = (*text).find(old_s);
		while(pos!=-1){
			(*text).replace(pos,old_s.length(),new_s);
			pos = (*text).find(old_s,pos+2);
		}
	}

	
	static void Utilita::sostituisciStringa(string *text, string old_s, string new_s){
		int pos = (*text).find(old_s);
		if(pos!=-1){
			(*text).replace(pos,old_s.length(),new_s);
		}
	}
	
	static void Utilita::sostituisciStringaRicorsiva(string *text, string old_s, string new_s){
		int pos = (*text).find(old_s);
		while(pos!=-1){
			(*text).replace(pos,old_s.length(),new_s);
			pos = (*text).find(old_s);
		}
	}

	static void Utilita::copiaFile(string src, string dst){
		Logger::debug("Copy of file " + src + " into " + dst);
		std::ifstream infile(Utilita::stringToChar(src), std::ios_base::binary);
		std::ofstream outfile(Utilita::stringToChar(dst), std::ios_base::binary);
		outfile << infile.rdbuf();
	}

	static string Utilita::caricaFile(char* nomeFile){
		ifstream in_file(nomeFile);
		if( !in_file ) {
			Logger::error("Unable to load file ", nomeFile);
			return false;
		}

		string out_string;
		string line;
		while(getline(in_file,line)){
			out_string += line + "\n";
		}

		return out_string;
	}

};

#endif