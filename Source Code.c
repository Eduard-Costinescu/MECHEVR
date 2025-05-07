#include<stdio.h>
#include<math.h>
#include<stdlib.h>


struct sdi{
	int z;
	float p;
	int rbrat;
	double uvol;
	double srd;
};
struct rezultate{
	int z;
	float p;
	int rbrat;
	double uvol;
	double sreal;

};
void citire(struct sdi s[],int n,FILE *f){


	int i;
	for(i = 0;i<n;i++){
		fscanf(f,"%lf%d%f%d%lf",&s[i].srd,&s[i].z,&s[i].p,&s[i].rbrat,&s[i].uvol);

	}

}
void citirez(struct rezultate r[],int n,FILE *f){


	int i;
	for(i = 0;i<n;i++){
		fscanf(f,"%lf%d%f%d%lf",&r[i].sreal,&r[i].z,&r[i].p,&r[i].rbrat,&r[i].uvol);
	}
}
void steeringratio(double srd,double uvol,int rbrat,int z,float p,FILE *f){
	int i;
	int j;
	double cursatot;
	double uroatarad;
	double uroata;
	double sreal;

	for(i = z;i<=20;i++)
		for(j = p;j<=6;j++){

			cursatot = i*j*(uvol/360);
			uroatarad = atan(cursatot/(double)rbrat);
			uroata = uroatarad*(180/3.1415);

			sreal = uvol/(2.0*uroata);
			if((sreal-srd <1) && (sreal-srd >-1)){
				//				printf("Steering ratio ul este %.2lf\n",sreal);
				fprintf(f,"%.2lf %d %.2f %d %.2lf",sreal,z,p,rbrat,uvol);
				fprintf(f,"\n");
			}}

}
int numarare(FILE *f){
	int n = 0;
	double d1,d2;
	int d3,d4;
	float d5;

	while(fscanf(f,"%lf%d%f%d%lf",&d1,&d3,&d5,&d4,&d2) == 5)
		n++;


	return n;
}
void sortarecrescatoare(struct rezultate r[],int n1,FILE *f){
	struct rezultate temp;
	int i;
	int j;
	for(i = 0; i < n1-1; i++)
		for(j = i+1; j < n1; j++){
			if(r[i].sreal > r[j].sreal){
				temp = r[i];
				r[i] = r[j];
				r[j] = temp;

			}
			else if(r[i].sreal == r[j].sreal && r[i].z > r[j].z){
				temp = r[i];
				r[i] = r[j];
				r[j] = temp;

			}

		}
	for(i = 0;i<n1;i++){
		fprintf(f,"%.2lf %d %.2f %d %.2lf",r[i].sreal,r[i].z,r[i].p,r[i].rbrat,r[i].uvol);
		fprintf(f,"\n");
	}

}
void sortaredescrescatoare(struct rezultate r[],int n1,FILE *f){
	struct rezultate temp;
	int i;
	int j;
	for(i = 0; i < n1-1; i++)
		for(j = i+1; j < n1; j++){
			if(r[i].sreal < r[j].sreal){
				temp = r[i];
				r[i] = r[j];
				r[j] = temp;

			}
			else if(r[i].sreal == r[j].sreal && r[i].z < r[j].z){
				temp = r[i];
				r[i] = r[j];
				r[j] = temp;

			}

		}
	for(i = 0;i<n1;i++){
		fprintf(f,"%.2lf %d %.2f %d %.2lf",r[i].sreal,r[i].z,r[i].p,r[i].rbrat,r[i].uvol);
		fprintf(f,"\n");
	}

}

void filtrareint(struct rezultate r[],int n,float min,float max){
	int i;
	int nr = 0;

	for(i = 0;i<n;i++){
		if(r[i].sreal>min && r[i].sreal <max){
			printf("Steering ratio ul obtinut in urma filtrarii este : %.2lf\n",r[i].sreal);
			nr++;
		}
	}
	if(nr == 0)
		printf("Nu s au gasit steering ratio urile dorite in intervalul introdus!");

}

int main(){
	struct sdi *s;
	struct rezultate *r;
	int i;
	int n;
	int n1;
	int rasp;
	float min = 5;
	float max = 6;
	FILE *fi;
	FILE *fo;
	FILE *f1;
	FILE *f2;
	fi = fopen("input.txt","r");
	fo = fopen("output.csv","w");




	if(!fi){
		printf("Eroare la deschidere fisier!");
		return 0;
	}
	n = numarare(fi);
	fseek(fi, 0, SEEK_SET);
	s = malloc(n*(sizeof(struct sdi)));

	citire(s,n,fi);

	for(i = 0;i<n;i++)
		steeringratio(s[i].srd, s[i].uvol,s[i].rbrat,s[i].z,s[i].p,fo);
	fclose(fo);
	f1 = fopen("output.csv","r");
	if(!f1){
		printf("Eroare la deschidere fisier!");
		return 0;
	}
	n1 = numarare(f1);
	fseek(f1, 0, SEEK_SET);
	r = malloc(n1*(sizeof(struct rezultate)));
	citirez(r,n1,f1);

	printf("Introduceti 1 pentru sortarea crescatoare 2 pt descrescatoare:");
	fflush(stdout);
	scanf("%d",&rasp);
	if(rasp == 1){
		f2 = fopen("output.csv","w");
		sortarecrescatoare(r,n1,f2);}
	if(rasp == 2){
		f2 = fopen("output.csv","w");
		sortaredescrescatoare(r,n1,f2);}

	filtrareint(r,n1,min,max);


	fclose(fi);
	fclose(f1);
	fclose(f2);

	return 0;
}
