#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>



#define INF -1 // N�o descoberto (desconexo).
#define NUL -2 // Orf�o (raiz).
#define PRETO 0 // Descendentes j� est�o pretos ou n�o tem descendentes.
#define CINZA 1 // Descoberto.
#define BRANCO 2 // N�o descoberto.


int *cor;
char *predescessor;

using namespace std;

vector<char> *g;
vector<char> Y;

void DFS_visit(char vA)
{
    Y.push_back(vA);
    char vB;
    vector<char>::iterator it;
    cor[vA] = CINZA;

    for(it = g[vA].begin(); it!=g[vA].end(); it++)
    { // Varre o vector, passando por todos os v�rtices adjacentes ao v�rtice u.

        vB = *it;
        if(cor[vB] == BRANCO)
        { // Se o v�rtice(vB) adjacente �quele que est� sendo avaliado(vA) ainda n�o tiver sido descoberto (branco).

            predescessor[vB] = vA; // O predecessor do v�rtice adjacente se torna o v�rtice que est� sendo avaliado pela fun��o(vA).
            DFS_visit(vB); // A fun��o � chamada, recursivamente, para avaliar o v�rtice adjacente.
        }
    }

    cor[vA] = PRETO; // Pinta de preto o v�rtice que est� sendo avaliado pela fun��o, j� que todos os v�rtices descendentes dele j� foram completamente avaliados (e tamb�m pintados de preto).
}


void DFS(int numeroDeVertices, int raiz)
{
    cor = new int['a'+numeroDeVertices];
    predescessor = new char['a'+numeroDeVertices];

    int vA;

    for(vA=0; vA < 'a'+numeroDeVertices-1; vA++)
    {

        cor[vA] = BRANCO;
        predescessor[vA] = NUL;
    }

    for(char i='a'; i < 'a'+numeroDeVertices-1; i++)
    {
        if(cor[i]==BRANCO) {

            DFS_visit(i);
        }
        if(!Y.empty()) {
            sort(Y.begin(), Y.end());
            for (int j = 0; j < Y.size(); j++) {
                cout << Y[j] << ",";
            }
            cout<<endl;
            while (!Y.empty())Y.pop_back();
        }
    }
}

int main()
{
    int N,M,T,aux = 0;
    cin>>T;
    for(int j; j<T; j++) {

        cin >>N>> M;

        g = new vector<char>['a'+N + 5];
        Y.reserve('a'+N+5);

        char x, y;
        for (int i = 0; i < M; i++) {
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        cout<<"Case #"<<j+1<<":"<<endl;
        DFS(N + 1, 'a');
        for (char i = 'a'; i <= 'a'+N-1; i++) {
            if(predescessor[i] == NUL) aux++;
        }
        cout<<aux<<" connected components"<<endl;
        cout<<endl;
        aux = 0;
    }
    return 0;
}
