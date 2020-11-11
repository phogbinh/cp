#include <bits/stdc++.h>

using namespace std;

#define LOCAL
#define MAX_E 250
#define INF 1000000000
#define PLACE 20
#define ID 10
#define WEIGHT 5

typedef pair<string, string> ss;

class Edge
{
public:
    Edge() {}
    Edge(string u, string v, string id, int w) : _u(u), _v(v), _id(id), _w(w) {}
    string _u, _v, _id;
    int _w = 0;
};

int E;
string line;
Edge EdgeList[MAX_E];
set<string> Vertex;
map<ss, int> AM; // [A]djacency [M]atrix
map<ss, string> p; // [p]arent

string parseWord(unsigned int& ind)
{
    string s;
    while (ind < line.size())
    {
        if (line[ind] == ',') break;
        s += line[ind];
        ++ind;
    }
    return s;
}

void parseComma(unsigned int& ind)
{
    ++ind;
}

int parseNumber(unsigned int& ind)
{
    int num = 0;
    while (ind < line.size())
    {
        num = 10*num + line[ind] - '0';
        ++ind;
    }
    return num;
}

void apsp()
{
    for (set<string>::iterator i = Vertex.begin(); i != Vertex.end(); ++i)
        for (set<string>::iterator j = Vertex.begin(); j != Vertex.end(); ++j)
            p[ ss(*i, *j) ] = *i;

    for (set<string>::iterator k = Vertex.begin(); k != Vertex.end(); ++k)
    {
        string t = *k;
        for (set<string>::iterator i = Vertex.begin(); i != Vertex.end(); ++i)
        {
            string u = *i;
            ss ut = ss(u, t);
            for (set<string>::iterator j = Vertex.begin(); j != Vertex.end(); ++j)
            {
                string v = *j;
                ss uv = ss(u, v);
                ss tv = ss(t, v);
                if (AM[ut] + AM[tv] < AM[uv])
                {
                    AM[uv] = AM[ut] + AM[tv];
                    p[uv] = p[tv];
                }
            }
        }
    }
}

void printAM()
{
    for (set<string>::iterator i = Vertex.begin(); i != Vertex.end(); ++i)
        printf("%s ", (*i).c_str());
    printf("\n");
    for (set<string>::iterator i = Vertex.begin(); i != Vertex.end(); ++i)
    {
        printf("%s: ", (*i).c_str());
        for (set<string>::iterator j = Vertex.begin(); j != Vertex.end(); ++j)
        {
            ss uv = ss(*i, *j);
            printf("%d ", AM[uv]);
        }
        printf("\n");
    }
}

vector<string> path;
void setPath(string u, string v)
{
    if (u != v) setPath(u, p[ss(u,v)]);
    path.push_back(v);
}

void printWhiteSpace(int i)
{
    while (i--) printf(" ");
}

int get_size(int n)
{
    int s = 0;
    while (true)
    {
        if (n == 0) break;
        n /= 10;
        ++s;
    }
    return s;
}

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL
    E = 0;
    while (true)
    {
        getline(cin, line);
        if (line == "") break;
        unsigned int ind = 0;
        string u = parseWord(ind);
        parseComma(ind);
        string v = parseWord(ind);
        parseComma(ind);
        string id = parseWord(ind);
        parseComma(ind);
        int w = parseNumber(ind);
//        printf("[%s]->[%s] - [%s] - [%d]\n", u.c_str(), v.c_str(), id.c_str(), w);
        Vertex.insert(u);
        Vertex.insert(v);
        EdgeList[E] = Edge(u, v, id, w);
        ss uv = ss(u, v);
        ss vu = ss(v, u);
        if (AM.find(uv) == AM.end()) AM[uv] = AM[vu] = w;
        else AM[uv] = AM[vu] = min(AM[uv], w);
        ++E;
    }
    for (set<string>::iterator i = Vertex.begin(); i != Vertex.end(); ++i)
        for (set<string>::iterator j = Vertex.begin(); j != Vertex.end(); ++j)
        {
            ss uv = ss(*i, *j);
            if ( AM.find(uv) == AM.end() ) AM[uv] = INF;
        }

//    for (int i = 0; i < E; ++i) printf("[%s]->[%s] - [%s] - [%d]\n", EdgeList[i]._u.c_str(), EdgeList[i]._v.c_str(), EdgeList[i]._id.c_str(), EdgeList[i]._w);
//    printAM();
    apsp();
//    printAM();
    while (getline(cin, line))
    {
        printf("\n\n");
        unsigned int ind = 0;
        string u = parseWord(ind);
        parseComma(ind);
        string v = parseWord(ind);
        path.clear();
        setPath(u, v);
        printf("From                 To                   Route      Miles\n");
        printf("-------------------- -------------------- ---------- -----\n");
        for (unsigned int i = 1; i < path.size(); ++i)
        {
            string u = path[i-1];
            string v = path[i];
            for (int j = 0; j < E; ++j)
                if ( (EdgeList[j]._u == u && EdgeList[j]._v == v)
                  || (EdgeList[j]._v == u && EdgeList[j]._u == v) )
            {
                printf("%s", u.c_str());
                printWhiteSpace(PLACE - (int)u.size() + 1);
                printf("%s", v.c_str());
                printWhiteSpace(PLACE - (int)v.size() + 1);
                string id = EdgeList[j]._id;
                printf("%s", id.c_str());
                printWhiteSpace(ID - (int)id.size() + 1);
                int w = EdgeList[j]._w;
                printWhiteSpace(WEIGHT - get_size(w));
                printf("%d\n", w);
                break;
            }
        }
        printf("                                                     -----\n");
        printf("                                          Total      ");
        int pathWeight = AM[ss(u, v)];
        printWhiteSpace(WEIGHT - get_size(pathWeight));
        printf("%d\n", pathWeight);
    }
    return 0;
}
