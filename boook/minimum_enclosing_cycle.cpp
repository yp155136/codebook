pdd arr[MAX], cen;
double r;
inline double dis(pdd a,pdd b){	return hypot(a.X-b.X,a.Y-b.Y);	}
int n,m;
inline double sq(double x){return x*x;}
pdd external(pdd p1,pdd p2,pdd p3){
	double a1=p1.X-p2.X,a2=p1.X-p3.X;
	double b1=p1.Y-p2.Y,b2=p1.Y-p3.Y;
	double c1=( sq(p1.X)-sq(p2.X)+sq(p1.Y)-sq(p2.Y) )/2;
	double c2=( sq(p1.X)-sq(p3.X)+sq(p1.Y)-sq(p3.Y) )/2;
	double dd=a1*b2-a2*b1;
	return pdd( (c1*b2-c2*b1)/dd , (a1*c2-a2*c1)/dd );
}
int main(){
	IOS
	srand(time(0));
	while(cin>>n>>m){
		if(n+m==0)	return 0;
		for(int i=0;i<m;i++){
			cin>>arr[i].X>>arr[i].Y;
		}
		random_shuffle(arr,arr+m);
		r=0;
		for(int i=0;i<m;i++){
			if(dis(cen,arr[i])>r){
				cen=arr[i]; r=0;
				for(int j=0;j<i;j++){
					if(dis(cen,arr[j])>r){
						cen=pdd( (arr[i].X+arr[j].X)/2 , (arr[i].Y+arr[j].Y)/2 );
						r=dis(cen,arr[j]);
						for(int k=0;k<j;k++){
							if(dis(cen,arr[k])>r){
								cen=external(arr[i],arr[j],arr[k]);
								r=dis(cen,arr[j]);
							}
						}
					}
				}
			}
		}
		cout<<stp<<r<< '\n';
	}
	return 0;
}
