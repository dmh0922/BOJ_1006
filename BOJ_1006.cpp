#include <iostream>
#define CASES 5

enum { X = 0, SELF = 1, UP = 2, DOWN = 3, BOTH = 4 };

int N, W;
std::pair<int,int>* Onetagon;

const int isCombSelf(const int X) { return ( Onetagon[X].first + Onetagon[X].second <= W ) ? 1 : 0; }
const int isCombUp(const int X, const int Y) { return ( Onetagon[X].first + Onetagon[Y].first <= W ) ? 1 : 0; }
const int isCombDown(const int X, const int Y) { return ( Onetagon[X].second + Onetagon[Y].second <= W ) ? 1 : 0; }

const int max(const int a, const int b) { return ( a > b ) ? a : b; }
const int max(int* data) {
    int ret = -1;
    for (int iter=0; iter<5; iter++) { ret = ( ret > data[iter] ) ? ret : data[iter]; }
    return ret;
}

void set(int** Combine, int idx);

int main(void)
{
    std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);

    int T; std::cin >> T;
    while ( T-- ) {
        std::cin >> N >> W;
        Onetagon = new std::pair<int,int> [N+1];
        for (int iter=1; iter<=N; iter++) { std::cin >> Onetagon[iter].first; }
        for (int iter=1; iter<=N; iter++) { std::cin >> Onetagon[iter].second; }

        if ( N == 1 ) { std::cout << 2 - isCombSelf(1) << '\n'; continue; }

        int** Combine = new int* [N+1]; int MaxComb[CASES];
        for (int iter=0; iter<=N; iter++) { Combine[iter] = new int [CASES]; }

        // case = X , SELF
        for (int iter=0; iter<CASES; iter++) { Combine[0][iter] = 0; Combine[1][iter] = 0; Combine[N][iter] = 0; }
        Combine[1][SELF] = isCombSelf(1);

        for (int iter=2; iter<N; iter++) { set(Combine,iter); }

        set(Combine,N);

        MaxComb[X] = max( Combine[N] ); MaxComb[SELF] = max( Combine[N] );

        // case = UP
        for (int iter=0; iter<CASES; iter++) { Combine[0][iter] = 0; Combine[1][iter] = 0; Combine[N][iter] = 0; }
        Combine[1][UP] = isCombUp(N,1);

        for (int iter=2; iter<N; iter++) { set(Combine,iter); }

        Combine[N][X] = max( Combine[N-1] );
        Combine[N][DOWN] = max( max( Combine[N-2] ), Combine[N-1][UP] ) + isCombDown(N-1,N);

        MaxComb[UP] = max( Combine[N][X], Combine[N][DOWN] );

        // case = DOWN
        for (int iter=0; iter<CASES; iter++) { Combine[0][iter] = 0; Combine[1][iter] = 0; Combine[N][iter] = 0; }
        Combine[1][DOWN] = isCombDown(N,1);

        for (int iter=2; iter<N; iter++) { set(Combine,iter); }

        Combine[N][X] = max( Combine[N-1] );
        Combine[N][UP] = max( max( Combine[N-2] ), Combine[N-1][DOWN] ) + isCombUp(N-1,N);

        MaxComb[DOWN] = max( Combine[N][X], Combine[N][UP] );

        // case = BOTH
        for (int iter=0; iter<CASES; iter++) { Combine[0][iter] = 0; Combine[1][iter] = 0; Combine[N][iter] = 0; }
        Combine[1][BOTH] = isCombDown(N,1) + isCombUp(N,1);

        for (int iter=2; iter<N; iter++) { set(Combine,iter); }

        Combine[N][X] = max( Combine[N-1] );

        MaxComb[BOTH] = Combine[N][X];

        std::cout << 2*N - max( MaxComb ) << '\n';
    }

    return 0;
}

void set(int** Combine, int idx) {

    if (idx < 2) return;

    Combine[idx][X] = max( Combine[idx-1] );
    Combine[idx][SELF] = max( Combine[idx-1] ) + isCombSelf(idx);
    Combine[idx][UP] = max( max ( Combine[idx-2] ), Combine[idx-1][DOWN] ) + isCombUp(idx-1,idx);
    Combine[idx][DOWN] = max( max ( Combine[idx-2] ), Combine[idx-1][UP] ) + isCombDown(idx-1,idx);
    Combine[idx][BOTH] = max( Combine[idx-2] ) + isCombDown(idx-1,idx) + isCombUp(idx-1,idx);

    return;
}