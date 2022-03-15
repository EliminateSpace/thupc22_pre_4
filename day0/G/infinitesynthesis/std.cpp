#include <cstdio>
using namespace std;
#define PMAX 333
#define Q2MAX 666
int p[100008], q[100008];
double f[100008][2][3], psuc[336][702], pdraw[336][702], pfail[336][702];
// Pr(Alice wins)
// place / player (0: Alice, 1: Bob) / status
// (0: normal, 1: additional without challenge, 2: bonus from opponent)
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define copt(_id, _a, _b) (_id ? cmin(_a, _b) : cmax(_a, _b))
int main(){
	int n, i, j, k, dest, pval, qval;
	double tmp;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%d", &p[i]);
	for (i = 0; i < n; ++i) scanf("%d", &q[i]);
	
	for (i = 1; i <= PMAX; ++i) {
		for (j = 0; j <= Q2MAX; ++j) {
			tmp = 0;
			for (k = 1; k <= i; ++k) {
				tmp += dmin(j + 1, k);
			}
			psuc[i][j] = tmp / i / (j + 1);
			pdraw[i][j] = 1.0 * dmin(i, j) / i / (j + 1);
			pfail[i][j] = 1 - psuc[i][j] - pdraw[i][j];
		}
	}
	
	for (i = n - 1; i >= 0; --i) {
		for (j = 0; j < 2; ++j) {
			if (n - i <= p[i]) {
				f[i][j][0] = f[i][j][1] = f[i][j][2] = 1 - j;
				continue;
			}
			// f[i][j][0]: challenge
			f[i][j][0] = f[i + p[i]][j ^ 1][0];
			for (k = 1; k < p[i]; ++k) {
				dest = i + k;
				pval = p[i] - k;
				qval = q[i] + q[dest];
				// success: j -> j; draw / fail: j -> opponent
				tmp = psuc[pval][qval] * f[dest][j][1] + pdraw[pval][qval] * f[dest][j ^ 1][0] + pfail[pval][qval] * f[dest][j ^ 1][2];
				//fprintf(stderr, "%d->%d(%d):%lf %lf\n", dest, i, j, tmp, f[dest][j ^ 1][0]);
				copt(j, f[i][j][0], tmp);
				copt(j, f[i][j][0], f[dest][j ^ 1][0]);
			}
			// f[i][j][1]: additional from own challenge, j -> opponent
			f[i][j][1] = f[i + 1][j ^ 1][0];
			for (k = 2; k <= p[i]; ++k) copt(j, f[i][j][1], f[i + k][j ^ 1][0]);
			// f[i][j][2]: bonus from opponent, j2 -> j0
			f[i][j][2] = f[i + 1][j][0];
			for (k = 2; k <= p[i]; ++k) copt(j, f[i][j][2], f[i + k][j][0]);
		}
	}
	printf("%.18lf\n", f[0][0][0]);
	//for (i = 0; i < n; ++i) for (j = 0; j < 2; ++j) for (k = 0; k < 3; ++k) fprintf(stderr, "%d %d %d: %lf\n", i, j, k, f[i][j][k]);
	return 0;
}