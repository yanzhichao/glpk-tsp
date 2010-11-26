#include <graph.hpp>

Solution Solution::best;

Graph::Graph(int size)
{
    nodes.resize(size);
}

void Graph::AddPath(int src, int dest, int length)
{
    nodes[src - 1][dest] = length;
}

void Graph::GenerateDataFile(string path)
{
    fstream stream;
    stream.open(path.c_str(),  ios_base::out | ios_base::trunc);
    stream << "data;" << endl;

    stream << "param n:=" << nodes.size() << ";" << endl;
    stream << "param : E : c:=" << endl;
    for(unsigned int n = 0; n < nodes.size(); n++)
        for(map<unsigned int , unsigned int >::iterator it = nodes[n].begin(); it != nodes[n].end(); ++it)
            stream << (n + 1) << " " << (*it).first << " " << (*it).second << endl;




    stream << ";" << endl;
    stream << "end;" << endl;
    stream.close();
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


void Solution::GenerateFromFile(string path)
{
    //Init
    char temp[256];
    weight = 0;
    map<int, int> pathList;

    fstream stream;
    stream.open(path.c_str(),  ios_base::in);
    stream.getline(temp, 256);
    stream >> weight;
    stream.getline(temp, 256);
    stream.getline(temp, 256);

    while(stream.good())
    {
        stream.getline(temp, 256);
        if(temp[0] != 'x')
            break;
        string data = temp;
        int n1 = atoi(data.substr(data.find('[') + 1, data.find(',')  - data.find('[') - 1).c_str());
        int n2 = atoi(data.substr(data.find(',') + 1, data.find(']')  - data.find(',') - 1).c_str());
        int v =  atoi(data.substr(data.find('=') + 2, 1).c_str());
        if(v == 1)
            pathList[n1] = n2;

        //cout << n1 << " " << n2 << " " << v << endl;
        //cout << temp << endl;
    }
    stream.close();

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
                return;
            }
            int current = (*it).first;
            next = (*it).second;
            pathList.erase(it);
            paths[n].push_back(current);
        }

        n++;
    }
}

void Solution::Iterate(glp_prob *mip, Graph& graph)
{
    //On parcourt la liste de sous tour
    for(vector<list<int> >::iterator listIt = paths.begin(); listIt != paths.end(); ++listIt)
    {
        //On parcourt les sommets
        for(list<int>::iterator it = (*listIt).begin(); it != (*listIt).end(); )
        {
            ostringstream out;

            int next;
            int start = (*it);
            ++it;
            if(it == (*listIt).end())
            {
                next = (*(*listIt).begin());
            }
            else
            {
                next = (*it);
                ++it;
            }
            out << "x[" << start << "," << next << "]";
            //cout << out.str() << endl;

            lpx_create_index(mip);

            int col = lpx_find_col(mip, out.str().c_str());
            if(col == 0)
                cout << "halloooo" << endl;
            lpx_set_col_bnds(mip, col, LPX_FX, 0, 0);


            lpx_simplex(mip);
            //cout << lpx_simplex(mip) << endl;
            //cout << LPX_NOFEAS << " " << lpx_get_status(mip) << endl;
            Solution sol;
            sol.GenerateFromGLPK(mip);
            if(sol.CountCycle() == 1)
                sol.CheckSolution(graph);

            //cout << sol.CountCycle() << endl;

            if(lpx_get_status(mip) == LPX_OPT //une de solution
                    && sol.HasSubCycle())//si on a des sous tour
                sol.Iterate(mip, graph);

            lpx_create_index(mip);
            col = lpx_find_col(mip, out.str().c_str());
            lpx_set_col_bnds(mip, col, LPX_LO, 0, 0);

        }

    }
}

void Solution::CheckSolution(Graph& graph)
{
    weight = 0;
    for(list<int>::iterator it = paths[0].begin(); it != paths[0].end(); )
    {
        ostringstream out;
        int next;
        int start = (*it);
        ++it;
        if(it == paths[0].end())
        {
            next = (*paths[0].begin());
        }
        else
        {
            next = (*it);
            ++it;
        }

        weight += graph.GetWeight(start, next);
    }

    if(weight < best.weight)
    {
        best.weight = weight;
    }
}


void Solution::EchoResult()
{
    cout << "meilleur resultat : " << best.weight << endl;


}

