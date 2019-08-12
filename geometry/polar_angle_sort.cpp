bool cmp(vec a,vec b){
	if((a.Y>0||(a.Y==0&&a.X>0))&&(b.Y<0||(b.Y==0&&b.X<0)))
		return 1;
	if((b.Y>0||(b.Y==0&&b.X>0))&&(a.Y<0||(a.Y==0&&a.X<0)))
		return 0;
	return (a^b)>0;
}
