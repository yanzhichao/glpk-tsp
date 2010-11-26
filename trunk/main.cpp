/* 
 * File:   main.cpp
 * Author: badkrist
 *
 * Created on 8 novembre 2010, 09:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>
#include <string>
#include <fstream>
#include <iostream>



using namespace std;

class Problem {
private:
    glp_prob *lp;
    glp_tran *tran;
public:

    Problem(string s1, string s2) {

        int ret;
        lp = glp_create_prob();
        glp_smcp parm;




        tran = glp_mpl_alloc_wksp();
        ret = glp_mpl_read_model(tran, s1.c_str(), 0);
        if (ret != 0) {
            fprintf(stderr, "Error on translating model\n");
            goto skip;
        }

        //create_data_file(s2); //on genere le fichier de donnees

        ret = glp_mpl_read_data(tran, "/home/badkrist/Documents/glpk/data");
        ret = glp_mpl_generate(tran, NULL);
        if (ret != 0) {
            fprintf(stderr, "Error on generating model\n");
            goto skip;
        }
        glp_mpl_build_prob(tran, lp);
        glp_init_smcp(&parm);
        parm.meth = GLP_DUAL;
                glp_simplex(lp, &parm);
        //
        glp_mpl_postsolve(tran,lp,GLP_SOL);

        glp_print_sol(lp, "25fv47.txt");


skip:
        glp_mpl_free_wksp(tran);
        glp_delete_prob(lp);


    }

    void create_data_file(string s) {
        ifstream fichier(s.c_str(), ios::in); // on ouvre en lecture
        string r;
        int nbLignes = 0;
        if (fichier) {
            string ligne;

            while (getline(fichier, ligne)) 
            {

                if (ligne.substr(0, 2) == "ae") {
                    ligne = ligne.replace(0, 3, "");
                    ligne = ligne.replace(0, ligne.find(" ") + 2, "");
                    ligne = ligne.replace(ligne.find(" ") - 1, 3, "&");
                    ligne = ligne.replace(ligne.find(" ") - 1, 9, " ");
                    ligne = ligne.replace(ligne.find("&"), 1, " ");
                    r.append(ligne);
                    r.append("\n");
                    nbLignes++;
                }

            }
            ofstream temp("data", ios::out | ios::trunc);
            if (temp) {
                temp << "data;" << endl;
                temp << "param n :=" << nbLignes << ";" << endl;
                temp << "param : E : c:=  " << endl;
                temp << r << ";";
                temp.close();
            } else
                cerr << "Impossible d'ecrire le fichier !" << endl;
        } else
            cerr << "Impossible d'ouvrir le fichier !" << endl;

    }

    void getGraph(string s) {
        ifstream fichier(s.c_str(), ios::in); // on ouvre en lecture
        string r;
        int nbLignes = 0;
        if (fichier) {
            string ligne;
            int compteurLignePointille=0;

            while (getline(fichier, ligne))
            {
                if(compteurLignePointille==2)
                {
                    
                }
                else
                    if(ligne.substr(0,2)=="--")
                    {
                        compteurLignePointille++;
                    }
                if (ligne.substr(0, 2) == "ae") {
                    ligne = ligne.replace(0, 3, "");
                    ligne = ligne.replace(0, ligne.find(" ") + 2, "");
                    ligne = ligne.replace(ligne.find(" ") - 1, 3, "&");
                    ligne = ligne.replace(ligne.find(" ") - 1, 9, " ");
                    ligne = ligne.replace(ligne.find("&"), 1, " ");
                    r.append(ligne);
                    r.append("\n");
                    nbLignes++;
                }

            }
            ofstream temp("data", ios::out | ios::trunc);
            if (temp) {
                temp << "data;" << endl;
                temp << "param n :=" << nbLignes << ";" << endl;
                temp << "param : E : c:=  " << endl;
                temp << r << ";";
                temp.close();
            } else
                cerr << "Impossible d'ecrire le fichier !" << endl;
        } else
            cerr << "Impossible d'ouvrir le fichier !" << endl;

    }

    void addConstraint(glp_prob * prob,int type, double lb, double ub)
    {
        int num = glp_add_cols(prob,1);
        glp_set_col_bnds(prob,num,type,lb,ub);
    }
};

int main(void) {
    Problem* p = new Problem("/home/badkrist/Documents/glpk/PVC2.modele", "/home/badkrist/Documents/glpk/greuville5.dgs");
}