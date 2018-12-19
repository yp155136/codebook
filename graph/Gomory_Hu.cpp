def cut(G,s,t) :
	return minimum s-t cut in G

def gomory_hu(G):
	T = {}
	P = [1] * |V(G)|
	for s in [2,n] :
		t = p[s]
		C = cut(G,s,t)
		add(s,t,w(C)) to c
		for i in [s+1,n] :
			if p[i] == t and s-i path exists in G\C :
				p[i] = s
	return T;
