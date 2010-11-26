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

        s2="/home/badkrist/Documents/glpk/data";


        int ret;
        lp = glp_create_prob();
        tran = glp_mpl_alloc_wksp();

        //glp_smcp parm;




        if (glp_mpl_read_model(tran, s1.c_str(), 1) != 0)
        {
            fprintf(stderr, "Error on translating model\n");
            goto skip;
        }

        //create_data_file(s2); //on genere le fichier de donnees

       
        ret = glp_mpl_generate(tran, NULL);

        if(glp_mpl_read_data(tran, s2.c_str()) != 0)
        {

            fprintf(stderr, "Error on generating model\n");
            goto skip;
        }


        if (glp_mpl_generate(tran, NULL) != 0)
        {
            fprintf(stderr, "Error on generating model\n");
            goto skip;
        }


        glp_mpl_build_prob(tran, lp);
        glp_simplex(lp, NULL);
        glp_intopt(lp, NULL);
        if (glp_mpl_postsolve(tran, lp, GLP_MIP) != 0)
             fprintf(stderr, "Error on postsolving model\n");

        Solution sol;
            sol.GenerateFromGLPK(lp);
            if(sol.HasSubCycle())
                sol.Iterate(lp, graph);



skip:
        glp_mpl_free_wksp(tran);
        glp_delete_prob(lp);


    }

    void Solution::GenerateFromGLPK(glp_prob *mip)
{
    //Init
    weight = 0;
    map<int, int> pathList;



    for (int i = 1; i <=  glp_get_num_cols(mip) ; i++)
    {
        //cout << lpx_get_col_name(mip, i) << " " << lpx_get_col_prim(mip, i) << endl;
        string data = lpx_get_col_name(mip, i);
        if(data[0] == 'x')
        {
            int n1 = atoi(data.substr(data.find('[') + 1, data.find(',')  - data.find('[') - 1).c_str());
            int n2 = atoi(data.substr(data.find(',') + 1, data.find(']')  - data.find(',') - 1).c_str());
            //cout << data.substr(data.find('[') + 1, data.find(',')  - data.find('[') - 1).c_str() << endl;
            //cout << data.substr(data.find(',') + 1, data.find(']')  - data.find(',') - 1).c_str() << endl;
            int v = lpx_get_col_prim(mip, i);
            if(v == 1)
                pathList[n1] = n2;
        }

    }

    int n = 0;
    while(!pathList.empty())
    {
        paths.resize(n + 1);
        int start = (*pathList.begin()).first;
        int next = (*pathList.begin()).second;
        pathList.erase(pathList.begin());
        paths[n].push_back(start);
        while(start != next && !pathList.empty())
        {
            map<int, int>::iterator it = pathList.find(next);
            if(it == pathList.end())
            {
                cout << "error while building solution" << endl;
                exit(1);
            }
            int current = (*it).first;
            next = (*it).second;
            pathList.erase(it);
            paths[n].push_back(current);
        }

        n++;
    }
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

        int num = glp_add_rows(prob,1);
        glp_set_row_bnds(prob,num,type,lb,ub);
    }


};

int main(void) {
    Problem* p = new Problem("/home/badkrist/Documents/glpk/PVC2.modele", "/home/badkrist/Documents/glpk/greuville5.dgs");
}