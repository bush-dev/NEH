#include <iostream>
#include <fstream>

using namespace std;

struct Quest
{
public:
	int r,p,q;
};

istream& operator >> (istream& enter, Quest& request)
{
	enter >> request.r >> request.p >> request.q;
	return enter;
}

ostream& operator << (ostream& exit, Quest& request)
{
	cout << request.r << " " << request.p << " " << request.q << endl;
	return exit;
}

int main()
{
	int n, m; 
	int PI[1000][3];
	int C[100][100];
	ifstream file;
	file.open("NEH1.DAT", ios::in);
	file >> n >> m;
	for (int i=1; i<=n; i++)
	{
		file >> PI[i][0] >> PI[i][1] >> PI[i][2];
		cout << PI[i][0] << PI[i][1] << PI[i][2] << endl;
	}
	file.close();
	for (int i=0; i<3; i++)
		PI[0][i]=0;
	for (int k=0; k<m; k++)
		C[0][k]=0;
	for (int j=0; j<n; j++)
		C[j][0]=0;

	for (int j=1; j<=n; j++)
		for (int k=1; k<=m; k++)
			C[j][k]=max(C[j-1][k], C[j][k-1]) + PI[j][k]; 

	cout << C[n][m] << endl;


}